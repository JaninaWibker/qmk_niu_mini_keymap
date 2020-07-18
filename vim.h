#pragma once

#include QMK_KEYBOARD_H

enum vim_keycodes {
  VIM_ENTER = SAFE_RANGE + 20, // what is this used for?
  VIM_NORMAL,
  VIM_A, // append
  VIM_B, // backwards word
  VIM_C, // change
  VIM_CI, // change inside
  VIM_D, // delete
  VIM_DI, // delete inside
  VIM_E, // end of word
  VIM_F, // not supported
  VIM_G, // macros
  VIM_H, // left
  VIM_I, // insert mode
  VIM_J, // down
  VIM_K, // up
  VIM_L, // right
  VIM_N, // not supported
  VIM_O, // new line above/below
  VIM_P, // paste
  VIM_S, // TODO: idk
  VIM_T, // not supported
  VIM_U, // undo
  VIM_V, // visual mode
  VIM_VI, // visual inside
  VIM_VS, // visual-line
  VIM_W, // forwards word
  VIM_X, // delete
  VIM_Y, // yank
  VIM_PERIOD, // TODO: idk
  VIM_COMMA, // TODO: idk
  VIM_SPACE, // TODO: handle this
  VIM_SHIFT, // using this to avoid side-effects of supprting real shift
  VIM_ESC, // what is this used for?
  VIM_SAFE_RANGE // non-vim keycodes start here; this is used to create a range of possible vim keycodes: VIM_NORMAL <= keycode && keycode < VIM_SAFE_RANGE
};

void raw_handle_vim_keycodes(uint16_t keycode);

bool handle_vim_keycodes(uint16_t keycode, keyrecord_t *record);

// must be implemented; this function is used to switch into normal mode
extern uint8_t vim_cmd_layer(void);

// must be implemented; this function is used to switch into insert mode
extern uint8_t vim_insert_layer(void);

// must be implemented; this function allows choosing correctly between cmd and ctrl
extern bool is_mac(void);

// current mode: normal, visual, visual-line, ... (and mode-like things for combos like g or d)
extern uint16_t vstate;