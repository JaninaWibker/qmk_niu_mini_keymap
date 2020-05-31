#pragma once

#undef RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT

/* rgb lighting will be switched off when host goes to sleep */
#define RGBLIGHT_SLEEP

#define BACKLIGHT_TIMEOUT 2 // in minutes

/* tap and hold (mod tap, layer tap; ) */
#define RETRO_TAPPING
#define PERMISSIVE_HOLD
#define TAPPING_TERM 0

/* mouse speed & acceleration */
#define MOUSEKEY_MAX_SPEED 10
#define MOUSEKEY_INTERVAL 32
#define MOUSEKEY_TIME_TO_MAX 40

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
#define _L_BACKSLASH RALT(KC_7)
#define _M_BACKSLASH LSFT(RALT(KC_7))

#define _BACKWARDS LCTL(KC_PGUP)
#define _FORWARDS  LCTL(KC_PGDN)

/* tab normally, but L_LOWER / M_LOWER when held down */
#define _L_TAB_LOWER LT(_L_LOWER, KC_TAB)
#define _M_TAB_LOWER LT(_M_LOWER, KC_TAB)

/* esc normally, but (left) control when held down */
#define _CTRL_ESC MT(MOD_LCTL, KC_ESC)

/* space normally, but (left) control when held down */ // TODO: currently not being used
#define _CTRL_SPC MT(MOD_LCTL, KC_SPC)

/* right arrow normally, but (right) shift when held down */
#define _SFT_RIGHT MT(MOD_RSFT, KC_RIGHT)

/* left arrow normally, but (right) gui when held down */ // TODO: is gui a good key here, what about using ctrl?
#define _GUI_LEFT  MT(MOD_RGUI, KC_LEFT)


/* apple fn key (mapped to F20, needs to be software remapped) */
#define _M_FN				 KC_F20