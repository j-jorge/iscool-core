// SPDX-License-Identifier: Apache-2.0
#include <iscool/i18n/load_translations.hpp>

#include <iscool/files/file_system_delegates.hpp>
#include <iscool/files/read_file.hpp>
#include <iscool/files/setup.hpp>
#include <iscool/i18n/gettext.hpp>
#include <iscool/i18n/numeric.hpp>
#include <iscool/language_name.hpp>

#include <iscool/files/test/file_system_delegates_mockup.hpp>

#include <fstream>

#include <gtest/gtest.h>

class iscool_i18n_test : public ::testing::Test
{
public:
  iscool_i18n_test();
  ~iscool_i18n_test();
};

iscool_i18n_test::iscool_i18n_test()
{
  iscool::files::initialize(
      iscool::files::test::default_file_system_delegates_mockup());
}

iscool_i18n_test::~iscool_i18n_test()
{
  iscool::files::finalize();
}

TEST_F(iscool_i18n_test, no_initialization)
{
  EXPECT_EQ("test_fr", ic_gettext("test_fr"));
  EXPECT_EQ("test_en", ic_gettext("test_en"));
  EXPECT_EQ("test_not_translated", ic_gettext("test_not_translated"));
}

TEST_F(iscool_i18n_test, valid_file)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::en_GB,
      *iscool::files::read_file("translations/en.mo")));

  EXPECT_EQ(std::string("French Test"), ic_gettext("test_fr"));
  EXPECT_EQ(std::string("English Test"), ic_gettext("test_en"));
  EXPECT_EQ("test_not_translated", ic_gettext("test_not_translated"));
}

TEST_F(iscool_i18n_test, invalid_file)
{
  std::unique_ptr<std::istream> file(
      iscool::files::read_file("translations/en.mo"));

  file->seekg(10);
  EXPECT_FALSE(
      iscool::i18n::load_translations(iscool::language_name::en_GB, *file));

  EXPECT_EQ("test_fr", ic_gettext("test_fr"));
  EXPECT_EQ("test_en", ic_gettext("test_en"));
  EXPECT_EQ("test_not_translated", ic_gettext("test_not_translated"));
}

TEST_F(iscool_i18n_test, numeric_br)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::br_FR,
      *iscool::files::read_file("translations/fr.mo")));
  EXPECT_EQ("20 400 200 300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_br)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::br_FR,
      *iscool::files::read_file("translations/fr.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_en)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::en_GB,
      *iscool::files::read_file("translations/en.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_en)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::en_GB,
      *iscool::files::read_file("translations/en.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_de)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::de_DE,
      *iscool::files::read_file("translations/de.mo")));
  EXPECT_EQ("20.400.200.300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_de)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::de_DE,
      *iscool::files::read_file("translations/de.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_es)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::es_ES,
      *iscool::files::read_file("translations/es.mo")));
  EXPECT_EQ("20.400.200.300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_es)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::es_ES,
      *iscool::files::read_file("translations/es.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_it)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::it_IT,
      *iscool::files::read_file("translations/it.mo")));
  EXPECT_EQ("20.400.200.300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_it)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::it_IT,
      *iscool::files::read_file("translations/it.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_nl)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::nl_NL,
      *iscool::files::read_file("translations/nl.mo")));
  EXPECT_EQ("20.400.200.300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_nl)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::it_IT,
      *iscool::files::read_file("translations/nl.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_fr)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::fr_FR,
      *iscool::files::read_file("translations/fr.mo")));
  EXPECT_EQ("20 400 200 300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_fr)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::fr_FR,
      *iscool::files::read_file("translations/fr.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_ja)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::ja_JP,
      *iscool::files::read_file("translations/ja.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_ja)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::ja_JP,
      *iscool::files::read_file("translations/ja.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_ko)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::ko_KR,
      *iscool::files::read_file("translations/ko.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_ko)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::ko_KR,
      *iscool::files::read_file("translations/ko.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_pt)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::pt_PT,
      *iscool::files::read_file("translations/pt.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_pt)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::pt_PT,
      *iscool::files::read_file("translations/pt.mo")));

  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_pt_BR)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::pt_BR,
      *iscool::files::read_file("translations/pt.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_pt_BR)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::pt_BR,
      *iscool::files::read_file("translations/pt_BR.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Plural"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_th)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::th_TH,
      *iscool::files::read_file("translations/th.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_th)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::th_TH,
      *iscool::files::read_file("translations/th.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_zh_CN)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::zh_CN,
      *iscool::files::read_file("translations/zh_CN.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_zh_CN)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::zh_CN,
      *iscool::files::read_file("translations/zh_CN.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 2));
}

TEST_F(iscool_i18n_test, numeric_zh_TW)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::zh_TW,
      *iscool::files::read_file("translations/zh_TW.mo")));
  EXPECT_EQ("20,400,200,300", iscool::i18n::numeric::to_string(20400200300ll));
}

TEST_F(iscool_i18n_test, plurals_zh_TW)
{
  EXPECT_TRUE(iscool::i18n::load_translations(
      iscool::language_name::zh_TW,
      *iscool::files::read_file("translations/zh_TW.mo")));

  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 0));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 1));
  EXPECT_EQ(std::string("Singular"), ic_ngettext("singular", "plural", 2));
}
