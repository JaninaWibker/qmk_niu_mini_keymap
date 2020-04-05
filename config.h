#pragma once

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

/* led colors */
#define LINUX_COLORS        0, 0, 0
#define MACOS_COLORS        0, 0, 0
#define CAPS_COLORS         0, 0, 0
#define WPM0_COLORS         0, 0, 0
#define WPM1_COLORS         0, 0, 0
#define WPM2_COLORS         0, 0, 0
#define WPM3_COLORS         0, 0, 0
#define LED_OFF_COLORS      0, 0, 0
#define LAYER_BASE_COLORS   0, 0, 0
#define LAYER_LOWER_COLORS  0, 0, 0
#define LAYER_RAISE_COLORS  0, 0, 0
#define LAYER_ADJUST_COLORS 0, 0, 0

/* backslash key on both Linux and MacOS */
#define _L_BACKSLASH RALT(7)
#define _M_BACKSLASH LSFT(RALT(7))

#define _BACKWARDS LCTL(KC_PGUP)
#define _FORWARDS  LCTL(KC_PGDN)

/* escape normally, but L_LOWER when held down */
#define _ESCAPE_LOWER MT(L_LOWER, KC_ESC)

/* apple fn key (mapped to F20, needs to be software remapped) */
#define _M_FN				 KC_F20