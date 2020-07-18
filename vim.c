/*
 * The following code is a derivative work of the code from xton <https://github.com/xton>,
 * which is licensed under GPLv2. This code therefore is also licensed under the terms of
 * the GNU Public License, version 2.
 * 
 * Copyright 2015-2017 Christon DeWan
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

#include "vim.h"

#define PRESS(kc) register_code(kc)
#define RELEASE(kc) unregister_code(kc)

static void TAP(uint16_t keycode) {
    PRESS(keycode);
    RELEASE(keycode);
}

static void CMD(uint16_t keycode) {
  PRESS(KC_LGUI);
    TAP(keycode);
  RELEASE(KC_LGUI);
}

static void CTRL(uint16_t keycode) {
  PRESS(KC_LCTRL);
    TAP(keycode);
  RELEASE(KC_LCTRL);
}

static void SHIFT(uint16_t keycode) {
  PRESS(KC_LSHIFT);
    TAP(keycode);
  RELEASE(KC_LSHIFT);
}

static void ALT(uint16_t keycode) {
  PRESS(KC_LALT);
    TAP(keycode);
  RELEASE(KC_LALT);
}

static void edit(void) {
  vstate = VIM_NORMAL;
  // this isn't going into "normal mode". 
  // Insert mode is different from all other modes as it is achieved by actual qmk layers
  // instead of just the vstate variable. The whole vim emulation is split into two layers
  // (or group of layers) which are the normal layer(s) and the seperate vim layer.
  // Setting vstate to VIM_NORMAL makes sure that once the vim layer is entered once again
  // normal mode is used. Setting this does not impact "insert mode" in any way as it's on
  // a whole different qmk layer.
  layer_clear();
  layer_on(vim_insert_layer());
  // is clearing the layer actually necessary? would something "less aggressive" also work?
}

static void change_state(uint16_t new_state) {
  #ifdef VIM_CALL_LAYER_STATE_CHANGE_ON_MODE_SWITCH
    layer_state_set_user(layer_state);
  #endif
  vstate = new_state;
}

static void shifted_movement(uint16_t keycode) {
  switch(keycode) {
    case VIM_W: {
      PRESS(KC_LSHIFT);
        PRESS(KC_LALT);
          TAP(KC_RIGHT);
          TAP(KC_RIGHT);
          TAP(KC_LEFT);
        RELEASE(KC_LALT);
        TAP(KC_RIGHT);
      RELEASE(KC_LSHIFT);
    } break;
    case VIM_B: {
      PRESS(KC_LALT);
        SHIFT(KC_LEFT);
      RELEASE(KC_LALT);
    } break;
    case VIM_E: {
      PRESS(KC_LALT);
        TAP(KC_RIGHT);
      RELEASE(KC_LALT);
    } break;
    case VIM_H: {
      SHIFT(KC_LEFT);
    } break;
    case VIM_J: {
      SHIFT(KC_DOWN);
    } break;
    case VIM_K: {
      SHIFT(KC_UP);
    } break;
    case VIM_L: {
      SHIFT(KC_RIGHT);
    } break;
  }
}

// TODO: think about the comma/period stuff, should such functionality exist or not?

static void copy(void) {
  if(!is_mac()) {
    CTRL(KC_C);
  } else {
    CMD(KC_C);
  }
}

static void cut(void) {
  if(!is_mac()) {
    CTRL(KC_X);
  } else {
    CMD(KC_X);
  }
}

static void paste(void) {
  if(!is_mac()) {
    CTRL(KC_V);
  } else {
    CMD(KC_V);
  }
}

static void undo(void) {
  if(!is_mac()) {
    CTRL(KC_Z);
  } else {
    CMD(KC_Z);
  }
}

static void redo(void) {
  if(!is_mac()) {
    PRESS(KC_LCTRL);
      SHIFT(KC_Z);
    RELEASE(KC_LCTRL);
  } else {
    PRESS(KC_LGUI);
      SHIFT(KC_Z);
    RELEASE(KC_LGUI);
  }
}

uint16_t vstate = VIM_NORMAL;
static bool yank_was_lines = false;
static bool SHIFTED = false;
static uint32_t mod_override_layer_state = 0;
static uint16_t mod_override_triggering_key = 0;

/*
 * TODO: add description
 */
bool handle_vim_keycodes(uint16_t keycode, keyrecord_t *record) {
  // TODO: check if modifier and do some stuff then
  /****** mod passthrough *****/
  // first check if currently in normal mode and then check if pressed key is actually a modifier
  if(record->event.pressed && layer_state_is(vim_cmd_layer()) && (IS_MOD(keycode) || keycode == LSFT(KC_LALT))) {
    // remember which layer was active and which key was pressed (which "normal mode" layer)
    mod_override_layer_state = layer_state;
    mod_override_triggering_key = keycode;
    layer_clear(); // go to base layer
    return true; // let the event be handled elsewhere if needed
  }
  // check if should disable mod passthrough by first checking if passthrough is active, event was keyrelease and the keycode is the same as the one activating the the passthrough
   // TODO: could this cause problems when not releasing modifiers in the reverse order like shift -> alt -> !shift -> !alt?
  if(mod_override_layer_state && !record->event.pressed && keycode == mod_override_triggering_key) {
    // reactivate the layer that was active before (why can't this just be set to vim_cmd_layer()?)
    layer_state_set(mod_override_layer_state);
    mod_override_layer_state = 0;
    mod_override_triggering_key = 0;
    return true; // let the event be handled elsewhere if needed
  }

  if(VIM_NORMAL <= keycode && keycode < VIM_SAFE_RANGE) {
    if(keycode == VIM_SHIFT) {
      SHIFTED = record->event.pressed;
      return false;
    }

    if (record->event.pressed) {
      if(keycode == VIM_NORMAL) {
        // turn on normal mode layer
        layer_on(vim_cmd_layer());

        change_state(VIM_NORMAL);

        // reset state
        yank_was_lines = false;
        SHIFTED = false;
        mod_override_layer_state = 0;
        mod_override_triggering_key = 0;

        return false;
      } else if(keycode == VIM_ESC && vstate == VIM_NORMAL) {
        // exit vim mode
        layer_clear();
      }

      raw_handle_vim_keycodes(keycode);
    } else {
      // no need to call clear_keyboard() as all keydown events have an accompanying keyup event
      // TODO: should this let the key release propagate up?
    }
    return false; // event was handled and does not need to propagate further
  } else {
    return true; // let the event be handled elsewhere if needed
  }
}

/*
 * This handles vim keycodes without considering modifier keys.
 * Handling modifiers and anything else should be done where this function is used
 * This function uses the global variables:
 * - vstate (both read and write)
 * - yank_was_lines (both read and write)
 * - SHIFTED (only reading)
 * The function directly performs the keypresses needed for the expected action
 */
void raw_handle_vim_keycodes(uint16_t keycode) {
  switch(vstate) {
    case VIM_NORMAL: {
    /***************
     * normal mode *
     ***************/
      switch(keycode) {
        case VIM_A: {
          if(SHIFTED) {
            TAP(KC_END);
          } else {
            TAP(KC_RIGHT);
          }
          edit();
        } break;
        case VIM_I: {
          if(SHIFTED) {
            TAP(KC_HOME);
          }
          edit();
        } break;

        case VIM_C: {
          if(SHIFTED) {
            SHIFT(KC_END);
            cut();
            edit();
          } else {
            change_state(VIM_C);
          }
        } break;
        case VIM_D: {
          if(SHIFTED) {
            SHIFT(KC_END);
            cut();
          } else {
            change_state(VIM_D);
          }
        } break;

        case VIM_V: {
          if(SHIFTED) {
            TAP(KC_HOME);
            SHIFT(KC_END);
            change_state(VIM_VS);
          } else {
            change_state(VIM_V);
          }
        } break;

        case VIM_B: {
          ALT(KC_LEFT);
        } break;
        case VIM_W: {
          PRESS(KC_LALT);
            TAP(KC_RIGHT);
            TAP(KC_RIGHT);
            TAP(KC_LEFT);
          RELEASE(KC_LALT);
        } break;
        case VIM_E: {
          if(SHIFTED) {
            ALT(KC_RIGHT);
          } else { // deviating from vim standard: shifted e is inverse of non-shifted e
            PRESS(KC_LALT);
              TAP(KC_LEFT);
              TAP(KC_LEFT);
              TAP(KC_RIGHT);
            RELEASE(KC_LALT);
          }
        } break;

        case VIM_G: {
          if(SHIFTED) {
            TAP(KC_PGDOWN);
          } else {
            change_state(VIM_G);
          }
        } break;


        case VIM_H: {
          TAP(KC_LEFT);
        } break;
        case VIM_J: {
          if(SHIFTED) {
            TAP(KC_HOME);
            TAP(KC_DOWN);
            TAP(KC_BSPC);
            TAP(KC_SPC);
          } else {
            TAP(KC_DOWN);
          }
        } break;
        case VIM_K: {
          TAP(KC_UP);
        } break;
        case VIM_L: {
          TAP(KC_RIGHT);
        } break;

        case VIM_O: {
          // TODO: decide wether to implement my kind of custom version of o/O or implement the default
        } break;

        case VIM_P: {
          if(SHIFTED) {
            if(yank_was_lines) {
              TAP(KC_HOME);
              TAP(KC_ENTER);
              TAP(KC_UP);
              paste();
            } else {
              TAP(KC_LEFT);
              paste();
            }
          } else {
            if(yank_was_lines) {
              TAP(KC_END);
              TAP(KC_ENTER);
              TAP(KC_DOWN);
              paste();
            } else {
              paste();
            }
          }
        } break;
        case VIM_Y: {
          if(SHIFTED) {
            TAP(KC_HOME);
            SHIFT(KC_DOWN);
            copy();
          } else {
            change_state(VIM_Y);
          }
        } break;
        case VIM_X: {
          TAP(KC_BSPC);
        } break;

        case VIM_S: {
          // TODO: idk
        } break;
        case VIM_U: {
          if(SHIFTED) {
            redo();
          } else {
            undo();
          }
        } break;
      }
    } break;

    case VIM_V: {
      /***************
       * visual mode *
       ***************/
      switch(keycode) {

        case VIM_ESC:
        case VIM_V: {
          change_state(VIM_NORMAL);
        } break;

        case VIM_I: {
          change_state(VIM_VI);
        }

        case VIM_D:
        case VIM_X: {
          yank_was_lines = false;
          cut();
        } break;

        case VIM_P: {
          paste();
          change_state(VIM_NORMAL);
        } break;

        case VIM_Y: {
          SHIFT(KC_LEFT);
          copy();
          TAP(KC_RIGHT);
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;

        case VIM_B: {
          PRESS(KC_LSHIFT);
          ALT(KC_LEFT);
          RELEASE(KC_LSHIFT);
          
        } break;
        case VIM_W: {
          PRESS(KC_LSHIFT);
          PRESS(KC_LALT);
          TAP(KC_RIGHT);
          TAP(KC_RIGHT);
          TAP(KC_LEFT);
          RELEASE(KC_LALT);
          TAP(KC_RIGHT);
          RELEASE(KC_LSHIFT);
        } break;
        case VIM_E: {
          PRESS(KC_LSHIFT);
          ALT(KC_RIGHT);
          RELEASE(KC_LSHIFT);
        } break;

        case VIM_H: {
          SHIFT(KC_LEFT);
        } break;
        case VIM_J: {
          SHIFT(KC_DOWN);
        } break;
        case VIM_K: {
          SHIFT(KC_UP);
        } break;
        case VIM_L: {
          SHIFT(KC_RIGHT);
        } break;

        default: break; // NOP
      }
    } break;
    case VIM_VI: {
      /*****************************
       * visual mode (inside word) *
       *****************************/
      switch(keycode) {
        case VIM_W: {
          PRESS(KC_LALT);
          TAP(KC_LEFT);
          SHIFT(KC_RIGHT);
          RELEASE(KC_LALT);
        } break;
        default: {
          change_state(VIM_V);
        } break;
      }
    } break;
    case VIM_VS: {
      /*****************************
       * visual (line) mode - <S>V *
       *****************************/
      switch(keycode) {
        case VIM_V:
        case VIM_ESC: {
          change_state(VIM_NORMAL);
        } break;

        case VIM_D:
        case VIM_X: {
          cut();
          yank_was_lines = true;
          change_state(VIM_NORMAL);
        } break;

        case VIM_J: {
          SHIFT(KC_DOWN);
        } break;
        case VIM_K: {
          SHIFT(KC_UP);
        } break;

        case VIM_Y: {
          copy();
          yank_was_lines = true;
          change_state(VIM_NORMAL);
        } break;
        case VIM_P: {
          paste();
          change_state(VIM_NORMAL);
        } break;
      }
    } break;

    case VIM_C: {
      /****************
       * change stuff *
       ****************/
      switch(keycode) {
        case VIM_W:
        case VIM_B:
        case VIM_E:
        case VIM_H:
        case VIM_J:
        case VIM_K:
        case VIM_L: {
          shifted_movement(keycode);
          cut();
          yank_was_lines = false;
          edit();
        } break;

        case VIM_C: {
          TAP(KC_END);
          SHIFT(KC_HOME);
          cut();
          yank_was_lines = false;
          edit();
        }

        case VIM_I: {
          change_state(VIM_CI);
        } break;

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    /******************************
     * change stuff (inside word) *
     ******************************/
    case VIM_CI: {
      switch(keycode) {
        case VIM_W: {
          PRESS(KC_LALT);
          TAP(KC_LEFT);
          SHIFT(KC_RIGHT);
          RELEASE(KC_LALT);
          cut();
          yank_was_lines = false;
          edit();
        }

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    case VIM_D: {
      /****************
       * delete stuff *
       ****************/
      switch(keycode) {
        case VIM_W:
        case VIM_B:
        case VIM_E:
        case VIM_H:
        case VIM_J:
        case VIM_K:
        case VIM_L: {
          shifted_movement(keycode);
          cut();
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;

        case VIM_D: {
          TAP(KC_END);
          SHIFT(KC_HOME);
          cut();
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;

        case VIM_I: {
          change_state(VIM_CI);
        } break;

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    case VIM_DI: {
      /******************************
       * delete stuff (inside word) *
       ******************************/
      switch(keycode) {
        case VIM_W: {
          PRESS(KC_LALT);
          TAP(KC_LEFT);
          SHIFT(KC_RIGHT);
          RELEASE(KC_LALT);
          cut();
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    
    case VIM_G: {
      /*******************************
       * gigantic amount of commands *
       *******************************/
      switch(keycode) {
        case VIM_G: {
          TAP(KC_PGUP);
          change_state(VIM_NORMAL);
        } break;

        case VIM_H: {
          // TODO: idk
          change_state(VIM_NORMAL);
        } break;
        case VIM_J: {
          TAP(KC_DOWN); // same as j in normal mode (in vim gj works with wrapped lines but this is the default behaviour in most editors)
          change_state(VIM_NORMAL);
        } break;
        case VIM_K: {
          TAP(KC_UP); // same as k in normal mode (in vim gk works with wrapped lines but this is the default behaviour in most editors)
          change_state(VIM_NORMAL);
        } break;
        case VIM_L: {
          // TODO: idk
          change_state(VIM_NORMAL);
        } break;

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    case VIM_Y: {
      /**************
       * yank stuff *
       **************/
      switch(keycode) {
        case VIM_W:
        case VIM_J:
        case VIM_L:
        case VIM_E: {
          shifted_movement(keycode);
          cut();
          TAP(KC_LEFT);
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;
        case VIM_B:
        case VIM_H:
        case VIM_K: {
          shifted_movement(keycode);
          cut();
          TAP(KC_RIGHT);
          yank_was_lines = false;
          change_state(VIM_NORMAL);
        } break;

        case VIM_Y: {
          TAP(KC_HOME);
          SHIFT(KC_END);
          copy();
          yank_was_lines = true;
          change_state(VIM_NORMAL);
        } break;

        default: {
          change_state(VIM_NORMAL);
        } break;
      }
    } break;
    
    default: {
      /* NOP */
    } break;
  }
}