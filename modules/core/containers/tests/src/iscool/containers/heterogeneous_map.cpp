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
#include "iscool/containers/heterogeneous_map.h"
#include "iscool/containers/heterogeneous_map.impl.tpp"

#include "iscool/optional.impl.tpp"

#include <functional>

#include <gtest/gtest.h>

TEST(iscool_containers_heterogeneous_map, string_int)
{
  iscool::containers::heterogeneous_map<std::string, int> map;

  EXPECT_TRUE(map.empty());
  map.set("key", 24);
  EXPECT_FALSE(map.empty());

  map.set("key2", 42);

  iscool::optional<int> value(map.get<int>("key"));
  EXPECT_TRUE(!!value);
  EXPECT_EQ(24, *value);

  EXPECT_FALSE(!!map.get<int>("nope"));

  EXPECT_TRUE(map.has<int>("key"));
  EXPECT_TRUE(map.has<int>("key2"));
  EXPECT_FALSE(map.has<int>("nope"));

  map.erase<int>("key2");
  EXPECT_FALSE(map.has<int>("key2"));

  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST(iscool_containers_heterogeneous_map, string_int_visit)
{
  iscool::containers::heterogeneous_map<std::string, int> map;
  map.set("key", 24);
  map.set("other", 48);

  std::map<std::string, int> visited;
  map.visit(
      [&visited](const std::string& key, int value) -> void
      {
        visited[key] = value;
      });

  EXPECT_EQ(std::size_t(2), visited.size());
  EXPECT_EQ(24, visited["key"]);
  EXPECT_EQ(48, visited["other"]);
}

TEST(iscool_containers_heterogeneous_map, string_int_swap)
{
  iscool::containers::heterogeneous_map<std::string, int> map_1;
  map_1.set("a", 24);
  map_1.set("b", 48);

  iscool::containers::heterogeneous_map<std::string, int> map_2;
  map_2.set("a", 2);
  map_2.set("c", 4);

  map_1.swap(map_2);

  EXPECT_EQ(2, *map_1.get<int>("a"));
  EXPECT_EQ(4, *map_1.get<int>("c"));

  EXPECT_EQ(24, *map_2.get<int>("a"));
  EXPECT_EQ(48, *map_2.get<int>("b"));
}

TEST(iscool_containers_heterogeneous_map, string_int_copy)
{
  iscool::containers::heterogeneous_map<std::string, int> map;
  map.set("a", 24);
  map.set("b", 48);

  const iscool::containers::heterogeneous_map<std::string, int> copy(map);

  EXPECT_EQ(24, *map.get<int>("a"));
  EXPECT_EQ(48, *map.get<int>("b"));

  EXPECT_EQ(24, *copy.get<int>("a"));
  EXPECT_EQ(48, *copy.get<int>("b"));
}

TEST(iscool_containers_heterogeneous_map, string_int_move)
{
  iscool::containers::heterogeneous_map<std::string, int> map;
  map.set("a", 24);
  map.set("b", 48);

  const iscool::containers::heterogeneous_map<std::string, int> moved(
      std::move(map));

  EXPECT_TRUE(map.empty());

  EXPECT_EQ(24, *moved.get<int>("a"));
  EXPECT_EQ(48, *moved.get<int>("b"));
}

TEST(iscool_containers_heterogeneous_map, size_t_float)
{
  iscool::containers::heterogeneous_map<std::size_t, float> map;

  EXPECT_TRUE(map.empty());
  map.set(400, 24.f);
  map.set(800, 42.f);
  EXPECT_FALSE(map.empty());

  iscool::optional<float> value(map.get<float>(400));
  EXPECT_TRUE(!!value);
  EXPECT_EQ(24, *value);

  EXPECT_FALSE(!!map.get<float>(900));

  EXPECT_TRUE(map.has<float>(400));
  EXPECT_TRUE(map.has<float>(800));
  EXPECT_FALSE(map.has<float>(900));

  map.erase<float>(800);
  EXPECT_FALSE(map.has<float>(800));

  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST(iscool_containers_heterogeneous_map, size_t_float_visit)
{
  iscool::containers::heterogeneous_map<std::size_t, float> map;
  map.set(400, 24.f);
  map.set(600, 48.f);

  std::map<std::size_t, float> visited;
  map.visit(
      [&visited](const std::size_t& key, float value) -> void
      {
        visited[key] = value;
      });

  EXPECT_EQ(std::size_t(2), visited.size());
  EXPECT_EQ(24, visited[400]);
  EXPECT_EQ(48, visited[600]);
}

TEST(iscool_containers_heterogeneous_map, size_t_float_swap)
{
  iscool::containers::heterogeneous_map<std::size_t, float> map_1;
  map_1.set(1, 24.f);
  map_1.set(2, 48.f);

  iscool::containers::heterogeneous_map<std::size_t, float> map_2;
  map_2.set(1, 2.f);
  map_2.set(3, 4.f);

  map_1.swap(map_2);

  EXPECT_EQ(2, *map_1.get<float>(1));
  EXPECT_EQ(4, *map_1.get<float>(3));

  EXPECT_EQ(24, *map_2.get<float>(1));
  EXPECT_EQ(48, *map_2.get<float>(2));
}

TEST(iscool_containers_heterogeneous_map, size_t_float_copy)
{
  iscool::containers::heterogeneous_map<std::size_t, float> map;
  map.set(1, 24.f);
  map.set(2, 48.f);

  const iscool::containers::heterogeneous_map<std::size_t, float> copy(map);

  EXPECT_EQ(24, *map.get<float>(1));
  EXPECT_EQ(48, *map.get<float>(2));

  EXPECT_EQ(24, *copy.get<float>(1));
  EXPECT_EQ(48, *copy.get<float>(2));
}

TEST(iscool_containers_heterogeneous_map, size_t_float_move)
{
  iscool::containers::heterogeneous_map<std::size_t, float> map;
  map.set(1, 24.f);
  map.set(2, 48.f);

  const iscool::containers::heterogeneous_map<std::size_t, float> moved(
      std::move(map));

  EXPECT_TRUE(map.empty());

  EXPECT_EQ(24, *moved.get<float>(1));
  EXPECT_EQ(48, *moved.get<float>(2));
}

TEST(iscool_containers_heterogeneous_map, string_short_string_char)
{
  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map;

  EXPECT_TRUE(map.empty());
  map.set<short>("short", 24);
  map.set("string", std::string("ssss"));
  map.set("char", 'a');
  EXPECT_FALSE(map.empty());

  iscool::optional<short> short_value(map.get<short>("short"));
  EXPECT_TRUE(!!short_value);
  EXPECT_EQ(24, *short_value);

  iscool::optional<std::string> string_value(map.get<std::string>("string"));
  EXPECT_TRUE(!!string_value);
  EXPECT_EQ("ssss", *string_value);

  iscool::optional<char> char_value(map.get<char>("char"));
  EXPECT_TRUE(!!char_value);
  EXPECT_EQ('a', *char_value);

  EXPECT_FALSE(!!map.get<short>("string"));
  EXPECT_FALSE(!!map.get<short>("char"));
  EXPECT_FALSE(!!map.get<std::string>("short"));
  EXPECT_FALSE(!!map.get<std::string>("char"));
  EXPECT_FALSE(!!map.get<char>("short"));
  EXPECT_FALSE(!!map.get<char>("string"));

  EXPECT_TRUE(map.has<short>("short"));
  EXPECT_TRUE(map.has<std::string>("string"));
  EXPECT_TRUE(map.has<char>("char"));

  EXPECT_FALSE(map.has<std::string>("short"));
  EXPECT_FALSE(map.has<std::string>("char"));
  EXPECT_FALSE(map.has<char>("short"));
  EXPECT_FALSE(map.has<char>("string"));
  EXPECT_FALSE(map.has<short>("string"));
  EXPECT_FALSE(map.has<short>("char"));

  map.erase<char>("char");
  EXPECT_FALSE(map.has<char>("char"));

  map.clear();
  EXPECT_TRUE(map.empty());
}

TEST(iscool_containers_heterogeneous_map, string_short_string_char_visit)
{
  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map;

  map.set<short>("short", 24);
  map.set("string", std::string("ssss"));
  map.set("restring", std::string("SSSS"));
  map.set("char", 'a');

  struct visitor
  {
    void operator()(const std::string key, short value)
    {
      shorts[key] = value;
    }

    void operator()(const std::string key, const std::string& value)
    {
      strings[key] = value;
    }

    void operator()(const std::string key, char value)
    {
      chars[key] = value;
    }

    std::map<std::string, short> shorts;
    std::map<std::string, std::string> strings;
    std::map<std::string, char> chars;
  };

  visitor visited;
  map.visit(visited);

  EXPECT_EQ(std::size_t(1), visited.shorts.size());
  EXPECT_EQ(24, visited.shorts["short"]);

  EXPECT_EQ(std::size_t(2), visited.strings.size());
  EXPECT_EQ("ssss", visited.strings["string"]);
  EXPECT_EQ("SSSS", visited.strings["restring"]);

  EXPECT_EQ(std::size_t(1), visited.chars.size());
  EXPECT_EQ('a', visited.chars["char"]);
}

TEST(iscool_containers_heterogeneous_map, string_short_string_char_swap)
{
  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map_1;

  map_1.set("a", short(24));
  map_1.set("b", 'b');

  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map_2;

  map_2.set("a", std::string("string"));
  map_2.set("c", short(12));

  map_1.swap(map_2);

  EXPECT_EQ("string", *map_1.get<std::string>("a"));
  EXPECT_EQ(12, *map_1.get<short>("c"));
  EXPECT_FALSE(map_1.has<char>("b"));

  EXPECT_EQ(24, *map_2.get<short>("a"));
  EXPECT_EQ('b', *map_2.get<char>("b"));
  EXPECT_FALSE(map_2.has<short>("c"));
}

TEST(iscool_containers_heterogeneous_map, string_short_string_char_copy)
{
  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map;

  map.set<short>("short", 24);
  map.set("string", std::string("ssss"));
  map.set("restring", std::string("SSSS"));
  map.set("char", 'a');

  const iscool::containers::heterogeneous_map<std::string, short, std::string,
                                              char>
      copy(map);

  EXPECT_EQ(24, *map.get<short>("short"));
  EXPECT_EQ("ssss", *map.get<std::string>("string"));
  EXPECT_EQ("SSSS", *map.get<std::string>("restring"));
  EXPECT_EQ('a', *map.get<char>("char"));

  EXPECT_EQ(24, *copy.get<short>("short"));
  EXPECT_EQ("ssss", *copy.get<std::string>("string"));
  EXPECT_EQ("SSSS", *copy.get<std::string>("restring"));
  EXPECT_EQ('a', *copy.get<char>("char"));
}

TEST(iscool_containers_heterogeneous_map, string_short_string_char_move)
{
  iscool::containers::heterogeneous_map<std::string, short, std::string, char>
      map;

  map.set<short>("short", 24);
  map.set("string", std::string("ssss"));
  map.set("restring", std::string("SSSS"));
  map.set("char", 'a');

  const iscool::containers::heterogeneous_map<std::string, short, std::string,
                                              char>
      moved(std::move(map));

  EXPECT_TRUE(map.empty());

  EXPECT_EQ(24, *moved.get<short>("short"));
  EXPECT_EQ("ssss", *moved.get<std::string>("string"));
  EXPECT_EQ("SSSS", *moved.get<std::string>("restring"));
  EXPECT_EQ('a', *moved.get<char>("char"));
}
