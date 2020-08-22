/* Copyright 2015-2017 Jannik Wibker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "keymap.h"

user_config_t user_config;

static bool led_on = true; // what is this even needed for?

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  /* Linux - Base
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Ctrl | Super|  Alt | Raise|    Space    | Lower|AltGr | Caps |   -  |   =  |
   * `-----------------------------------------------------------------------------------'
   */
  [_L_BASE] = LAYOUT_planck_mit(
    _CTRL_ESC,    KC_Q,    KC_W,     KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,        KC_P,      KC_BSPC,
    _L_TAB_LOWER, KC_A,    KC_S,     KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,        KC_LBRC,   KC_RBRC,
    KC_LSFT,      KC_Z,    KC_X,     KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,      KC_SLSH,   KC_ENT,
    KC_LCTL,      KC_LGUI, L_ADJUST, KC_LALT, L_RAISE, KC_SPC,     L_LOWER, KC_RALT, _L_CAPSLOCK, _GUI_MINS, _CTL_EQL
  ),

  [_L_VIM_INSERT] = LAYOUT_planck_mit(
    VIM_NORMAL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_L_VIM_NORMAL] = LAYOUT_planck_mit(
    VIM_ESC,   KC_NO,   VIM_W,   VIM_E,   KC_NO,   KC_NO,     VIM_Y,   VIM_U,   VIM_I,     VIM_O,      VIM_P,   KC_NO,
    KC_TRNS,   VIM_A,   VIM_S,   VIM_D,   KC_NO,   VIM_G,     VIM_H,   VIM_J,   VIM_K,     VIM_L,      KC_NO,   KC_NO,
    VIM_SHIFT, KC_NO,   VIM_X,   VIM_C,   VIM_V,   VIM_B,     KC_NO,   KC_NO,   VIM_COMMA, VIM_PERIOD, KC_NO,   VIM_ENTER,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, VIM_SPACE,          KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS
  ),

  /* Linux Lower
   * ,-----------------------------------------------------------------------------------.
   * | Ctrl |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   \  |   ^  |   *  |   /  |   #  | Left | Down |  Up  |Right |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Val- | Val+ |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Delete|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Ctrl | Super|  Alt | Raise|    Enter    |Lower |AltGr | Caps | Left | Right|
   * `-----------------------------------------------------------------------------------'
   */
  [_L_LOWER] = LAYOUT_planck_mit(
    KC_RCTL, KC_1,         KC_2,    KC_3,         KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    KC_TRNS, _L_BACKSLASH, KC_GRV,  _L_ASTERISKS, _L_SLASH, KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, KC_QUOT,
    KC_TRNS, _L_DOLLAR,    KC_DEL,  KC_INS,       KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RIGHT
  ),

  /* Linux Raise
   * ,-----------------------------------------------------------------------------------.
   * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Super|Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Ctrl | Super|  Alt | Raise|  Backspace  |Lower |AltGr | Caps | Hue+ | Sat+ |
   * `-----------------------------------------------------------------------------------'
   */
  [_L_RAISE] = LAYOUT_planck_mit(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_LGUI, _L_VD_P, KC_UP,   _L_VU_N, KC_MPLY, KC_TAB,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_LBRC, KC_RBRC,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,  KC_SLSH, KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI
  ),

  /* Linux Adjust
   * ,-----------------------------------------------------------------------------------.
   * | NumLk| Btn1 | M Up | Btn2 |Scrll+|Delete|   /  |   1  |   2  |   3  |   -  | Reset|
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Btn3 |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Forw |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| RGB T| Cycle| InfT |  Mac |  Esc | Bksp |   7  |   8  |   9  |Enter | Bckw |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |Adjust| Ctrl | Super|  Alt | Raise|    Space    |Lower |   0  |   .  |AltGr | Vim  |
   * `-----------------------------------------------------------------------------------'
   */
  [_L_ADJUST] = LAYOUT_planck_mit(
    _NUM_PS,  KC_BTN1, KC_MS_U,           KC_BTN2, KC_WH_U, RESET,  KC_PSLS,  KC_P1,   KC_P2, KC_P3,   KC_PMNS, RESET,
    KC_BTN3,  KC_MS_L, KC_MS_D,         KC_MS_R, KC_WH_D, KC_TAB, KC_PAST,  KC_P4,   KC_P5, KC_P6,   KC_PPLS, _FORWARDS,
    KC_TRNS, RGB_TOG, RGB_MODE_FORWARD, INF_TGL, L_TO_M,  KC_ESC, KC_BSPC,  KC_P7,   KC_P8, KC_P9,   KC_PENT, _BACKWARDS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_SPC,           KC_TRNS, KC_P0, KC_PDOT, KC_RALT, VIM_NORMAL
  ),


  /* MacOS - Base
   * ,-----------------------------------------------------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    | Lower|AltGr | Caps |   -  |   =  |
   * `-----------------------------------------------------------------------------------'
   */
  [_M_BASE] = LAYOUT_planck_mit(
    _CTRL_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,        KC_P,      KC_BSPC,
    _M_TAB_LOWER, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,        KC_LBRC,   KC_RBRC,
    KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,      KC_SLSH,   KC_ENT,
    _M_FN,        KC_LCTL, KC_LALT, KC_LGUI, M_RAISE, KC_SPC,     M_LOWER, KC_RALT, _M_CAPSLOCK, _GUI_MINS, _CTL_EQL
  ),

  [_M_VIM_INSERT] = LAYOUT_planck_mit(
    VIM_NORMAL, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_M_VIM_NORMAL] = LAYOUT_planck_mit(
    VIM_ESC,   KC_NO,   VIM_W,   VIM_E,   KC_NO,   KC_NO,     VIM_Y,   VIM_U,   VIM_I,     VIM_O,      VIM_P,   KC_NO,
    KC_TRNS,   VIM_A,   VIM_S,   VIM_D,   KC_NO,   VIM_G,     VIM_H,   VIM_J,   VIM_K,     VIM_L,      KC_NO,   KC_NO,
    VIM_SHIFT, KC_NO,   VIM_X,   VIM_C,   VIM_V,   VIM_B,     KC_NO,   KC_NO,   VIM_COMMA, VIM_PERIOD, KC_NO,   VIM_ENTER,
    KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, VIM_SPACE,          KC_TRNS, KC_TRNS,   KC_TRNS,    KC_TRNS, KC_TRNS
  ),

  /* MacOS Lower
   * ,-----------------------------------------------------------------------------------.
   * | Ctrl |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Tab  |   \  |   ^  |   *  |   /  |   #  | Left | Down |  Up  |Right |   ;  |  '   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Val- | Val+ |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Delete|
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Fn  | Ctrl |  Alt | Super| Raise|    Enter    |Lower |AltGr | Caps | Left | Right|
   * `-----------------------------------------------------------------------------------'
   */
  [_M_LOWER] = LAYOUT_planck_mit(
    KC_RCTL,      KC_1,         KC_2,    KC_3,         KC_4,     KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
    _M_TAB_LOWER, _M_BACKSLASH, KC_GRV,  _M_ASTERISKS, _M_SLASH, KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_SCLN, KC_QUOT,
    KC_TRNS,      _M_DOLLAR,    KC_DEL,  KC_INS,       KC_HOME,  KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    KC_TRNS,      KC_TRNS,      KC_TRNS, KC_TRNS,      KC_TRNS,  KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS, KC_LEFT, KC_RIGHT
  ),

  /* MacOS Raise
   * ,-----------------------------------------------------------------------------------.
   * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Super|Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Fn  | Ctrl |  Alt | Super| Raise|  Backspace  |Lower |AltGr | Caps | Hue+ | Sat+ |
   * `-----------------------------------------------------------------------------------'
   */
  [_M_RAISE] = LAYOUT_planck_mit(
    KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    KC_LGUI, _M_VD_P, KC_UP,   _L_VU_N, KC_MPLY, KC_TAB,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT, KC_LBRC, KC_RBRC,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,  KC_SLSH, KC_F12,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, RGB_HUI, RGB_SAI, RGB_VAI
  ),

  /* MacOS Adjust
   * ,-----------------------------------------------------------------------------------.
   * | NumLk| Btn1 | M Up | Btn2 |Scrll+|Delete|   /  |   1  |   2  |   3  |   -  | Reset|
   * |------+------+------+------+------+-------------+------+------+------+------+------|
   * | Btn3 |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Forw |
   * |------+------+------+------+------+------|------+------+------+------+------+------|
   * | Shift| RGB T| Cycle| InfT | Linux|  Esc | Bksp |   7  |   8  |   9  |Enter | Bckw |
   * |------+------+------+------+------+------+------+------+------+------+------+------|
   * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    |Lower |   0  |   .  |AltGr | Vim  |
   * `-----------------------------------------------------------------------------------'
   */
  [_M_ADJUST] = LAYOUT_planck_mit(
    _NUM_PS,   KC_BTN1, KC_MS_U,          KC_BTN2, KC_WH_U, KC_DEL, KC_PSLS,  KC_P1,   KC_P2,   KC_P3,    KC_PMNS, RESET,
    KC_BTN3, KC_MS_L, KC_MS_D,          KC_MS_R, KC_WH_D, KC_TAB, KC_PAST,  KC_P4,   KC_P5,   KC_P6,    KC_PPLS, _FORWARDS,
    KC_TRNS, RGB_TOG, RGB_MODE_FORWARD, INF_TGL, M_TO_L,  KC_ESC, KC_BSPC,  KC_P7,   KC_P8,   KC_P9,    KC_PENT, _BACKWARDS,
    KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_SPC,           KC_TRNS, KC_P0,   KC_PDOT,  KC_RALT, VIM_NORMAL
  )

};

extern bool is_mac(void) {
  return !user_config.linux_mode;
}

extern uint8_t vim_cmd_layer(void) {
  return user_config.linux_mode ? _L_VIM_NORMAL : _M_VIM_NORMAL;
}

extern uint8_t vim_insert_layer(void) {
  return user_config.linux_mode ? _L_VIM_INSERT : _M_VIM_INSERT;
}

void set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t i) {
  if (i < RGBLED_NUM) {
    rgblight_setrgb_at(r, g, b, i);
  }
}

/* print 8-bit number */
void _iprint(char n) {
  #ifdef CONSOLE_ENABLE
    xputc((char) (n / 100 + 48));
    xputc((char) ((n % 100) / 10 + 48));
    xputc((char) ((n % 10) / 1 + 48));
  #endif
}

void set_rgblight_by_layer(layer_state_t state) {
  switch(biton32(state)) {
    case _L_BASE:
    case _M_BASE: {
      _print("layer:base\n");
      set_led(LAYER_BASE_COLORS, LED13);
      rgblight_set_effect_range(LED00, 14);
    } break;
    case _L_LOWER:
    case _M_LOWER: {
      _print("layer:lower\n");
      rgblight_set_effect_range(LED00, 8);
      set_led(LAYER_LOWER_COLORS, LED08);
      set_led(LAYER_LOWER_COLORS, LED09);
      set_led(LAYER_LOWER_COLORS, LED10);
      set_led(LAYER_LOWER_COLORS, LED11);
      set_led(LAYER_LOWER_COLORS, LED12);
      set_led(LAYER_LOWER_COLORS, LED13);
    } break;
    case _L_RAISE:
    case _M_RAISE: {
      _print("layer:raise\n");
      rgblight_set_effect_range(LED00, 8);
      set_led(LAYER_RAISE_COLORS, LED08);
      set_led(LAYER_RAISE_COLORS, LED09);
      set_led(LAYER_RAISE_COLORS, LED10);
      set_led(LAYER_RAISE_COLORS, LED11);
      set_led(LAYER_RAISE_COLORS, LED12);
      set_led(LAYER_RAISE_COLORS, LED13);
    } break;
    case _L_ADJUST:
    case _M_ADJUST: {
      _print("layer:adjst\n");
      rgblight_set_effect_range(LED00, 8);
      set_led(LAYER_ADJUST_COLORS, LED08);
      set_led(LAYER_ADJUST_COLORS, LED09);
      set_led(LAYER_ADJUST_COLORS, LED10);
      set_led(LAYER_ADJUST_COLORS, LED11);
      set_led(LAYER_ADJUST_COLORS, LED12);
      #ifdef OS_INDICATOR
        if(user_config.linux_mode) {
          set_led(LAYER_ADJUST_COLORS, LED13);
        } else {
          set_led(MACOS_COLORS, LED13);
        }
      #else
        set_led(LAYER_ADJUST_COLORS, LED13);
      #endif
    } break;

    case _L_VIM_INSERT:
    case _M_VIM_INSERT: {
      _print("layer:vim_insert\n");
      rgblight_set_effect_range(LED00, 8);
      set_led(LAYER_VIM_INSERT_COLORS, LED08);
      set_led(LAYER_VIM_INSERT_COLORS, LED09);
      set_led(LAYER_VIM_INSERT_COLORS, LED10);
      set_led(LAYER_VIM_INSERT_COLORS, LED11);
      set_led(LAYER_VIM_INSERT_COLORS, LED12);
    } break;

    case _L_VIM_NORMAL:
    case _M_VIM_NORMAL: {
      switch(vstate) {
        case VIM_NORMAL: {
          _print("layer:vim_normal\n");
          rgblight_set_effect_range(LED00, 8);
          set_led(LAYER_VIM_NORMAL_COLORS, LED08);
          set_led(LAYER_VIM_NORMAL_COLORS, LED09);
          set_led(LAYER_VIM_NORMAL_COLORS, LED10);
          set_led(LAYER_VIM_NORMAL_COLORS, LED11);
          set_led(LAYER_VIM_NORMAL_COLORS, LED12);
          set_led(LAYER_VIM_NORMAL_COLORS, LED13);
        } break;
        case VIM_V:
        case VIM_VS: {
          _print("layer:vim_visual\n");
          rgblight_set_effect_range(LED00, 8);
          set_led(LAYER_VIM_VISUAL_COLORS, LED08);
          set_led(LAYER_VIM_VISUAL_COLORS, LED09);
          set_led(LAYER_VIM_VISUAL_COLORS, LED10);
          set_led(LAYER_VIM_VISUAL_COLORS, LED11);
          set_led(LAYER_VIM_VISUAL_COLORS, LED12);
          set_led(LAYER_VIM_VISUAL_COLORS, LED13);
        } break;
      }
    }

  }
  rgblight_set();
}

// loading the eeprom data
void keyboard_post_init_user(void) {
  user_config.raw = eeconfig_read_user();

  if(user_config.info_mode) {
    // TODO: what to do here?
  }
}

// EEPROM is getting reset
void eeconfig_init_user(void) {
  user_config.raw = 0;
  user_config.linux_mode = true; // linux mode by default
  eeconfig_update_user(user_config.raw);
  rgblight_sethsv(192, 255, 255); // set default led color
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(record->event.pressed) { // what is this needed for?
    #ifdef BACKLIGHT_ENABLE
      if(led_on == false) {
        backlight_enable();
        led_on = true;
      }
    #endif
  }

  #ifdef ENABLE_VIM_MODE

  bool was_handled_by_vim = !handle_vim_keycodes(keycode, record);

  if(was_handled_by_vim) {
    return false;
  }

  #endif

  switch (keycode) {

    case _NUM_PS: {
      uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
      if(record->event.pressed) {
        if(shifted) {
          unregister_code(KC_LSFT);
          register_code(KC_PSCREEN);
          register_code(KC_LSFT);
        } else {
          register_code(KC_NUMLOCK);
        }
      } else {
        // unregistering both keys; is this potentially bad practice?
        unregister_code(KC_PSCREEN);
        unregister_code(KC_NUMLOCK);
      }
    } break;

    case L_LOWER:
      if(record->event.pressed) {
        layer_on(_L_LOWER);
      } else {
        layer_off(_L_LOWER);
      }
      update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
      return false;

    case L_RAISE:
      if(record->event.pressed) {
        layer_on(_L_RAISE);
      } else {
        layer_off(_L_RAISE);
      }
      update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
      return false;

    case L_ADJUST:
      if(record->event.pressed) {
        layer_on(_L_ADJUST);
      } else {
        layer_off(_L_ADJUST);
      }
      return false;


    case M_LOWER:
      if(record->event.pressed) {
        layer_on(_M_LOWER);
      } else {
        layer_off(_M_LOWER);
      }
      update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
      return false;
        
    case M_RAISE:
      if(record->event.pressed) {
        layer_on(_M_RAISE);
      } else {
        layer_off(_M_RAISE);
      }
      update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
      return false;

    case M_ADJUST:
      if(record->event.pressed) {
        layer_on(_M_ADJUST);
      } else {
        layer_off(_M_ADJUST);
      }
      return false;

    case RGB_HUI:
    case RGB_HUD:
    case RGB_SAI:
    case RGB_SAD:
    case RGB_VAI:
    case RGB_VAD: {
      if(record->event.pressed) {

        process_rgb(keycode, record);

        rgblight_set_effect_range(LED00, 0);
        rgblight_sethsv_range(
          rgblight_get_hue(),
          rgblight_get_sat(),
          rgblight_get_val(),
          LED00,
          LED13
        );

        _print("rgb_showcase\n");
      }
    } return false;

    case _L_VD_P: // volume down; previous song
    case _M_VD_P: { // could theoretically make OS dependent changes here but the OS's are quite
      uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
      if(record->event.pressed) {
        if(shifted) {
          unregister_code(KC_LSFT);
          register_code(KC_MPRV);
          register_code(KC_LSFT);
        } else {
          register_code(KC_VOLD);
        }
      } else {
        // unregistering both keys; is this potentially bad practice?
        unregister_code(KC_MPRV);
        unregister_code(KC_VOLD);
      }
    } break;

    case _L_VU_N: // volume up; next song
    case _M_VU_N: {
      uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
      if(record->event.pressed) {
        if(shifted) {
          unregister_code(KC_LSFT);
          register_code(KC_MNXT);
          register_code(KC_LSFT);
        } else {
          register_code(KC_VOLU);
        }
      } else {
        // unregistering both keys; is this potentially bad practice?
        unregister_code(KC_MNXT);
        unregister_code(KC_VOLU);
      }
    } break;


    /* Info Toggle */
    case INF_TGL: { // toggle if keyboard state is displayed through LEDs; if shift is pressed print debug information to console
      if(record->event.pressed) {
        uint8_t shifted = get_mods() & MOD_MASK_SHIFT;
        if(shifted) {
          _print("OS:");
          if(user_config.linux_mode) _print("L");
          else                       _print("M");
          _print(",INF:");
          if(user_config.info_mode) _print("on,");
          else                      _print("off,");
          _print("RGB hue,sat,val,mode: ");
          _iprint(rgblight_get_hue());
          _print(",");
          _iprint(rgblight_get_sat());
          _print(",");
          _iprint(rgblight_get_val());
          _print(",");
          _iprint(rgblight_get_mode());
          _print("\n");
        } else {
          user_config.info_mode = !user_config.info_mode;
          eeconfig_update_user(user_config.raw);
          rgblight_set_effect_range(LED00, user_config.info_mode ? 8 : 14);
          #ifdef CONSOLE_ENABLE
            print("INF_TGL");
            if(user_config.info_mode) print("on\n");
            else                      print("off\n");
          #endif
        }
      }
    } break;

    /* Switch from Linux to MacOS */
    case L_TO_M: {
      if(record->event.pressed) {
        _print("OS: Mac\n");
        user_config.linux_mode = false;
        eeconfig_update_user(user_config.raw);
        set_single_persistent_default_layer(_M_BASE); // TODO: integrate in user_config?
      }
    } break;

    /* Switch from MacOS to Linux */
    case M_TO_L: {
      if(record->event.pressed) {
        _print("OS: Linux\n");
        user_config.linux_mode = true;
        eeconfig_update_user(user_config.raw);
        set_single_persistent_default_layer(_L_BASE);
      }
    } break;
  }


  return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
  #ifdef LAYER_INDICATOR
    if(user_config.info_mode) {
      set_rgblight_by_layer(state);
    }
  #endif
  return state;
}

void oneshot_layer_changed_user(uint8_t layer) {

  if(layer == _L_LOWER || layer == _M_LOWER) {
    _print("modtap:shift down\n");
    register_code(KC_LSFT);
    // activate shift
  }

  if(!layer) {
    // deactivate shift and other things
    _print("modtap:shift up\n");
    unregister_code(KC_LSFT);
  }
}

bool led_update_user(led_t led_state) {
  #ifdef CAPSLOCK_INDICATOR
    if(led_state.caps_lock) {
      set_led(CAPS_COLORS, LED07);
      rgblight_set();
      return false;
    } else {
      return true;
    }
  #endif
}
