/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum corne_layers {
  _QWERTY = 0,
  _QWERTY_LHOME = 1,
  _QWERTY_RHOME = 2,
  _NUMS = 3,
  _NAV = 4,
  _MEDIA = 5
};

enum custom_keycodes {
  HELLO = SAFE_RANGE,
};

// Shorthand aliases to keep keymap columns a consistent width
#define L_LHOM  MO(_QWERTY_LHOME)
#define L_RHOM  MO(_QWERTY_RHOME)
#define L_MED   MO(_MEDIA)
#define HYPRNO  MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, KC_NO)
#define NO_OP   XXXXXXX
#define TRNS    _______

// Base QWERTY rows
#define ROW_BASE_L0 KC_ESC, KC_Q, KC_W, KC_E, KC_R, KC_T
#define ROW_BASE_R0 KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC
#define ROW_BASE_L1 KC_TAB, KC_A, KC_S, KC_D, KC_F, KC_G
#define ROW_BASE_R1 KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT
#define ROW_BASE_L2 KC_X, KC_Z, KC_X, KC_C, KC_V, KC_B
#define ROW_BASE_R2 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, L_RHOM
#define THUMB_BASE_L L_RHOM, L_LHOM, KC_SPC
#define THUMB_BASE_R KC_ENT, MO(_NUMS), MO(_NAV)

// Home-row modifier overrides
#define ROW_LHOME_L1 KC_TAB, KC_LSFT, KC_LCTL, KC_LCMD, KC_LOPT, KC_G
#define ROW_RHOME_R1 KC_H, KC_ROPT, KC_RCMD, KC_RCTL, KC_RSFT, KC_QUOT
#define ROW_HOME_R2 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, HYPRNO
#define THUMB_HOME_L TRNS, TRNS, KC_SPC
#define THUMB_HOME_R KC_ENT, MO(_NUMS), MO(_NAV)

// Number layer
#define ROW_NUMS_L0 TRNS, KC_1, KC_2, KC_3, KC_4, KC_5
#define ROW_NUMS_R0 KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC
#define ROW_NUMS_L1 TRNS, KC_LSFT, KC_LCTL, KC_LCMD, KC_LOPT, KC_LCBR
#define ROW_NUMS_R1 KC_RCBR, KC_ROPT, KC_RCMD, KC_RCTL, KC_RSFT, KC_NUHS
#define ROW_NUMS_L2 NO_OP, KC_GRV, KC_UNDS, NO_OP, KC_LBRC, KC_RBRC
#define ROW_NUMS_R2 KC_PLUS, KC_MINS, KC_PEQL, KC_UNDS, KC_GRV, NO_OP
#define THUMB_NUMS_L TRNS, TRNS, KC_SPC
#define THUMB_NUMS_R KC_ENT, TRNS, MO(_NAV)

// Navigation layer
#define ROW_NAV_L0 TRNS, NO_OP, NO_OP, NO_OP, NO_OP, DT_PRNT
#define ROW_NAV_R0 NO_OP, NO_OP, KC_UP, NO_OP, NO_OP, TRNS
#define ROW_NAV_L1 TRNS, TRNS, TRNS, TRNS, TRNS, DT_UP
#define ROW_NAV_R1 NO_OP, KC_LEFT, KC_DOWN, KC_RGHT, NO_OP, NO_OP
#define ROW_NAV_L2 NO_OP, NO_OP, NO_OP, NO_OP, NO_OP, DT_DOWN
#define ROW_NAV_R2 NO_OP, NO_OP, NO_OP, NO_OP, NO_OP, NO_OP
#define THUMB_NAV_L TRNS, TRNS, KC_SPC
#define THUMB_NAV_R KC_ENT, L_MED, TRNS

// Media layer
#define ROW_MEDIA_L0 RGB_TOG, RGB_MOD, RGB_HUI, RGB_SPI, NO_OP, NO_OP
#define ROW_MEDIA_R0 NO_OP, KC_VOLD, KC_MUTE, KC_VOLU, NO_OP, NO_OP
#define ROW_MEDIA_L1 NO_OP, RGB_RMOD, RGB_HUD, RGB_SPD, NO_OP, NO_OP
#define ROW_MEDIA_R1 NO_OP, KC_MPRV, KC_MPLY, KC_MNXT, NO_OP, NO_OP
#define ROW_MEDIA_L2 NO_OP, NO_OP, NO_OP, NO_OP, NO_OP, KC_F3
#define ROW_MEDIA_R2 NO_OP, NO_OP, NO_OP, NO_OP, NO_OP, HELLO
#define THUMB_MEDIA_L TRNS, TRNS, KC_SPC
#define THUMB_MEDIA_R KC_ENT, TRNS, TRNS

// Helper to compose row aliases without tripping macro argument counting.
#define LAYOUT_ROWS(r0l, r0r, r1l, r1r, r2l, r2r, thl, thr) \
  LAYOUT_split_3x6_3( \
    r0l, r0r, \
    r1l, r1r, \
    r2l, r2r, \
    thl, thr \
  )

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case HELLO:
      if (record->event.pressed) {
        SEND_STRING("hello");
      }
      return false;
    default:
      return true;
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
  case _QWERTY:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    break;
  case _QWERTY_LHOME:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_RED);
    break;
  case _QWERTY_RHOME:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
    break;
  case _NUMS:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_ORANGE);
    break;
  case _NAV:
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  default:
    rgblight_config.raw = eeconfig_read_rgblight();
    if (rgblight_config.enable) {
      rgblight_sethsv_noeeprom(HSV_WHITE);
    } else {
      rgblight_disable_noeeprom();
    }
    break;
  }
  return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_ROWS(
    ROW_BASE_L0, ROW_BASE_R0,
    ROW_BASE_L1, ROW_BASE_R1,
    ROW_BASE_L2, ROW_BASE_R2,
    THUMB_BASE_L, THUMB_BASE_R
  ),

  [_QWERTY_LHOME] = LAYOUT_ROWS(
    ROW_BASE_L0, ROW_BASE_R0,
    ROW_LHOME_L1, ROW_BASE_R1,
    ROW_BASE_L2, ROW_HOME_R2,
    THUMB_HOME_L, THUMB_HOME_R
  ),

  [_QWERTY_RHOME] = LAYOUT_ROWS(
    ROW_BASE_L0, ROW_BASE_R0,
    ROW_BASE_L1, ROW_RHOME_R1,
    ROW_BASE_L2, ROW_HOME_R2,
    THUMB_HOME_L, THUMB_HOME_R
  ),

  [_NUMS] = LAYOUT_ROWS(
    ROW_NUMS_L0, ROW_NUMS_R0,
    ROW_NUMS_L1, ROW_NUMS_R1,
    ROW_NUMS_L2, ROW_NUMS_R2,
    THUMB_NUMS_L, THUMB_NUMS_R
  ),

  [_NAV] = LAYOUT_ROWS(
    ROW_NAV_L0, ROW_NAV_R0,
    ROW_NAV_L1, ROW_NAV_R1,
    ROW_NAV_L2, ROW_NAV_R2,
    THUMB_NAV_L, THUMB_NAV_R
  ),

  [_MEDIA] = LAYOUT_ROWS(
    ROW_MEDIA_L0, ROW_MEDIA_R0,
    ROW_MEDIA_L1, ROW_MEDIA_R1,
    ROW_MEDIA_L2, ROW_MEDIA_R2,
    THUMB_MEDIA_L, THUMB_MEDIA_R
  )

};
