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
#include <iscool/net/decode_base64_string.hpp>

#include <algorithm>

#include <gtest/gtest.h>

TEST(decode_base64_string, empty)
{

  EXPECT_EQ(0, iscool::net::size_of_decoded_base64_string(""));
  iscool::net::decode_base64_string({}, "");
}

static void expect_eq(const std::string& encoded, const std::string& expected)
{
  const std::size_t n = iscool::net::size_of_decoded_base64_string(encoded);
  ASSERT_EQ(n, expected.size());

  std::vector<char> decoded(n);
  iscool::net::decode_base64_string(
      std::span(reinterpret_cast<std::byte*>(decoded.data()), n), encoded);

  EXPECT_TRUE(std::equal(expected.begin(), expected.end(), decoded.begin()));
}

TEST(decode_base64_string, exhaustive_string)
{
  expect_eq(
      "U28/PHA+VGhpcyA0LCA1LCA2LCA3LCA4LCA5LCB6LCB7LCB8LCB9IHRlc3RzIEJhc2U2"
      "NCBlbmNvZGVyLiBTaG93IG1lOiBALCBBLCBCLCBDLCBELCBFLCBGLCBHLCBILCBJLCBK"
      "LCBLLCBMLCBNLCBOLCBPLCBQLCBRLCBSLCBTLCBULCBVLCBWLCBXLCBYLCBZLCBaLCBb"
      "LCBcLCBdLCBeLCBfLCBgLCBhLCBiLCBjLCBkLCBlLCBmLCBnLCBoLCBpLCBqLCBrLCBs"
      "LCBtLCBuLCBvLCBwLCBxLCByLCBzLg==",
      "So?<p>"
      "This 4, 5, 6, 7, 8, 9, z, {, |, } tests Base64 encoder. "
      "Show me: @, A, B, C, D, E, F, G, H, I, J, K, L, M, "
      "N, O, P, Q, R, S, T, U, V, W, X, Y, Z, [, \\, ], ^, _, `, "
      "a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s.");
}

TEST(decode_base64_string, padding)
{
  expect_eq("YW55IGNhcm5hbCBwbGVhc3VyZS4=", "any carnal pleasure.");
  expect_eq("YW55IGNhcm5hbCBwbGVhc3VyZQ==", "any carnal pleasure");
  expect_eq("YW55IGNhcm5hbCBwbGVhc3Vy", "any carnal pleasur");
  expect_eq("YW55IGNhcm5hbCBwbGVhc3U=", "any carnal pleasu");
  expect_eq("YW55IGNhcm5hbCBwbGVhcw==", "any carnal pleas");
}
