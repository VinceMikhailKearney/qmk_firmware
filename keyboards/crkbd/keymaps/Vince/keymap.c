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

#define RBG_VAL 120
layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
  case _QWERTY:
    // Green
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  case _QWERTY_LHOME:
    // Red
    rgblight_enable_noeeprom();	
    rgblight_sethsv_noeeprom(HSV_RED);
    break;
  case _QWERTY_RHOME:
    // Blue
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
    break;
  case _NUMS:
    // Blue
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_ORANGE);
    break;
  case _NAV:
    // Blue
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_PURPLE);
    break;
  default:
    // White
    //Read RGB Light State
    rgblight_config.raw = eeconfig_read_rgblight();
    //If enabled, set white
    if (rgblight_config.enable) {
		rgblight_sethsv_noeeprom(HSV_WHITE);
	} else { //Otherwise go back to disabled
		rgblight_disable_noeeprom();
	}
    break;
  }
  return state;
}

void tap(uint16_t keycode){
    register_code(keycode);
    unregister_code(keycode);
};

// Place `KC_CYCLE_LAYERS` as a keycode in your keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_TAB,  KC_A,     KC_S,   KC_D,    KC_F,    KC_G,                          KC_H,       KC_J,       KC_K,       KC_L,       KC_SCLN,     KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      KC_X,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,     KC_COMM,  KC_DOT, KC_SLSH,  HYPR_T(KC_NO),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                     MO(_QWERTY_RHOME), MO(_QWERTY_LHOME),  KC_SPC,     KC_ENT,   MO(_NUMS), MO(_NAV)
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY_LHOME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_TAB, KC_LSFT, KC_LCTL, KC_LCMD, KC_LOPT,  KC_G,                           KC_H,     KC_J,       KC_K,       KC_L,        KC_SCLN,     KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      KC_X,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,     KC_COMM,  KC_DOT, KC_SLSH,  HYPR_T(KC_NO),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______,   KC_SPC,        KC_ENT, MO(_NUMS), MO(_NAV)
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY_RHOME] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_TAB,   KC_A,   KC_S,    KC_D,    KC_F,  KC_G,                           KC_H,     KC_ROPT,    KC_RCMD,    KC_RCTL,      KC_RSFT,     KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      KC_X,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M,     KC_COMM,  KC_DOT, KC_SLSH,  HYPR_T(KC_NO),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         _______, _______,   KC_SPC,        KC_ENT, MO(_NUMS), MO(_NAV)
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LSFT, KC_LCTL, KC_LCMD, KC_LOPT, KC_LCBR,                     KC_RCBR,  KC_ROPT, KC_RCMD, KC_RCTL, KC_RSFT, KC_NUHS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_GRV, KC_UNDS, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_PLUS, KC_MINS, KC_PEQL, KC_UNDS, KC_GRV, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_SPC,     KC_ENT, _______, MO(_NAV)
                                      //`--------------------------'  `--------------------------'
  ),

  // This is not working. The config.h change works, there's 6 layers, but this config isn't picked up, so the rest has to be set in VIA.
  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DT_PRNT,                      XXXXXXX, XXXXXXX, KC_UP,  XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, DT_UP,                        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DT_DOWN,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_SPC,     KC_ENT, MO(_MEDIA), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_MEDIA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SPI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_RMOD, RGB_HUD, RGB_SPD, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______,  KC_SPC,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};