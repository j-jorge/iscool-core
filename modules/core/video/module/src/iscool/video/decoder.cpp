/*
  Copyright 2018-present IsCool Entertainment

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.
*/
#include <iscool/video/decoder.hpp>

#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/log/nature/info.hpp>
#include <iscool/none.hpp>
#include <iscool/signals/implement_signal.hpp>
#include <iscool/signals/relay.hpp>
#include <iscool/signals/scoped_connection.hpp>

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

#include <array>
#include <chrono>
#include <functional>
#include <memory>

namespace iscool
{
  namespace video
  {
    namespace detail
    {
      static void close_format_context(AVFormatContext* context);
      static bool log_av_error(int result_code);
      static void log_hardware_device_types();
      static void log_codec_details(const AVCodecContext& context,
                                    const AVCodec& codec);

      using format_context_pointer =
          std::unique_ptr<AVFormatContext, decltype(&close_format_context)>;
      using codec_context_pointer =
          std::unique_ptr<AVCodecContext, decltype(&avcodec_close)>;
      using scale_context_pointer =
          std::unique_ptr<SwsContext, decltype(&sws_freeContext)>;
      using frame_pointer = std::unique_ptr<AVFrame, decltype(&av_free)>;

      static constexpr std::size_t frame_queue_capacity = 2;

      class decoder_thread
      {
      public:
        using frame_ready_function = std::function<void(std::uint8_t*)>;

      public:
        decoder_thread(decoder_state& shared_state,
                       format_context_pointer format_context,
                       codec_context_pointer codec_context,
                       int video_stream_index,
                       frame_ready_function frame_ready);

        void operator()();

      private:
        void initialize();

        void push_next_frame();
        bool decode_frame(AVPacket& packet);
        void pop_frame();
        void dispatch_frame();
        void reset_stream();

      private:
        format_context_pointer _format_context;
        codec_context_pointer _codec_context;
        int _video_stream_index;
        frame_ready_function _frame_ready;

        decoder_state& _shared_state;

        frame_pointer _current_frame;

        std::vector<std::uint8_t> _frame_buffer[frame_queue_capacity];

        frame_pointer _frame_dispatch_queue[frame_queue_capacity];
        int _frame_dispatch_pop_index;
        int _frame_dispatch_push_index;
        int _frame_dispatch_queue_size;

        scale_context_pointer _scale_context;

        std::chrono::time_point<std::chrono::steady_clock>
            _last_frame_dispatch_date;

        std::chrono::nanoseconds _frame_duration;
      };
    }
  }
}

IMPLEMENT_SIGNAL(iscool::video::decoder, frame_ready, _frame_ready);

iscool::video::decoder::decoder()
{
  detail::log_hardware_device_types();
}

iscool::video::decoder::~decoder()
{
  terminate_thread();
}

iscool::optional<iscool::video::video_info>
iscool::video::decoder::decode(const std::string& path)
{
  terminate_thread();

  _decoder_state.quit = false;
  _decoder_state.need_update = false;

  AVFormatContext* raw_format_context(nullptr);

  if (detail::log_av_error(avformat_open_input(
          &raw_format_context, path.c_str(), nullptr, nullptr)))
    return iscool::none;

  detail::format_context_pointer format_context(raw_format_context,
                                                &detail::close_format_context);

  if (detail::log_av_error(
          avformat_find_stream_info(raw_format_context, nullptr)))
    return iscool::none;

  int video_stream_index(-1);

  for (int i(0); i != raw_format_context->nb_streams; ++i)
    if (raw_format_context->streams[i]->codecpar->codec_type
        == AVMEDIA_TYPE_VIDEO)
      {
        video_stream_index = i;
        break;
      }

  if (video_stream_index == -1)
    {
      ic_log(iscool::log::nature::error(), "iscool::video::decoder",
             "No video stream found in '{}'.", path.c_str());
      return iscool::none;
    }

  detail::codec_context_pointer codec_context(
      raw_format_context->streams[video_stream_index]->codec, &avcodec_close);

  AVCodec* const codec(avcodec_find_decoder(codec_context->codec_id));

  if (codec == nullptr)
    {
      ic_log(iscool::log::nature::error(), "iscool::video::decoder",
             "Unsupported codec in '{}': {}.", path.c_str(),
             static_cast<int>(codec_context->codec_id));
      return iscool::none;
    }

  AVDictionary* options(nullptr);

  if (detail::log_av_error(
          avcodec_open2(codec_context.get(), codec, &options)))
    return iscool::none;

  detail::log_codec_details(*codec_context, *codec);

  video_info result;

  result.width = codec_context->width;
  result.height = codec_context->height;

  _thread = std::thread(detail::decoder_thread(
      _decoder_state, std::move(format_context), std::move(codec_context),
      video_stream_index,
      std::bind(iscool::signals::relay(_frame_ready), std::placeholders::_1)));

  return result;
}

void iscool::video::decoder::consume_frame()
{
  {
    std::unique_lock<std::mutex> lock(_decoder_state.mutex);
    _decoder_state.need_update = true;
  }

  _decoder_state.update_condition.notify_one();
}

void iscool::video::decoder::terminate_thread()
{
  {
    const std::lock_guard<std::mutex> lock(_decoder_state.mutex);
    _decoder_state.quit = true;
    _decoder_state.need_update = true;
  }

  _decoder_state.update_condition.notify_one();

  if (_thread.joinable())
    _thread.join();
}

void iscool::video::detail::close_format_context(AVFormatContext* context)
{
  avformat_close_input(&context);
}

bool iscool::video::detail::log_av_error(int result_code)
{
  if (result_code >= 0)
    return false;

  static char string_buffer[AV_ERROR_MAX_STRING_SIZE];
  av_strerror(result_code, string_buffer, sizeof(string_buffer));
  ic_log(iscool::log::nature::error(), "iscool::video::decoder", "{}",
         static_cast<const char*>(string_buffer));

  return true;
}

void iscool::video::detail::log_hardware_device_types()
{
  ic_log(iscool::log::nature::info(), "iscool::video::decoder",
         "HW device types");

  for (AVHWDeviceType type(av_hwdevice_iterate_types(AV_HWDEVICE_TYPE_NONE));
       type != AV_HWDEVICE_TYPE_NONE; type = av_hwdevice_iterate_types(type))
    ic_log(iscool::log::nature::info(), "iscool::video::decoder", "- {0}",
           av_hwdevice_get_type_name(type));
}

void iscool::video::detail::log_codec_details(const AVCodecContext& context,
                                              const AVCodec& codec)
{
  ic_log(iscool::log::nature::info(), "iscool::video::decoder",
         "Selected codec is '{0}', '{1}'.", codec.name, codec.long_name);

  int index(0);
  const AVCodecHWConfig* hw_config(avcodec_get_hw_config(&codec, index));

  while (hw_config != nullptr)
    {
      ic_log(iscool::log::nature::info(), "iscool::video::decoder",
             "- HW accel pix_fmt={0}, method={1}",
             av_get_pix_fmt_name(hw_config->pix_fmt), hw_config->methods);
      ++index;
      hw_config = avcodec_get_hw_config(&codec, index);
    }

  if (context.hwaccel == nullptr)
    ic_log(iscool::log::nature::info(), "iscool::video::decoder",
           "Hardware acceleration disabled.");
  else
    ic_log(iscool::log::nature::info(), "iscool::video::decoder",
           "Hardware acceleration enabled: '{0}'", context.hwaccel->name);
}

iscool::video::detail::decoder_thread::decoder_thread(
    decoder_state& shared_state, format_context_pointer format_context,
    codec_context_pointer codec_context, int video_stream_index,
    frame_ready_function frame_ready)
  : _format_context(std::move(format_context))
  , _codec_context(std::move(codec_context))
  , _video_stream_index(video_stream_index)
  , _frame_ready(std::move(frame_ready))
  , _shared_state(shared_state)
  , _current_frame(nullptr, &av_free)
  , _frame_dispatch_queue{ frame_pointer(nullptr, &av_free),
                           frame_pointer(nullptr, &av_free) }
  , _scale_context(nullptr, &sws_freeContext)
{}

void iscool::video::detail::decoder_thread::operator()()
{
  initialize();

  while (_frame_dispatch_queue_size != frame_queue_capacity)
    push_next_frame();

  _last_frame_dispatch_date = std::chrono::steady_clock::now();

  while (true)
    {
      std::unique_lock<std::mutex> lock(_shared_state.mutex);

      _shared_state.update_condition.wait(lock,
                                          [this]() -> bool
                                          {
                                            return _shared_state.need_update;
                                          });

      if (_shared_state.quit)
        break;

      _shared_state.need_update = false;
      lock.unlock();

      if (_frame_dispatch_queue_size != 0)
        pop_frame();

      if (_frame_dispatch_queue_size != frame_queue_capacity)
        push_next_frame();

      if (_frame_dispatch_queue_size != 0)
        dispatch_frame();
    }
}

void iscool::video::detail::decoder_thread::initialize()
{
  auto target_pixel_format(AV_PIX_FMT_RGB24);
  const int width(_codec_context->width);
  const int height(_codec_context->height);

  _current_frame = frame_pointer(av_frame_alloc(), &av_free);

  _frame_dispatch_queue[0] = frame_pointer(av_frame_alloc(), &av_free);
  _frame_dispatch_queue[1] = frame_pointer(av_frame_alloc(), &av_free);

  _frame_dispatch_pop_index = 0;
  _frame_dispatch_push_index = 0;
  _frame_dispatch_queue_size = 0;

  for (std::size_t i(0); i != frame_queue_capacity; ++i)
    {
      _frame_buffer[i].resize(
          av_image_get_buffer_size(target_pixel_format, width, height, 1));

      const frame_pointer& frame(_frame_dispatch_queue[i]);

      log_av_error(av_image_fill_arrays(
          frame->data, frame->linesize, _frame_buffer[i].data(),
          target_pixel_format, width, height, 1));
    }

  assert(_frame_dispatch_queue[0]->linesize[0] == width * 3);
  assert(_frame_dispatch_queue[1]->linesize[0] == width * 3);

  _scale_context = scale_context_pointer(
      sws_getContext(width, height, _codec_context->pix_fmt, width, height,
                     target_pixel_format, SWS_POINT, nullptr, nullptr,
                     nullptr),
      &sws_freeContext);

  _frame_duration = std::chrono::nanoseconds(
      std::size_t(1.0
                  / av_q2d(av_stream_get_r_frame_rate(
                      _format_context->streams[_video_stream_index]))
                  * 1000000000.0));
}

void iscool::video::detail::decoder_thread::push_next_frame()
{
  assert(_frame_dispatch_queue_size != frame_queue_capacity);

  AVPacket packet;
  bool stop(false);

  do
    {
      const std::unique_ptr<AVPacket, decltype(&av_packet_unref)>
          packet_releaser(&packet, &av_packet_unref);

      const int read_result(av_read_frame(_format_context.get(), &packet));

      if (read_result == AVERROR_EOF)
        reset_stream();
      else if (log_av_error(read_result))
        stop = true;
      else if (packet.stream_index == _video_stream_index)
        stop = decode_frame(packet);
    }
  while (!stop);

  ++_frame_dispatch_queue_size;
  ++_frame_dispatch_push_index;

  if (_frame_dispatch_push_index == frame_queue_capacity)
    _frame_dispatch_push_index = 0;
}

bool iscool::video::detail::decoder_thread::decode_frame(AVPacket& packet)
{
  int frame_finished(0);

  if (log_av_error(avcodec_decode_video2(_codec_context.get(),
                                         _current_frame.get(), &frame_finished,
                                         &packet)))
    return true;

  if (frame_finished == 0)
    return false;

  const frame_pointer& rgb_frame(
      _frame_dispatch_queue[_frame_dispatch_push_index]);

  sws_scale(_scale_context.get(),
            const_cast<uint8_t const**>(_current_frame->data),
            _current_frame->linesize, 0, _codec_context->height,
            rgb_frame->data, rgb_frame->linesize);

  return true;
}

void iscool::video::detail::decoder_thread::pop_frame()
{
  assert(_frame_dispatch_queue_size != 0);

  --_frame_dispatch_queue_size;
  ++_frame_dispatch_pop_index;

  if (_frame_dispatch_pop_index == frame_queue_capacity)
    _frame_dispatch_pop_index = 0;
}

void iscool::video::detail::decoder_thread::dispatch_frame()
{
  assert(_frame_dispatch_queue_size != 0);

  const auto now(std::chrono::steady_clock::now());
  const auto next_dispatch_date(_last_frame_dispatch_date + _frame_duration);

  if (next_dispatch_date > now)
    std::this_thread::sleep_for(next_dispatch_date - now);

  _last_frame_dispatch_date = std::chrono::steady_clock::now();

  std::uint8_t* const data(
      _frame_dispatch_queue[_frame_dispatch_pop_index]->data[0]);

  _frame_ready(data);
}

void iscool::video::detail::decoder_thread::reset_stream()
{
  avio_seek(_format_context->pb, 0, SEEK_SET);
  avformat_seek_file(_format_context.get(), _video_stream_index, 0, 0,
                     _format_context->streams[_video_stream_index]->duration,
                     0);
}
