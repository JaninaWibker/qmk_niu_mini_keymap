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

enum layers {
	/* Linux layers */
	_L_BASE,
	_L_LOWER,
	_L_RAISE,
	_L_ADJUST,

	/* MacOS layers */
	_M_BASE,
	_M_LOWER,
	_M_RAISE,
	_M_ADJUST
};

enum keycodes {
	/* Linux layer switches */
	L_BASE = SAFE_RANGE,
	L_LOWER,
	L_RAISE,
	L_ADJUST,

	L_D_BASE,
	L_D_LOWER,
	L_D_RAISE,
	L_D_ADJUST,

	/* MacOS layer switches */
	M_BASE,
	M_LOWER,
	M_RAISE,
	M_ADJUST,

	M_D_BASE,
	M_D_LOWER,
	M_D_RAISE,
	M_D_ADJUST,

	/* toggle additional information via rgb leds ON/OFF */
	INF_TGL,
	/* switch from Linux layout to MacOS layout */
	L_TO_M,
	/* switch from MacOs layout to Linux layout */
	M_TO_L
};

/* backslash key on both Linux and MacOS */
#define _L_BACKSLASH RALT(7)
#define _M_BACKSLASH LSFT(RALT(7))

#define _BACKWARDS LCTL(KC_PGUP)
#define _FORWARDS  LCTL(KC_PGDN)

/* apple fn key (mapped to F20, needs to be software remapped) */
#define _M_FN				 KC_F20

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/* Linux - Base
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn1 | Ctrl | Super|  Alt | Raise|    Space    | Lower|AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_BASE] = LAYOUT_planck_mit(
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, 
		KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,    KC_LBRC,  KC_RBRC, 
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, 
		L_LOWER, KC_LCTL, KC_LGUI, KC_LALT, L_RAISE, KC_SPC,     L_LOWER, KC_RALT, KC_CAPS, KC_LEFT,  KC_RGHT),

	/* Linux Lower
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |  \*  |   ^  |   -  |   =  |   \  | Left | Down |  Up  |Right |   ;  |  '   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB C| BL C |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Lower| Ctrl | Super|  Alt | Raise|    Enter    |Lower |AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_LOWER] = LAYOUT_planck_mit(
		KC_TAB,  KC_1,    	   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL, 
		KC_RCTL, _L_BACKSLASH, KC_GRV,  KC_MINS, KC_EQL,  KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_SCLN, KC_QUOT, 
		KC_TRNS, RGB_TOG,			 BL_TOGG, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, 
		KC_TRNS, KC_TRNS,			 KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,           KC_TRNS, KC_TRNS, KC_TRNS,  RGB_HUD, RGB_HUI),

	/* Linux Raise
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Lower| Ctrl | Super|  Alt | Raise|  Backspace  |Lower |AltGr | Caps | Bckw | Forw |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_RAISE] = LAYOUT_planck_mit(
		KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,     KC_F11, 
		KC_RCTL, KC_VOLD, KC_UP,   KC_VOLU, KC_MPLY, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT,  KC_LBRC,    KC_RBRC, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,   KC_SLSH,    KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, KC_TRNS,  _BACKWARDS, _FORWARDS),

	/* Linux Adjust
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  | Btn1 | M Up | Btn2 |Scrll+| InfT |   /  |   1  |   2  |   3  |   -  | Lck1 |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Lck2 |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB T| BL T | Reset|  Mac |  Esc | Bksp |   7  |   8  |   9  |Enter | Lck3 |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * | Lower| Ctrl | Super|  Alt | Raise|    Space    |Lower |   0  |   .  |AltGr | Lck0 |
	 * `-----------------------------------------------------------------------------------'
   */
	[_L_ADJUST] = LAYOUT_planck_mit(
		KC_TAB,  KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, KC_NO,  KC_PSLS,  KC_P1,   KC_P2,   KC_P3,    KC_PMNS, L_D_LOWER, 
		KC_RCTL, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_TAB, KC_PAST,  KC_P4,   KC_P5,   KC_P6,    KC_PPLS, L_D_RAISE, 
		KC_TRNS, RGB_TOG, BL_TOGG, RESET,   L_TO_M,  KC_ESC, KC_BSPC,  KC_P7,   KC_P8,   KC_P9,    KC_PENT, L_D_ADJUST, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,           KC_TRNS, KC_P0,   KC_PDOT,  KC_RALT, L_D_BASE),

	/* MacOS - Base
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    | Lower|AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_BASE] = LAYOUT_planck_mit(
		KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T, KC_Y, KC_U,    KC_I,    KC_O,    KC_P,     KC_BSPC, 
		KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G, KC_H, KC_J,    KC_K,    KC_L,    KC_LBRC,  KC_RBRC, 
		KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N, KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT, 
		_M_FN,   KC_LCTL, KC_LALT, KC_LGUI, M_RAISE, KC_SPC,     M_LOWER, KC_RALT, KC_CAPS, KC_LEFT,  KC_RGHT),

	/* MacOS Lower
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |  \*  |   ^  |   -  |   =  |   \  | Left | Down |  Up  |Right |   ;  |  '   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB C| BL C |  Ins | Home | P Up |P Down| End  |   ,  |   .  |   /  |Enter |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Enter    |Lower |AltGr | Caps | Left |Right |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_LOWER] = LAYOUT_planck_mit(
		KC_TAB,  KC_1,   		   KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,     KC_0,    KC_DEL, 
		KC_RCTL, _M_BACKSLASH, KC_GRV,  KC_MINS, KC_EQL,  KC_BSLS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,  KC_SCLN, KC_QUOT, 
		KC_TRNS, RGB_TOG,		   BL_TOGG, KC_INS,  KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT, 
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS, KC_TRNS, KC_ENT,           KC_TRNS, KC_TRNS, KC_TRNS,  RGB_HUD, RGB_HUI),

	/* MacOS Raise
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |Vol Up|  Up  |VolDwn| Play |      |      |      |      |      |   [  |  ]   |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| Left | Down | Right| Mute |  Esc |Enter | End  |   ,  |   .  |   /  | F12  |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|  Backspace  |Lower |AltGr | Caps | Bckw | Forw |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_RAISE] = LAYOUT_planck_mit(
		KC_TAB,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,    KC_F10,     KC_F11, 
		KC_TRNS, KC_VOLD, KC_UP,   KC_VOLU, KC_MPLY, KC_GRV,  KC_MINS, KC_EQL,  KC_SCLN, KC_QUOT,  KC_LBRC,    KC_RBRC, 
		KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_MUTE, KC_ESC,  KC_ENT,  KC_BSLS, KC_COMM, KC_DOT,   KC_SLSH,    KC_F12, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_BSPC,          KC_TRNS, KC_TRNS, KC_TRNS,  _BACKWARDS, _FORWARDS),


  /* MacOS Adjust
	 * ,-----------------------------------------------------------------------------------.
	 * | Tab  | Btn1 | M Up | Btn2 |Scrll+| InfT |   /  |   1  |   2  |   3  |   -  | Lck1 |
	 * |------+------+------+------+------+-------------+------+------+------+------+------|
	 * | Ctrl |M Left|M Down|MRight|Scrll-|  Tab |   *  |   4  |   5  |   6  |   +  | Lck2 |
	 * |------+------+------+------+------+------|------+------+------+------+------+------|
	 * | Shift| RGB T| BL T | Reset| Linux|  Esc | Bksp |   7  |   8  |   9  |Enter | Lck3 |
	 * |------+------+------+------+------+------+------+------+------+------+------+------|
	 * |  Fn  | Ctrl |  Alt | Super| Raise|    Space    |Lower |   0  |   .  |AltGr | Lck0 |
	 * `-----------------------------------------------------------------------------------'
   */
	[_M_ADJUST] = LAYOUT_planck_mit(
		KC_TAB,  KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, INF_TGL, KC_PSLS,  KC_P1,   KC_P2,   KC_P3,    KC_PMNS,  M_D_LOWER, 
		KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_TAB,  KC_PAST,  KC_P4,   KC_P5,   KC_P6,    KC_PPLS,  M_D_RAISE, 
		KC_TRNS, RGB_TOG, BL_TOGG, RESET,   M_TO_L,  KC_ESC,  KC_BSPC,  KC_P7,   KC_P8,   KC_P9,    KC_PENT,  M_D_ADJUST, 
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SPC,             KC_TRNS, KC_P0,   KC_PDOT,  KC_RALT, M_D_BASE)

};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	/* Linux */
	switch (keycode) {
		case L_BASE:		if(record->event.pressed) {
			// TODO: what to do here? (base layer)
		}
		return false;
		case L_LOWER:		if(record->event.pressed) {
			layer_on(_L_LOWER);
			update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
		} else {
			layer_off(_L_LOWER);
			update_tri_layer(_L_LOWER, _L_RAISE, _L_ADJUST);
		}
		return false;
		case L_RAISE:		if(record->event.pressed) {
			layer_on(_M_RAISE);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
		} else {
			layer_off(_M_RAISE);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
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
			// TODO: what to do here?
		}
		return false;
		case M_LOWER:		if(record->event.pressed) {
			layer_on(_M_LOWER);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
		} else {
			layer_off(_M_LOWER);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
		}
		return false;
		case M_RAISE:		if(record->event.pressed) {
			layer_on(_M_RAISE);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
		} else {
			layer_off(_M_RAISE);
			update_tri_layer(_M_LOWER, _M_RAISE, _M_ADJUST);
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

		} break;

		/* Switch from Linux to MacOS */
		case L_TO_M: {
			set_single_persistent_default_layer(_M_BASE);
		} break;

		/* Switch from MacOS to Linux */
		case M_TO_L: {
			set_single_persistent_default_layer(_L_BASE);
		} break;
	}
	return true;
}

void led_set_user(uint8_t usb_led) {

	if (usb_led & (1 << USB_LED_NUM_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_COMPOSE)) {
		
	} else {
		
	}

	if (usb_led & (1 << USB_LED_KANA)) {
		
	} else {
		
	}

}