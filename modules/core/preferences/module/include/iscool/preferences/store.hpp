// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/preferences/property_map.hpp>
#include <iscool/schedule/scoped_connection.hpp>

#include <chrono>
#include <functional>
#include <vector>

namespace iscool::preferences
{
  class store
  {
  private:
    typedef std::function<void(const property_map&)> save_function;

  public:
    store(const std::chrono::milliseconds& flush_delay,
          const property_map& initial_values,
          const save_function& save_delegate);

    store(const store&) = delete;
    store& operator=(const store&) = delete;

    template <typename T>
    void set_value(const std::string& key, const T& value);

    template <typename T>
    T get_value(const std::string& key, const T& default_value) const;

    bool is_dirty() const;
    void flush();
    void confirm_save();
    void save_error();

    std::vector<std::string> get_keys() const;

    const property_map& get_properties() const;
    void reset(const property_map& values);

  private:
    void abort_save();
    void schedule_save();
    void save();

  private:
    std::chrono::milliseconds _flush_delay;
    property_map _preferences;
    property_map _dirty;
    property_map _pending_changes;
    iscool::schedule::scoped_connection _save_connection;
    save_function _save_delegate;
  };
}
