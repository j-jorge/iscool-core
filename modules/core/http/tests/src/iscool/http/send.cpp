// SPDX-License-Identifier: Apache-2.0
#include <iscool/http/request.hpp>
#include <iscool/http/send.hpp>
#include <iscool/http/setup.hpp>

#include <iscool/schedule/manual_scheduler.hpp>
#include <iscool/schedule/setup.hpp>

#include <iscool/time/setup.hpp>

#include <iscool/none.hpp>
#include <iscool/optional.hpp>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

class send_mockup
{
public:
  send_mockup();
  ~send_mockup();

  iscool::signals::shared_connection_set get(const std::string& url);
  iscool::signals::shared_connection_set post(const std::string& url,
                                              std::vector<std::string> headers,
                                              std::string body);

  void dispatch_response(int status, const std::string& body);
  std::string result_string() const;
  std::string error_string() const;

public:
  std::vector<iscool::http::request> _requests;
  iscool::optional<std::vector<char>> _last_result;
  iscool::optional<int> _last_error_status;
  iscool::optional<std::vector<char>> _last_error;
  const char* _active_response_body;
};

send_mockup::send_mockup()
  : _active_response_body(nullptr)
{
  auto request_handler(
      [this](iscool::http::request request) -> void
        {
          _requests.push_back(std::move(request));
        });

  iscool::http::initialize(request_handler);
}

send_mockup::~send_mockup()
{
  iscool::http::finalize();
}

iscool::signals::shared_connection_set send_mockup::get(const std::string& url)
{
  auto on_result(
      [this](std::span<const char> result) -> void
        {
          // There should be no copy from the call site to this callback.
          EXPECT_EQ(_active_response_body, result.data());
          _last_error = iscool::none;
          _last_error_status = iscool::none;
          _last_result = std::vector(result.begin(), result.end());
        });

  auto on_error(
      [this](int status, std::span<const char> error) -> void
        {
          // There should be no copy from the call site to this callback.
          EXPECT_EQ(_active_response_body, error.data());
          _last_result = iscool::none;
          _last_error_status = status;
          _last_error = std::vector(error.begin(), error.end());
        });

  return iscool::http::get(url, on_result, on_error);
}

iscool::signals::shared_connection_set
send_mockup::post(const std::string& url, std::vector<std::string> headers,
                  std::string body)
{
  auto on_result(
      [this](std::span<const char> result) -> void
        {
          // There should be no copy from the call site to this callback.
          EXPECT_EQ(_active_response_body, result.data());
          _last_error = iscool::none;
          _last_result = std::vector(result.begin(), result.end());
        });

  auto on_error(
      [this](int status, std::span<const char> error) -> void
        {
          // There should be no copy from the call site to this callback.
          EXPECT_EQ(_active_response_body, error.data());
          _last_result = iscool::none;
          _last_error = std::vector(error.begin(), error.end());
        });

  return iscool::http::post(url, std::move(headers), std::move(body),
                            on_result, on_error);
}

void send_mockup::dispatch_response(int status, const std::string& body)
{
  assert(!_requests.empty());

  const iscool::http::request request(std::move(_requests.front()));
  _requests.erase(_requests.begin());

  const iscool::http::response response(
      status, std::span<const char>(body.begin(), body.end()));

  _active_response_body = response.body.data();
  request.result_handler(response);
  _active_response_body = nullptr;
}

std::string send_mockup::result_string() const
{
  assert(_last_result);
  return std::string(_last_result->begin(), _last_result->end());
}

std::string send_mockup::error_string() const
{
  assert(_last_error);
  return std::string(_last_error->begin(), _last_error->end());
}

TEST(iscool_http_send_test, get_error)
{
  send_mockup mockup;

  const std::string url("http://www.example.com");
  const iscool::signals::shared_connection_set connections(mockup.get(url));

  mockup.dispatch_response(404, "nope");

  ASSERT_TRUE(!!mockup._last_error_status);
  EXPECT_EQ(404, *mockup._last_error_status);

  ASSERT_TRUE(!!mockup._last_error);
  EXPECT_FALSE(!!mockup._last_result);
  EXPECT_EQ("nope", mockup.error_string());
}

TEST(iscool_http_send_test, disconnected_result)
{
  send_mockup mockup;

  const std::string url("http://www.example.info");
  iscool::signals::shared_connection_set connections(mockup.get(url));

  EXPECT_FALSE(connections.empty());
  connections.clear();

  mockup.dispatch_response(200, "yep");

  EXPECT_FALSE(mockup._last_result);
  EXPECT_FALSE(mockup._last_error);
}

TEST(iscool_http_send_test, disconnected_error)
{
  send_mockup mockup;

  const std::string url("http://www.example.net");
  iscool::signals::shared_connection_set connections(mockup.get(url));

  EXPECT_FALSE(connections.empty());
  connections.clear();

  mockup.dispatch_response(500, "nope");

  EXPECT_FALSE(mockup._last_result);
  EXPECT_FALSE(mockup._last_error);
}

TEST(iscool_http_send_test, one_hundred_get_requests)
{
  send_mockup mockup;

  const std::string url("http://www.example.org");
  iscool::signals::shared_connection_set connections;

  const std::size_t request_count(100);

  for (std::size_t i(0); i != request_count; ++i)
    connections.insert(mockup.get(boost::lexical_cast<std::string>(i)));

  std::size_t errors(0);
  std::size_t results(0);

  for (std::size_t i(0); i != request_count; ++i)
    if (i % 3 == 0)
      {
        mockup.dispatch_response(400, "");
        ASSERT_FALSE(!!mockup._last_result);
        ASSERT_TRUE(!!mockup._last_error);
        ++errors;
      }
    else
      {
        mockup.dispatch_response(200, "");
        ASSERT_TRUE(!!mockup._last_result);
        ASSERT_FALSE(!!mockup._last_error);
        ++results;
      }

  EXPECT_EQ(request_count, errors + results);
}

TEST(iscool_http_send_test, mixed_requests_and_results)
{
  send_mockup mockup;

  const std::string url("http://www.example.org");
  iscool::signals::shared_connection_set connections;

  const std::size_t request_count(10);
  std::vector<std::string> results;

  for (std::size_t i(0); i != request_count; ++i)
    {
      if (i <= 6)
        connections.insert(mockup.get(boost::lexical_cast<std::string>(i)));

      if (i >= 3)
        {
          const std::string response(boost::lexical_cast<std::string>(i - 3));

          mockup.dispatch_response(200, response);
          ASSERT_TRUE(!!mockup._last_result);
          ASSERT_FALSE(!!mockup._last_error);
          results.push_back(mockup.result_string());
        }
    }

  const std::vector<std::string> expected_results(
      { "0", "1", "2", "3", "4", "5", "6" });
  EXPECT_EQ(expected_results, results);
}

TEST(iscool_http_send_test, post_result)
{
  send_mockup mockup;

  const std::string url("http://www.example.org");
  const std::vector<std::string> headers({ "head 1", "more", "head 24" });
  const std::string body("the body");

  const iscool::signals::shared_connection_set connections(
      mockup.post(url, headers, body));

  ASSERT_EQ(1ull, mockup._requests.size());
  EXPECT_EQ(iscool::http::request::type::post,
            mockup._requests[0].request_type);
  EXPECT_EQ(url, mockup._requests[0].url);
  EXPECT_EQ(body, mockup._requests[0].body);
  EXPECT_EQ(headers, mockup._requests[0].headers);

  mockup.dispatch_response(200, "yep");

  ASSERT_TRUE(!!mockup._last_result);
  EXPECT_FALSE(!!mockup._last_error);
  EXPECT_EQ("yep", mockup.result_string());
}

TEST(iscool_http_send_test, post_error)
{
  send_mockup mockup;

  const std::string url("http://www.example.org");
  const std::vector<std::string> headers({ "head 1", "more", "head 24" });
  const std::string body("the body");

  const iscool::signals::shared_connection_set connections(
      mockup.post(url, headers, body));

  mockup.dispatch_response(300, "nope");

  ASSERT_FALSE(!!mockup._last_result);
  EXPECT_TRUE(!!mockup._last_error);
  EXPECT_EQ("nope", mockup.error_string());
}

TEST(iscool_http_send_test, send_in_response)
{
  std::string second_result_value;

  auto second_result(
      [&second_result_value](std::span<const char> result) -> void
        {
          second_result_value = std::string(result.begin(), result.end());
        });

  auto second_error(
      [](int status, std::span<const char> error) -> void
        {
          EXPECT_TRUE(false);
        });

  iscool::signals::shared_connection_set connections;

  std::string first_result_value;
  auto first_result(
      [&connections, &first_result_value, second_result,
       second_error](std::span<const char> result) -> void
        {
          first_result_value = std::string(result.begin(), result.end());
          connections.insert(
              iscool::http::get("b", second_result, second_error));
        });

  auto first_error(
      [this](int status, std::span<const char> error) -> void
        {
          EXPECT_TRUE(false);
        });

  std::vector<iscool::http::request> requests;

  auto mockup(
      [&requests](const iscool::http::request& r) -> void
        {
          requests.push_back(r);
        });

  iscool::http::initialize(mockup);
  connections = iscool::http::get("a", first_result, first_error);

  EXPECT_EQ(1ull, requests.size());
  const char first_body[] = { '1' };
  requests[0].result_handler(iscool::http::response(200, first_body));
  EXPECT_EQ("1", first_result_value);

  EXPECT_EQ(2ull, requests.size());
  const char second_body[] = { '2' };
  requests[1].result_handler(iscool::http::response(200, second_body));
  EXPECT_EQ("2", second_result_value);

  iscool::http::finalize();
}

class iscool_http_send_retry_test : public testing::Test
{
public:
  iscool_http_send_retry_test()
    : m_current_date{}
    , m_time_source_initializer(
          [this]() -> std::chrono::nanoseconds
            {
              return m_current_date;
            },
          [this]() -> std::chrono::nanoseconds
            {
              return m_current_date;
            })
    , m_scheduler_initializer(m_scheduler.get_delayed_call_delegate())
  {}

protected:
  std::chrono::nanoseconds m_current_date;
  iscool::time::scoped_time_source_delegate m_time_source_initializer;
  iscool::schedule::manual_scheduler m_scheduler;
  iscool::schedule::scoped_scheduler_delegate m_scheduler_initializer;
};

TEST_F(iscool_http_send_retry_test, retry_on_error)
{
  send_mockup mockup;

  const std::string url("http://www.example.com");
  const iscool::signals::shared_connection_set connections(mockup.get(url));

  for (int i = 0; i != 5; ++i)
    {
      mockup.dispatch_response(408, "retry");

      EXPECT_FALSE(!!mockup._last_error_status);
      EXPECT_FALSE(!!mockup._last_error);
      EXPECT_FALSE(!!mockup._last_result);

      const std::chrono::seconds d(i);
      m_current_date += d;
      m_scheduler.update_interval(d);
    }

  mockup.dispatch_response(408, "retry");

  ASSERT_TRUE(!!mockup._last_error_status);
  EXPECT_EQ(408, *mockup._last_error_status);

  ASSERT_TRUE(!!mockup._last_error);
  EXPECT_FALSE(!!mockup._last_result);

  EXPECT_EQ("retry", mockup.error_string());
}
