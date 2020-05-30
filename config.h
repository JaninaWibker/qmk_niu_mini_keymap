#pragma once

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

/* rgb lighting will be switched off when host goes to sleep */
#define RGBLIGHT_SLEEP

#define BACKLIGHT_TIMEOUT 5 // in minutes

/* led colors */
#define LINUX_COLORS        RGB_PURPLE
#define MACOS_COLORS        RGB_WHITE
#define CAPS_COLORS         RGB_BLUE
#define WPM0_COLORS         RGB_WHITE
#define WPM1_COLORS         RGB_TEAL
#define WPM2_COLORS         RGB_PINK
#define WPM3_COLORS         RGB_RED
#define LED_OFF_COLORS      0, 0, 0
#define LAYER_BASE_COLORS   RGB_WHITE
#define LAYER_LOWER_COLORS  RGB_CYAN
#define LAYER_RAISE_COLORS  RGB_GREEN
#define LAYER_ADJUST_COLORS RGB_RED

/* #define WPM_INDICATOR */
#define LAYER_INDICATOR
#define CAPSLOCK_INDICATOR
#define OS_INDICATOR

/* backslash key on both Linux and MacOS */
#define _L_BACKSLASH RALT(7)
#define _M_BACKSLASH LSFT(RALT(7))

#define _BACKWARDS LCTL(KC_PGUP)
#define _FORWARDS  LCTL(KC_PGDN)

/* escape normally, but L_LOWER when held down */
#define _L_TAB_LOWER LT(_L_LOWER, KC_TAB)
#define _M_TAB_LOWER LT(_M_LOWER, KC_TAB)

/* apple fn key (mapped to F20, needs to be software remapped) */
#define _M_FN				 KC_F20