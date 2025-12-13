#include <GxEPD2.h>
#include <GxEPD2_GFX.h>
#include <GxEPD2_3C.h>
#include <DisplayTypeHelpers.h>

#include <map>
#include <utility>


template <class Display>
inline static GxEPD2_GFX* __gxepd2_build_3c_driver(const uint8_t dc, const uint8_t rst, const uint8_t busy, const uint8_t ssPin) {
  return new GxEPD2_3C<Display, 340>(Display(ssPin, dc, rst, busy)); //460 ok 680 max
}
//Free: 103068    MaxAlloc: 40948  PSFree: 0
const std::map<const char*, GxEPD2::Panel, cmp_str> DisplayTypeHelpers::PANELS_BY_NAME = {
  { "GDEM133Z91", GxEPD2::Panel::GDEM133Z91 }
};

const std::map<const GxEPD2::Panel, const char*> DisplayTypeHelpers::PANEL_DESCRIPTIONS = {
  { GxEPD2::Panel::GDEM133Z91, "13.3\" B/W/R" }
};

const std::map<const GxEPD2::Panel, const char*> DisplayTypeHelpers::PANEL_COLOR_SUPPORT = {
  { GxEPD2::Panel::GDEM133Z91, "BWR"}
};

// Data generated with:
// ls src/{epd,epd3c}/*.h | xargs -I % bash -c 'grep -Eo "GxEPD2::[^;]+;" % | cut -d":" -f5 | tr -d "\n" && grep -Eo "(WIDTH|HEIGHT)[ ]*=[ ]*\d+" % | grep -Eo "[0-9]+" | tr "\n" "," && echo'
const std::map<const GxEPD2::Panel, std::pair<uint16_t, uint16_t>> DisplayTypeHelpers::PANEL_SIZES = {
  { GxEPD2::Panel::GDEM133Z91, std::make_pair<uint16_t, uint16_t>(960, 680) }
};

const GxEPD2::Panel DisplayTypeHelpers::DEFAULT_PANEL = GxEPD2::Panel::GDEM133Z91;

String DisplayTypeHelpers::displayTypeToString(GxEPD2::Panel type) {
  for (auto it = PANELS_BY_NAME.begin(); it != PANELS_BY_NAME.end(); ++it) {
    if (it->second == type) {
      return it->first;
    }
  }

  return "UNKNOWN";
}

GxEPD2::Panel DisplayTypeHelpers::stringToDisplayType(const String& displayType) {
  auto it = PANELS_BY_NAME.find(displayType.c_str());

  if (it == PANELS_BY_NAME.end()) {
    return DEFAULT_PANEL;
  } else {
    return it->second;
  }
}


bool DisplayTypeHelpers::is3Color(GxEPD2::Panel type) {
  switch (type) {
    case GxEPD2::Panel::GDEM133Z91:
      return true;
    default:
      return false;
  }
}

GxEPD2_GFX* DisplayTypeHelpers::buildDisplay(GxEPD2::Panel type, uint8_t dc, uint8_t rst, uint8_t busy, uint8_t ss) {
  switch (type) {
    case GxEPD2::Panel::GDEM133Z91:
      return __gxepd2_build_3c_driver<GxEPD2_1330c_GDEM133Z91>(dc, rst, busy, ss);
    default:
      Serial.printf_P(PSTR("Unsupported display type, using default.  Provided display: %d\n"), static_cast<size_t>(type));
      return buildDisplay(DisplayTypeHelpers::DEFAULT_PANEL, dc, rst, busy, ss);
  }
}