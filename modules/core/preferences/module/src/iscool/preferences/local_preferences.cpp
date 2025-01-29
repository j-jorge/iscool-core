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
#include <iscool/preferences/local_preferences.hpp>

#include <iscool/files/copy_file.hpp>
#include <iscool/files/delete_file.hpp>
#include <iscool/files/file_exists.hpp>
#include <iscool/files/rename_file.hpp>
#include <iscool/json/from_file.hpp>
#include <iscool/json/write_to_stream.hpp>
#include <iscool/log/log.hpp>
#include <iscool/log/nature/error.hpp>
#include <iscool/log/nature/info.hpp>
#include <iscool/log/nature/warning.hpp>
#include <iscool/memory/make_unique.hpp>
#include <iscool/preferences/detail/local_preferences_from_json.hpp>
#include <iscool/preferences/log_context.hpp>
#include <iscool/preferences/property_map_to_json.hpp>
#include <iscool/preferences/store.impl.tpp>
#include <iscool/signals/implement_signal.hpp>

#include <format>
#include <fstream>

namespace iscool
{
  namespace preferences
  {
    namespace detail
    {
      class backup_thread
      {
      public:
        backup_thread(backup_state& shared_state,
                      const std::string& original_file_path,
                      const std::string& backup_extension_format,
                      std::size_t backup_count);

        void operator()();

      private:
        bool create_temporary_backup() const;
        void validate_backup() const;
        void roll_backups() const;

      private:
        const std::string& _original_file_path;
        const std::string& _backup_extension_format;
        const std::string _temporary_file_path;
        const std::size_t _backup_max_count;

        backup_state& _shared_state;
      };

      static std::string
      get_backup_file_path(const std::string& file_path,
                           const std::string& extension_format,
                           std::size_t index);
      static Json::Value
      load_preferences_file(const std::string& file_path,
                            const std::string& backup_extension_format,
                            std::size_t backup_max_count);
      static Json::Value
      load_backup_file(const std::string& file_path,
                       const std::string& backup_extension_format,
                       std::size_t backup_max_count);
    }
  }
}

IMPLEMENT_SIGNAL(iscool::preferences::local_preferences, saving, _saving);

iscool::preferences::local_preferences::local_preferences(
    const property_map& values)
  : _file_path("")
  , _backup_extension_format("")
  , _store(std::chrono::seconds::zero(), values,
           std::bind(&local_preferences::save, this, std::placeholders::_1))
{
  property_map_to_json visitor(_values);
  values.visit(visitor);
}

iscool::preferences::local_preferences::local_preferences(
    const std::chrono::milliseconds& flush_delay, const std::string& file_path)
  : local_preferences(flush_delay, file_path, "", 0)
{}

iscool::preferences::local_preferences::local_preferences(
    const std::chrono::milliseconds& flush_delay, const std::string& file_path,
    const std::string& backup_extension_format, std::size_t backup_count)
  : _file_path(file_path)
  , _backup_extension_format(backup_extension_format)
  , _values(detail::load_preferences_file(file_path, backup_extension_format,
                                          backup_count))
  , _store(flush_delay, detail::local_preferences_from_json(_values),
           std::bind(&local_preferences::save, this, std::placeholders::_1))
{
  if (backup_count == 0)
    return;

  _backup_thread_state.quit = false;
  _backup_thread_state.available = false;

  _backup_thread = std::thread(
      detail::backup_thread(_backup_thread_state, _file_path,
                            _backup_extension_format, backup_count));
}

iscool::preferences::local_preferences::~local_preferences()
{
  {
    const std::lock_guard<std::mutex> lock(_backup_thread_state.mutex);
    _backup_thread_state.quit = true;
    _backup_thread_state.available = true;
  }

  _backup_thread_state.ready_condition.notify_one();

  if (_backup_thread.joinable())
    _backup_thread.join();
}

void iscool::preferences::local_preferences::flush()
{
  if (_store.is_dirty())
    _store.flush();
}

std::int64_t iscool::preferences::local_preferences::get_value(
    const std::string& key, std::int64_t default_value) const
{
  return _store.get_value(key, default_value);
}

void iscool::preferences::local_preferences::set_value(const std::string& key,
                                                       std::int64_t value)
{
  _store.set_value(key, value);
}

bool iscool::preferences::local_preferences::get_value(
    const std::string& key, bool default_value) const
{
  return _store.get_value(key, default_value);
}

void iscool::preferences::local_preferences::set_value(const std::string& key,
                                                       bool value)
{
  _store.set_value(key, value);
}

std::string iscool::preferences::local_preferences::get_value(
    const std::string& key, const std::string& default_value) const
{
  return _store.get_value(key, default_value);
}

void iscool::preferences::local_preferences::set_value(
    const std::string& key, const std::string& value)
{
  _store.set_value(key, value);
}

std::vector<std::string>
iscool::preferences::local_preferences::get_keys() const
{
  return _store.get_keys();
}

const iscool::preferences::property_map&
iscool::preferences::local_preferences::get_properties() const
{
  return _store.get_properties();
}

void iscool::preferences::local_preferences::save(property_map dirty)
{
  update_fields(dirty);
  _saving(dirty);
}

void iscool::preferences::local_preferences::update_fields(
    const property_map& dirty)
{
  property_map_to_json visitor(_values);
  dirty.visit(visitor);

  if (save_to_file())
    _store.confirm_save();
  else
    _store.save_error();
}

bool iscool::preferences::local_preferences::save_to_file()
{
  if (_file_path.empty())
    return true;

  std::unique_lock<std::mutex> lock(_backup_thread_state.mutex);
  std::ofstream file(_file_path);

  if (iscool::json::write_to_stream(file, _values) && file)
    {
      file.close();
      _backup_thread_state.available = true;

      lock.unlock();
      _backup_thread_state.ready_condition.notify_one();

      return true;
    }
  else
    {
      ic_log(iscool::log::nature::error(), log_context(),
             "Could not save the local preferences");
      return false;
    }
}

iscool::preferences::detail::backup_thread::backup_thread(
    backup_state& shared_state, const std::string& original_file_path,
    const std::string& backup_extension_format, std::size_t backup_count)
  : _original_file_path(original_file_path)
  , _backup_extension_format(backup_extension_format)
  , _temporary_file_path(
        get_backup_file_path(original_file_path, backup_extension_format, 0))
  , _backup_max_count(backup_count)
  , _shared_state(shared_state)
{
  assert(_backup_max_count > 0);
}

void iscool::preferences::detail::backup_thread::operator()()
{
  while (true)
    {
      std::unique_lock<std::mutex> lock(_shared_state.mutex);

      _shared_state.ready_condition.wait(lock,
                                         [this]() -> bool
                                         {
                                           return _shared_state.available;
                                         });

      if (_shared_state.quit)
        break;

      _shared_state.available = false;

      const bool copied(create_temporary_backup());

      lock.unlock();

      if (copied)
        validate_backup();
    }
}

bool iscool::preferences::detail::backup_thread::create_temporary_backup()
    const
{
  if (iscool::files::file_exists(_temporary_file_path))
    {
      ic_log(iscool::log::nature::warning(), log_context(),
             "Deleting already present temporary backup file.");
      iscool::files::delete_file(_temporary_file_path);
    }

  return iscool::files::copy_file(_original_file_path, _temporary_file_path);
}

void iscool::preferences::detail::backup_thread::validate_backup() const
{
  const Json::Value value(iscool::json::from_file(_temporary_file_path));

  if (value.isNull())
    return;

  roll_backups();

  const std::string backup_file_path(
      get_backup_file_path(_original_file_path, _backup_extension_format, 1));

  iscool::files::rename_file(_temporary_file_path, backup_file_path);
}

void iscool::preferences::detail::backup_thread::roll_backups() const
{
  assert(_backup_max_count > 0);

  std::string to(get_backup_file_path(
      _original_file_path, _backup_extension_format, _backup_max_count));

  for (std::size_t index(_backup_max_count - 1); index != 0; --index)
    {
      std::string from(get_backup_file_path(_original_file_path,
                                            _backup_extension_format, index));

      if (!iscool::files::file_exists(from))
        break;

      iscool::files::rename_file(from, to);
      to = std::move(from);
    }
}

std::string iscool::preferences::detail::get_backup_file_path(
    const std::string& file_path, const std::string& extension_format,
    std::size_t index)
{
  return file_path
         + std::vformat(extension_format, std::make_format_args(index));
}

Json::Value iscool::preferences::detail::load_preferences_file(
    const std::string& file_path, const std::string& backup_extension_format,
    std::size_t backup_max_count)
{
  if (!iscool::files::file_exists(file_path))
    return Json::Value(Json::objectValue);

  Json::Value result(iscool::json::from_file(file_path));

  if (!result.isNull())
    return result;

  ic_log(iscool::log::nature::error(), log_context(),
         "Could not load local preferences from '{}'. Trying the backups",
         file_path);

  return load_backup_file(file_path, backup_extension_format,
                          backup_max_count);
}

Json::Value iscool::preferences::detail::load_backup_file(
    const std::string& file_path, const std::string& backup_extension_format,
    std::size_t backup_max_count)
{
  Json::Value result;

  for (std::size_t index(1); (index <= backup_max_count) && result.isNull();
       ++index)
    {
      const std::string full_path(
          get_backup_file_path(file_path, backup_extension_format, index));

      if (!iscool::files::file_exists(full_path))
        return result;

      ic_log(iscool::log::nature::info(), log_context(),
             "Trying backup file '{}'", full_path);

      result = iscool::json::from_file(full_path);
    }

  if (result.isNull())
    ic_log(iscool::log::nature::error(), log_context(),
           "No valid backup file found for '{}'", file_path);

  return result;
}
