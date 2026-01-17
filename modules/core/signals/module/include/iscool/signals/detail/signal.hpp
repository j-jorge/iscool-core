// SPDX-License-Identifier: Apache-2.0
#pragma once

#include <iscool/signals/connection.hpp>
#include <iscool/signals/detail/slot.hpp>

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <type_traits>
#include <vector>

namespace iscool
{
  namespace signals
  {
    namespace detail
    {
      template <typename Signature>
      class signal
      {
      public:
        typedef void result_type;

      public:
        signal();
        signal(const signal<Signature>&) = delete;
        signal(signal<Signature>&&) = delete;
        ~signal();

        signal<Signature>& operator=(const signal<Signature>&) = delete;

        signal<Signature>& operator=(signal<Signature>&&) = delete;

        connection connect(std::function<Signature> f);

        template <typename... Arg>
        void operator()(Arg&&... arg) const;

        bool empty() const;
        void disconnect_all_slots();
        std::size_t num_slots() const;
        void swap(signal<Signature>& that) noexcept;

      private:
        struct internal_slot : public slot
        {
          explicit internal_slot(std::function<Signature> f);
          ~internal_slot();

          std::function<Signature> callback;
        };

        typedef std::shared_ptr<internal_slot> shared_slot_ptr;
        typedef std::vector<shared_slot_ptr> shared_slot_ptr_vector;

        using slot_storage_type =
            std::conditional_t<(sizeof(shared_slot_ptr)
                                > sizeof(shared_slot_ptr_vector)),
                               shared_slot_ptr, shared_slot_ptr_vector>;

        enum class storage_kind : char
        {
          none,
          pointer,
          vector
        };

      private:
        shared_slot_ptr& get_storage_as_pointer();
        const shared_slot_ptr& get_storage_as_pointer() const;
        shared_slot_ptr_vector& get_storage_as_vector();
        const shared_slot_ptr_vector& get_storage_as_vector() const;

        void swap_pointer_vector(signal<Signature>& that) noexcept;
        void swap_pointer_none(signal<Signature>& that) noexcept;
        void swap_vector_none(signal<Signature>& that) noexcept;

      private:
        alignas(slot_storage_type) std::byte
            _slot_storage[sizeof(slot_storage_type)];

        storage_kind _storage_kind;
      };
    }
  }
}
