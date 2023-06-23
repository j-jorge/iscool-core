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
#ifndef ISCOOL_RANDOM_RANDOMGENERATOR_H
#define ISCOOL_RANDOM_RANDOMGENERATOR_H

#include <iscool/random/rand.hpp>

#include <unordered_map>
#include <vector>

namespace iscool
{
  namespace random
  {
    template <typename Value>
    class random_generator
    {
    public:
      typedef unsigned int weight_type;

    public:
      random_generator();
      explicit random_generator(rand random);

      void set_random_source(rand random);

      void set_value_weight(Value value, weight_type weight);
      std::size_t get_cardinality() const;
      Value get_random();
      std::vector<Value> get_all_possible_values() const;

    private:
      struct entry
      {
        Value value;
        weight_type weight;
      };

      typedef std::vector<entry> value_weight_container;

    private:
      Value get_value_cut_at_weight_sum(weight_type weight_cut) const;

      void remove_value_if_any(Value value);
      void set_or_replace_value_weight(Value value, weight_type weight);
      typename value_weight_container::iterator
      find_entry_by_value(Value value);

    private:
      value_weight_container _weights;
      weight_type _weight_sum;
      rand _random;
    };
  }
}

#include <iscool/random/random_generator.tpp>

#endif
