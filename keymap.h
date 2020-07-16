#pragma once

#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <print.h>
#define _print(str) print(str)
#elif
#define _print(str) (void)0
#endif


enum leds {
  LED00, LED01, LED02,
  LED03, LED04, LED05,
  LED06, LED07, LED08,
  LED09, LED10, LED11,
  LED12, LED13
};

enum layers {
  /* Linux layers */
  _L_BASE, _L_LOWER, _L_RAISE, _L_ADJUST,

  /* MacOS layers */
  _M_BASE, _M_LOWER, _M_RAISE, _M_ADJUST
};

enum keycodes {
  /* toggle additional information via rgb leds ON/OFF */
  INF_TGL = SAFE_RANGE,

  /* switch from Linux layout to MacOS layout */
  L_TO_M,
  /* switch from MacOs layout to Linux layout */
  M_TO_L,

  /* Linux layer switches */
  L_BASE, L_LOWER, L_RAISE, L_ADJUST,

  /* MacOS layer switches */
  M_BASE, M_LOWER, M_RAISE, M_ADJUST
};

typedef union {
  uint32_t raw;
  struct {
    bool info_mode :1;
    bool linux_mode :1;
  };
} user_config_t;