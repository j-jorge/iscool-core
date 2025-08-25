// SPDX-License-Identifier: Apache-2.0
#include <iscool/language_name.hpp>

#include <iscool/iso_639_language_code.hpp>

iscool::iso_639_language_code iscool::to_language_code(language_name c)
{
  switch (c)
    {
    case language_name::de_DE:
      return iso_639_language_code::de;
    case language_name::en_GB:
      return iso_639_language_code::en;
    case language_name::es_ES:
      return iso_639_language_code::es;
    case language_name::fi_FI:
      return iso_639_language_code::fi;
    case language_name::fr_FR:
      return iso_639_language_code::fr;
    case language_name::it_IT:
      return iso_639_language_code::it;
    case language_name::ja_JP:
      return iso_639_language_code::ja;
    case language_name::ko_KR:
      return iso_639_language_code::ko;
    case language_name::nl_NL:
      return iso_639_language_code::nl;
    case language_name::pl_PL:
      return iso_639_language_code::pl;
    case language_name::pt_BR:
    case language_name::pt_PT:
      return iso_639_language_code::pt;
    case language_name::ru_RU:
      return iso_639_language_code::ru;
    case language_name::sv_SE:
      return iso_639_language_code::sv;
    case language_name::th_TH:
      return iso_639_language_code::th;
    case language_name::tr_TR:
      return iso_639_language_code::tr;
    case language_name::zh_CN:
    case language_name::zh_TW:
      return iso_639_language_code::zh;
    }

  return iso_639_language_code::en;
}

std::string_view iscool::to_string(iscool::language_name c)
{
  switch (c)
    {
    case language_name::de_DE:
      return "de_DE";
    case language_name::en_GB:
      return "en_GB";
    case language_name::es_ES:
      return "es_ES";
    case language_name::fi_FI:
      return "fi_FI";
    case language_name::fr_FR:
      return "fr_FR";
    case language_name::it_IT:
      return "it_IT";
    case language_name::ja_JP:
      return "ja_JP";
    case language_name::ko_KR:
      return "ko_KR";
    case language_name::nl_NL:
      return "nl_NL";
    case language_name::pl_PL:
      return "pl_PL";
    case language_name::pt_BR:
      return "pt_BR";
    case language_name::pt_PT:
      return "pt_PT";
    case language_name::ru_RU:
      return "ru_RU";
    case language_name::sv_SE:
      return "sv_SE";
    case language_name::th_TH:
      return "th_TH";
    case language_name::tr_TR:
      return "tr_TR";
    case language_name::zh_CN:
      return "zh_CN";
    case language_name::zh_TW:
      return "zh_TW";
    }

  return "";
}

iscool::language_name iscool::from_string_with_fallback(std::string_view s)
{
  const std::string_view::size_type underscore = s.find_first_of('_');
  const std::string_view language_code =
      (underscore == std::string_view::npos) ? s : s.substr(0, underscore);

  if (language_code == "de")
    return language_name::de_DE;

  if (language_code == "en")
    return language_name::en_GB;

  if (language_code == "es")
    return language_name::es_ES;

  if (language_code == "fi")
    return language_name::fi_FI;

  if (language_code == "fr")
    return language_name::fr_FR;

  if (language_code == "it")
    return language_name::it_IT;

  if (language_code == "ja")
    return language_name::ja_JP;

  if (language_code == "ko")
    return language_name::ko_KR;

  if (language_code == "nl")
    return language_name::nl_NL;

  if (language_code == "pl")
    return language_name::pl_PL;

  if (language_code == "pt")
    {
      if (s == "pt_BR")
        return language_name::pt_BR;

      return language_name::pt_PT;
    }

  if (language_code == "ru")
    return language_name::ru_RU;

  if (language_code == "sv")
    return language_name::sv_SE;

  if (language_code == "th")
    return language_name::th_TH;

  if (language_code == "tr")
    return language_name::tr_TR;

  if (language_code == "zh")
    {
      if (s == "zh_TW")
        return language_name::zh_TW;

      return language_name::zh_CN;
    }

  return language_name::en_GB;
}

std::string_view iscool::to_human_string(iscool::language_name c)
{
  switch (c)
    {
    case language_name::de_DE:
      return "Deutsch";
    case language_name::en_GB:
      return "English";
    case language_name::es_ES:
      return "Español";
    case language_name::fi_FI:
      return "Suomi";
    case language_name::fr_FR:
      return "Français";
    case language_name::it_IT:
      return "Italiano";
    case language_name::ja_JP:
      return "日本語";
    case language_name::ko_KR:
      return "한국어";
    case language_name::nl_NL:
      return "Nederlands";
    case language_name::pl_PL:
      return "Polski";
    case language_name::pt_BR:
      return "Português (Brasil)";
    case language_name::pt_PT:
      return "Português";
    case language_name::ru_RU:
      return "Русский";
    case language_name::sv_SE:
      return "Svenska";
    case language_name::th_TH:
      return "อักษรไทย";
    case language_name::tr_TR:
      return "Türkçe";
    case language_name::zh_CN:
      return "简体中文";
    case language_name::zh_TW:
      return "繁體中文";
    }

  return "English";
}
