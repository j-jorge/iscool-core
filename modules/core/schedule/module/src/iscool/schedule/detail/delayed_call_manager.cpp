// SPDX-License-Identifier: Apache-2.0
#include <iscool/schedule/detail/delayed_call_manager.hpp>

#include <iscool/time/monotonic_now.hpp>

#include <iscool/log/log.hpp>
#include <iscool/log/nature/warning.hpp>
#include <iscool/schedule/detail/call_later.hpp>
#include <iscool/signals/signal.impl.tpp>

iscool::schedule::detail::delayed_call_manager::delayed_call_manager(
    std::size_t pool_size)
  : _short_call_cumulated("delayed_call_manager::short_call_cumulated")
  , _short_call_non_cumulated("delayed_call_manager::short_call_non_cumulated")
  , _tmp_signals(pool_size)
  , _pool(pool_size)
  , _client_guard(false)
  , _in_cumulated_loop(false)
{}

iscool::schedule::connection
iscool::schedule::detail::delayed_call_manager::schedule_call(
    std::function<void()> f, duration delay)
{
  assert(delay.count() > 0);
  return schedule_delayed(std::move(f), delay);
}

iscool::schedule::connection
iscool::schedule::detail::delayed_call_manager::schedule_call(
    std::function<void()> f, short_call_policy policy)
{
  if (policy == short_call_policy::cumulated)
    return schedule_cumulated(std::move(f));

  assert(policy == short_call_policy::non_cumulated);
  return schedule_non_cumulated(std::move(f));
}

bool iscool::schedule::detail::delayed_call_manager::connected(
    const connection& c)
{
  const std::unique_lock<std::recursive_mutex> lock(_mutex);
  return c._signal_connection.connected();
}

void iscool::schedule::detail::delayed_call_manager::disconnect(
    const connection& c)
{
  const std::unique_lock<std::recursive_mutex> lock(_mutex);
  c._signal_connection.disconnect();
}

void iscool::schedule::detail::delayed_call_manager::clear()
{
  std::unique_lock<std::recursive_mutex> lock(_mutex);

  _short_call_cumulated.disconnect_all_slots();
  _short_call_non_cumulated.disconnect_all_slots();
  _pool.clear();
}

iscool::schedule::connection
iscool::schedule::detail::delayed_call_manager::schedule_cumulated(
    std::function<void()> f)
{
  std::unique_lock<std::recursive_mutex> lock(_mutex);

  if (!_in_cumulated_loop && _short_call_cumulated.empty())
    schedule_client_cumulated();

  return connection(_short_call_cumulated.connect(std::move(f)));
}

iscool::schedule::connection
iscool::schedule::detail::delayed_call_manager::schedule_non_cumulated(
    std::function<void()> f)
{
  std::unique_lock<std::recursive_mutex> lock(_mutex);

  if (_short_call_non_cumulated.empty())
    schedule_client_non_cumulated();

  return connection(_short_call_non_cumulated.connect(std::move(f)));
}

iscool::schedule::connection
iscool::schedule::detail::delayed_call_manager::schedule_delayed(
    std::function<void()> f, duration delay)
{
  std::unique_lock<std::recursive_mutex> lock(_mutex);

  assert(delay.count() > 0);

  const auto slot(_pool.pick_available());
  connection result(slot.value->connect(std::move(f)));

  schedule_client(slot.id, delay);

  return result;
}

void iscool::schedule::detail::delayed_call_manager::schedule_client(
    std::size_t id, duration delay)
{
  assert(detail::call_later);

  detail::call_later(
      [this, id, d = time::monotonic_now<duration>() + delay]() -> void
      {
        trigger(id, d);
      },
      delay);
}

void iscool::schedule::detail::delayed_call_manager::
    schedule_client_cumulated()
{
  assert(!_client_guard);
  _client_guard = true;

  assert(detail::call_later);

  detail::call_later(
      [this]() -> void
      {
        trigger_cumulated();
      },
      duration::zero());

  _client_guard = false;
}

void iscool::schedule::detail::delayed_call_manager::
    schedule_client_non_cumulated()
{
  assert(_short_call_non_cumulated.empty());
  assert(!_client_guard);
  _client_guard = true;

  assert(detail::call_later);

  detail::call_later(
      [this]() -> void
      {
        trigger_non_cumulated();
      },
      duration::zero());

  _client_guard = false;
}

void iscool::schedule::detail::delayed_call_manager::trigger(
    std::size_t id, duration expected_date)
{
  const duration now(time::monotonic_now<duration>());

  if (expected_date > now)
    {
      const duration remaining(expected_date - now);
      schedule_client(id, remaining);
    }
  else
    {
      pool_type::slot slot;

      {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        slot = _tmp_signals.pick_available();
        slot.value->swap(_pool.get(id));
        _pool.release(id);
      }

      (*slot.value)();
      {
        std::unique_lock<std::recursive_mutex> lock(_mutex);
        _tmp_signals.release(slot.id);
      }

      trigger_cumulated();
    }
}

void iscool::schedule::detail::delayed_call_manager::trigger_cumulated()
{
  _mutex.lock();

  assert(!_client_guard);
  assert(!_in_cumulated_loop);

  _in_cumulated_loop = true;

  std::size_t limit(10);

  do
    {
      --limit;

      const pool_type::slot slot = _tmp_signals.pick_available();
      slot.value->swap(_short_call_cumulated);

      _mutex.unlock();
      (*slot.value)();
      _mutex.lock();

      _tmp_signals.release(slot.id);
    }
  while ((limit != 0) && !_short_call_cumulated.empty());

  _in_cumulated_loop = false;

  if (!_short_call_cumulated.empty())
    {
      ic_log(iscool::log::nature::warning(), "Scheduler",
             "Too many recursively cumulated calls.");

      schedule_client_cumulated();
    }

  _mutex.unlock();
}

void iscool::schedule::detail::delayed_call_manager::trigger_non_cumulated()
{
  pool_type::slot slot;

  {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    assert(!_client_guard);
    slot = _tmp_signals.pick_available();
    slot.value->swap(_short_call_non_cumulated);
  }

  (*slot.value)();

  {
    std::unique_lock<std::recursive_mutex> lock(_mutex);
    _tmp_signals.release(slot.id);
  }
}
