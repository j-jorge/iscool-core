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
#include <algorithm>

template <typename Value>
iscool::random::random_generator<Value>::random_generator()
  : random_generator<Value>(rand())
{}

template <typename Value>
iscool::random::random_generator<Value>::random_generator(rand random)
  : _weight_sum{ 0 }
  , _random{ random }

{}

template <typename Value>
void iscool::random::random_generator<Value>::set_random_source(rand random)
{
  _random = random;
}

template <typename Value>
void iscool::random::random_generator<Value>::set_value_weight(
    Value value, weight_type weight)
{
  if (weight == weight_type(0))
    remove_value_if_any(value);
  else
    set_or_replace_value_weight(value, weight);
}

template <typename Value>
std::size_t iscool::random::random_generator<Value>::get_cardinality() const
{
  return _weights.size();
}

template <typename Value>
Value iscool::random::random_generator<Value>::get_random()
{
  if (_weights.empty())
    throw std::out_of_range("There is no value among which to select.");

  const weight_type selected_weight(
      _random.random<weight_type>(1, _weight_sum));

  return get_value_cut_at_weight_sum(selected_weight);
}

template <typename Value>
std::vector<Value>
iscool::random::random_generator<Value>::get_all_possible_values() const
{
  std::vector<Value> result;
  result.reserve(_weights.size());

  for (auto entry : _weights)
    result.push_back(entry.value);

  return result;
}

template <typename Value>
Value iscool::random::random_generator<Value>::get_value_cut_at_weight_sum(
    weight_type weight_cut) const
{
  weight_type weight_sum(0);

  for (auto entry : _weights)
    {
      weight_sum += entry.weight;

      if (weight_sum >= weight_cut)
        return entry.value;
    }

  throw std::out_of_range("Weight is outside acceptable range.");
}

template <typename Value>
void iscool::random::random_generator<Value>::remove_value_if_any(Value value)
{
  const typename value_weight_container::iterator it{ find_entry_by_value(
      value) };

  if (it == _weights.end())
    return;

  _weight_sum -= it->weight;
  _weights.erase(it);
}

template <typename Value>
void iscool::random::random_generator<Value>::set_or_replace_value_weight(
    Value value, weight_type weight)
{
  const typename value_weight_container::iterator it{ find_entry_by_value(
      value) };

  if (it == _weights.end())
    _weights.insert(it, entry{ value, weight });
  else
    {
      _weight_sum -= it->weight;
      it->weight = weight;
    }

  _weight_sum += weight;
}

template <typename Value>
typename iscool::random::random_generator<
    Value>::value_weight_container::iterator
iscool::random::random_generator<Value>::find_entry_by_value(Value value)
{
  auto is_searched_value(
      [value](entry entry) -> bool
      {
        return entry.value == value;
      });

  return std::find_if(_weights.begin(), _weights.end(), is_searched_value);
}
