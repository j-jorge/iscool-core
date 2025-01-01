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
#include <iscool/net/encode_base64_string.hpp>

#include <gtest/gtest.h>

static void expect_encode_base64_eq(const std::string& output,
                                    const std::string& input)
{
  const std::byte* const data =
      reinterpret_cast<const std::byte*>(input.data());
  EXPECT_EQ(output,
            iscool::net::encode_base64_string(std::span(data, input.size())));
}

TEST(encode_base64_string, empty)
{
  EXPECT_EQ("", iscool::net::encode_base64_string({}));
}

TEST(encode_base64_string, exhaustive_string)
{
  const std::string exhaustive_string(
      "So?<p>"
      "This 4, 5, 6, 7, 8, 9, z, {, |, } tests Base64 encoder. "
      "Show me: @, A, B, C, D, E, F, G, H, I, J, K, L, M, "
      "N, O, P, Q, R, S, T, U, V, W, X, Y, Z, [, \\, ], ^, _, `, "
      "a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s.");
  expect_encode_base64_eq(
      "U28/PHA+VGhpcyA0LCA1LCA2LCA3LCA4LCA5LCB6LCB7LCB8LCB9IHRlc3RzIEJhc2U2"
      "NCBlbmNvZGVyLiBTaG93IG1lOiBALCBBLCBCLCBDLCBELCBFLCBGLCBHLCBILCBJLCBK"
      "LCBLLCBMLCBNLCBOLCBPLCBQLCBRLCBSLCBTLCBULCBVLCBWLCBXLCBYLCBZLCBaLCBb"
      "LCBcLCBdLCBeLCBfLCBgLCBhLCBiLCBjLCBkLCBlLCBmLCBnLCBoLCBpLCBqLCBrLCBs"
      "LCBtLCBuLCBvLCBwLCBxLCByLCBzLg==",
      exhaustive_string);
}

TEST(encode_base64_string, padding)
{
  expect_encode_base64_eq("YW55IGNhcm5hbCBwbGVhc3VyZS4=",
                          "any carnal pleasure.");
  expect_encode_base64_eq("YW55IGNhcm5hbCBwbGVhc3VyZQ==",
                          "any carnal pleasure");
  expect_encode_base64_eq("YW55IGNhcm5hbCBwbGVhc3Vy", "any carnal pleasur");
  expect_encode_base64_eq("YW55IGNhcm5hbCBwbGVhc3U=", "any carnal pleasu");
  expect_encode_base64_eq("YW55IGNhcm5hbCBwbGVhcw==", "any carnal pleas");
}
