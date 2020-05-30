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

#include QMK_KEYBOARD_H
#ifdef CONSOLE_ENABLE
#include <print.h>
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

	L_D_BASE, L_D_LOWER, L_D_RAISE, L_D_ADJUST,

	/* MacOS layer switches */
	M_BASE, M_LOWER, M_RAISE, M_ADJUST,

	M_D_BASE, M_D_LOWER, M_D_RAISE, M_D_ADJUST,
};

typedef union {
  uint32_t raw;
  struct {
    bool info_mode :1;
    bool linux_mode :1;
  };
} user_config_t;

user_config_t user_config;

static uint16_t idle_timer = 0;
static uint8_t halfmin_counter = 0;
static bool led_on = true;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Linux - Base
	 * ,-----------------------------------------------------------------------------------.
	 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Adjust| Ctrl | Super|  Alt | Raise|    Space    | Lower|AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_BASE] = LAYOUT_planck_mit(
		KC_ESC,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, 
		_L_TAB_LOWER, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,    KC_LBRC,  KC_RBRC, 
		KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, 
		L_ADJUST,     KC_LCTL, KC_LGUI, KC_LALT, L_RAISE, KC_SPC,     L_LOWER, KC_RALT, KC_CAPS, KC_LEFT,  KC_RGHT),

	/* Linux Lower
	 * ,-----------------------------------------------------------------------------------.
	 * | Ctrl |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |  \*  |   ^  |   -  |   =  |   \  | Left | Down |  Up  |Right |   ;  |  '   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Val- | Val+ |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Shift |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Adjust| Ctrl | Super|  Alt | Raise|    Enter    |Lower |AltGr | Caps | Hue+ | Sat+ |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_LOWER] = LAYOUT_planck_mit(
		KC_RCTL, KC_1,    	   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL, 
		KC_TRNS, _L_BACKSLASH, KC_GRV,  KC_MINS, KC_EQL,  KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_SCLN, KC_QUOT, 
		KC_TRNS, RGB_VAD,			 RGB_VAI, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, 
		KC_TRNS, KC_TRNS,			 KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,           KC_TRNS, KC_TRNS, KC_TRNS,  RGB_HUI, RGB_SAI),

	/* Linux Raise
	 * ,-----------------------------------------------------------------------------------.
	 * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Super|Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Adjust| Ctrl | Super|  Alt | Raise|  Backspace  |Lower |AltGr | Caps | Bckw | Forw |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_RAISE] = LAYOUT_planck_mit(
		KC_TRNS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,     KC_F11, 
		KC_LGUI, KC_VOLD, KC_UP,   KC_VOLU, KC_MPLY, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT,  KC_LBRC,    KC_RBRC, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,   KC_SLSH,    KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, KC_TRNS,  _BACKWARDS, _FORWARDS),

	/* Linux Adjust
	 * ,-----------------------------------------------------------------------------------.
	 * | Debug| Btn1 | M Up | Btn2 |Scrll+| InfT |   /  |   1  |   2  |   3  |   -  | Lck1 |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Btn3 |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Lck2 |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB T| Cycle| Reset|  Mac |  Esc | Bksp |   7  |   8  |   9  |Enter | Lck3 |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |Adjust| Ctrl | Super|  Alt | Raise|    Space    |Lower |   0  |   .  |AltGr | Lck0 |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_ADJUST] = LAYOUT_planck_mit(
		DEBUG,  KC_BTN1, KC_MS_U,					  KC_BTN2, KC_WH_U, INF_TGL, KC_PSLS,  KC_P1,   KC_P2,   KC_P3,    KC_PMNS, L_D_LOWER, 
		KC_BTN3,  KC_MS_L, KC_MS_D,					KC_MS_R, KC_WH_D, KC_TAB,  KC_PAST,  KC_P4,   KC_P5,   KC_P6,    KC_PPLS, L_D_RAISE, 
		KC_TRNS, RGB_TOG, RGB_MODE_FORWARD, RESET,   L_TO_M,  KC_ESC,  KC_BSPC,  KC_P7,   KC_P8,   KC_P9,    KC_PENT, L_D_ADJUST, 
		KC_TRNS, KC_TRNS, KC_TRNS,					KC_TRNS, KC_TRNS, KC_SPC,            KC_TRNS, KC_P0,   KC_PDOT,  KC_RALT, L_D_BASE),

	/* MacOS - Base
	 * ,-----------------------------------------------------------------------------------.
	 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    | Lower|AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_BASE] = LAYOUT_planck_mit(
		KC_ESC,       KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, 
		_M_TAB_LOWER, KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,    KC_LBRC,  KC_RBRC, 
		KC_LSFT,      KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, 
		_M_FN,        KC_LCTL, KC_LALT, KC_LGUI, M_RAISE, KC_SPC,     M_LOWER, KC_RALT, KC_CAPS, KC_LEFT,  KC_RGHT),

	/* MacOS Lower
	 * ,-----------------------------------------------------------------------------------.
	 * | Ctrl |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Tab  |  \*  |   ^  |   -  |   =  |   \  | Left | Down |  Up  |Right |   ;  |  '   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Val- | Val+ |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Enter    |Lower |AltGr | Caps | Hue+ | Sat+ |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_LOWER] = LAYOUT_planck_mit(
		KC_RCTL, 			KC_1,   		  KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL, 
		_M_TAB_LOWER, _M_BACKSLASH,	KC_GRV,  KC_MINS, KC_EQL,  KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_SCLN, KC_QUOT, 
		KC_TRNS, 			RGB_VAD,			RGB_VAI, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, 
		KC_TRNS, 			KC_TRNS,		  KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,           KC_TRNS, KC_TRNS, KC_TRNS,  RGB_HUI, RGB_SAI),

	/* MacOS Raise
	 * ,-----------------------------------------------------------------------------------.
	 * | Ctrl |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Super|Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|  Backspace  |Lower |AltGr | Caps | Bckw | Forw |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_RAISE] = LAYOUT_planck_mit(
		KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,     KC_F11, 
		KC_LGUI, KC_VOLD, KC_UP,   KC_VOLU, KC_MPLY, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT,  KC_LBRC,    KC_RBRC, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,   KC_SLSH,    KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, KC_TRNS,  _BACKWARDS, _FORWARDS),

  /* MacOS Adjust
	 * ,-----------------------------------------------------------------------------------.
	 * | Debug| Btn1 | M Up | Btn2 |Scrll+| InfT |   /  |   1  |   2  |   3  |   -  | Lck1 |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Btn3 |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Lck2 |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB T| Cycle| Reset| Linux|  Esc | Bksp |   7  |   8  |   9  |Enter | Lck3 |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    |Lower |   0  |   .  |AltGr | Lck0 |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_ADJUST] = LAYOUT_planck_mit(
		DEBUG,   KC_BTN1, KC_MS_U,          KC_BTN2, KC_WH_U, INF_TGL, KC_PSLS,  KC_P1,   KC_P2,   KC_P3,    KC_PMNS,  M_D_LOWER, 
		KC_BTN3, KC_MS_L, KC_MS_D,          KC_MS_R, KC_WH_D, KC_TAB,  KC_PAST,  KC_P4,   KC_P5,   KC_P6,    KC_PPLS,  M_D_RAISE, 
		KC_TRNS, RGB_TOG, RGB_MODE_FORWARD, RESET,   M_TO_L,  KC_ESC,  KC_BSPC,  KC_P7,   KC_P8,   KC_P9,    KC_PENT,  M_D_ADJUST, 
		KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_SPC,             KC_TRNS, KC_P0,   KC_PDOT,  KC_RALT, M_D_BASE)

};

void set_led(uint8_t r, uint8_t g, uint8_t b, uint8_t i) {
  if (i < RGBLED_NUM) {
		rgblight_setrgb_at(r, g, b, i);
		// #ifdef CONSOLE_ENABLE
		// 	printf("set_led:%d,%d,%d,%d", r, g, b, i);
		// #endif
    // led[i].r = r;
    // led[i].g = g;
    // led[i].b = b;
  }
}

void suspend_power_down_user(void) {
    // rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    // rgb_matrix_set_suspend_state(false);
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
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
  /* idle_timer needs to be set one time */
  if(idle_timer == 0) idle_timer = timer_read();

  #ifdef BACKLIGHT_ENABLE
    if(led_on && timer_elapsed(idle_timer) > 30000) {
      halfmin_counter++;
      idle_timer = timer_read();
    }

    if(led_on && halfmin_counter >= BACKLIGHT_TIMEOUT * 2) {
			backlight_disable();
      led_on = false;
      halfmin_counter = 0;
    }
  #endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if(record->event.pressed) {
    #ifdef BACKLIGHT_ENABLE
      if(led_on == false) {
				backlight_enable();
        led_on = true;
      }
    #endif
    idle_timer = timer_read();
    halfmin_counter = 0;
  }

  #ifdef WPM_INDICATOR

    uint8_t wpm = get_current_wpm();

    if(wpm < 20) {
      set_led(WPM0_COLORS, LED08);
      set_led(LED_OFF_COLORS, LED09);
      set_led(LED_OFF_COLORS, LED10);
      set_led(LED_OFF_COLORS, LED11);
    } else if(wpm < 50) {
      set_led(WPM1_COLORS, LED08);
      set_led(WPM1_COLORS, LED09);
      set_led(LED_OFF_COLORS, LED10);
      set_led(LED_OFF_COLORS, LED11);
    } else if(wpm < 80) {
      set_led(WPM2_COLORS, LED08);
      set_led(WPM2_COLORS, LED09);
      set_led(WPM2_COLORS, LED10);
      set_led(LED_OFF_COLORS, LED11);
    } else {
      set_led(WPM3_COLORS, LED08);
      set_led(WPM3_COLORS, LED09);
      set_led(WPM3_COLORS, LED10);
      set_led(WPM3_COLORS, LED11);
    }
		rgblight_set();

  #endif


	/* Linux */
	switch (keycode) {
		case L_BASE:		if(record->event.pressed) {
			// TODO: what to do here? (base layer)
		}
		return false;
    case L_LOWER:
			if(record->event.pressed) {
				layer_on(_L_LOWER);
				#ifdef CONSOLE_ENABLE
					print("L_LOWER down\n");
				#endif
			} else {
				layer_off(_L_LOWER);
				#ifdef CONSOLE_ENABLE
					print("L_LOWER up\n");
				#endif
			}
			update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
			return false;

		case L_RAISE:
			if(record->event.pressed) {
				layer_on(_L_RAISE);
				#ifdef CONSOLE_ENABLE
					print("L_RAISE down\n");
				#endif
			} else {
				layer_off(_L_RAISE);
				#ifdef CONSOLE_ENABLE
					print("L_RAISE up\n");
				#endif
			}
			update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
			return false;

    case L_ADJUST:
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("L_ADJST down\n");
				#endif
				layer_on(_L_ADJUST);
			} else {
				#ifdef CONSOLE_ENABLE
					print("L_ADJST up\n");
				#endif
				layer_off(_L_ADJUST);
			}
			return false;

		case L_D_BASE:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case L_D_LOWER:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case L_D_RAISE:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case L_D_ADJUST:	if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;
		
		/* MacOS */
		case M_BASE:		if(record->event.pressed) {
			// TODO: what to do here? (base layer)
		}
		return false;

		case M_LOWER:
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("M_LOWER down\n");
				#endif
				layer_on(_M_LOWER);
			} else {
				#ifdef CONSOLE_ENABLE
					print("M_LOWER up\n");
				#endif
				layer_off(_M_LOWER);
			}
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
			return false;
				
		case M_RAISE:
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("M_RAISE down\n");
				#endif
				layer_on(_M_RAISE);
			} else {
				#ifdef CONSOLE_ENABLE
					print("M_RAISE up\n");
				#endif
				layer_off(_M_RAISE);
			}
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
			return false;

    case M_ADJUST:
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("M_ADJST down\n");
				#endif
				layer_on(_M_ADJUST);
			} else {
				#ifdef CONSOLE_ENABLE
					print("M_ADJST up\n");
				#endif
				layer_off(_M_ADJUST);
			}
			return false;

    case M_D_BASE:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case M_D_LOWER:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case M_D_RAISE:		if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;

		case M_D_ADJUST:  if(record->event.pressed) {
      // TODO: what to do here? (change default layer)
		}
		return false;


		/* Info Toggle */
		case INF_TGL: {
			if(record->event.pressed) {
				user_config.info_mode = !user_config.info_mode;
				eeconfig_update_user(user_config.raw);
				#ifdef CONSOLE_ENABL
					print("INF_TGL");
					if(user_config.info_mode) print("on\n");
					else 											print("off\n");
				#endif
			}
		} break;

		/* Switch from Linux to MacOS */
		case L_TO_M: {
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("LAYOUT: Mac\n");
				#endif
				user_config.linux_mode = false;
				if(user_config.info_mode) {
					#ifdef OS_INDICATOR
						set_led(MACOS_COLORS, LED12);
						rgblight_set();
					#endif
				}
				set_single_persistent_default_layer(_M_BASE); // TODO: integrate in user_config?
			}
		} break;

		/* Switch from MacOS to Linux */
		case M_TO_L: {
			if(record->event.pressed) {
				#ifdef CONSOLE_ENABLE
					print("LAYOUT: Linux\n");
				#endif
				user_config.linux_mode = true;
				if(user_config.info_mode) {
					#ifdef OS_INDICATOR
						set_led(LINUX_COLORS, LED12);
						rgblight_set();
					#endif
				}
				set_single_persistent_default_layer(_L_BASE);
			}
		} break;
	}
	return true;
}

layer_state_t layer_state_set_user(layer_state_t state) { // TODO: add correct colors
  #ifdef LAYER_INDICATOR
    if(user_config.info_mode) {
			#ifdef CONSOLE_ENABLE
				print("info_mode:on");
			#endif
      switch(biton32(state)) {
        case _L_BASE:
				case _M_BASE: {
					#ifdef CONSOLE_ENABLE
						print("layer:base\n");
					#endif
					/*if(rgblight_is_enabled()) {*/ // TODO: does this read the eeprom? (would be the wanted behaviour here)
						// rgblight_enable_noeeprom();
					/*}*/
          set_led(LAYER_BASE_COLORS, LED06);
          set_led(LAYER_BASE_COLORS, LED13);
        } break;
        case _L_LOWER:
				case _M_LOWER: {
					#ifdef CONSOLE_ENABLE
						print("layer:lower\n");
					#endif
					// rgblight_disable_noeeprom();
          set_led(LAYER_LOWER_COLORS, LED06);
          set_led(LAYER_LOWER_COLORS, LED13);
        } break;
        case _L_RAISE:
				case _M_RAISE: {
					#ifdef CONSOLE_ENABLE
						print("layer:raise\n");
					#endif
					// rgblight_disable_noeeprom();
          set_led(LAYER_RAISE_COLORS, LED06);
          set_led(LAYER_RAISE_COLORS, LED13);
        } break;
        case _L_ADJUST:
				case _M_ADJUST: {
					#ifdef CONSOLE_ENABLE
						print("layer:adjst\n");
					#endif
					// rgblight_disable_noeeprom();
          set_led(LAYER_ADJUST_COLORS, LED06);
          set_led(LAYER_ADJUST_COLORS, LED13);
        } break;
      }
			rgblight_set();
    } else {
			#ifdef CONSOLE_ENABLE
				print("info_mode:off");
			#endif
		}
  #endif
  return state;
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