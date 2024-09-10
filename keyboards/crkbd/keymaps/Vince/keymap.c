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
  _QWERTY,
  _GAMINGALPHA,
  _GAMING,
  _NUMS,
  _NAV,
  _LIGHTS,
  _FUN
};

// enum planck_keycodes {
//   QWERTY = SAFE_RANGE,
//   GAMING_ALPHA,
//   GAMING
// };

#define RBG_VAL 120
layer_state_t layer_state_set_user(layer_state_t state) {
  rgblight_config_t rgblight_config;
  switch(biton32(state)) {
  case _QWERTY:
    // Green
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_GREEN);
    break;
  case _NUMS:
    // Red
    rgblight_enable_noeeprom();	
    rgblight_sethsv_noeeprom(HSV_RED);
    break;
  case _NAV:
    // Blue
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_BLUE);
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

// layer_state_t layer_state_set_user(layer_state_t state) {
//   return update_tri_layer_state(state, _NUMS, _NAV, _LIGHTS);
// }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//     case QWERTY:
//       if (record->event.pressed) {
//         print("mode just switched to qwerty and this is a huge string\n");
//         set_single_persistent_default_layer(_QWERTY);
//       }
//       return false;
//       break;

//     case GAMING_ALPHA:
//       if (record->event.pressed) {
//         // set_single_persistent_default_layer(_GAMINGALPHA);
//         layer_off(_QWERTY);
//         // layer_off(_LOWER);
//         // layer_off(_ADJUST);
//         // layer_on(_PLOVER);
//       }
//       return false;
//       break;

//     case GAMING:
//       if (record->event.pressed) {
//         set_single_persistent_default_layer(_GAMING);
//       }
//       return false;
//       break;
//     }

//     return true;
// }

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
// 	switch (keycode) {
// 		case GAMING_ON:
//             if (record->event.pressed) { 
//                 layer_off(0);
//                 layer_off(1);
//                 layer_off(3);
//                 layer_off(4);
//                 layer_off(5);
//                 layer_off(6);

//                 layer_on(2);
//              }
//             return false;

//         case GAMING_OFF:
//             if (record->event.pressed) { 
//                 layer_on(0);
//                 layer_on(1);
//                 layer_on(3);
//                 layer_on(4);
//                 layer_on(5);
//                 layer_on(6);

//                 layer_off(2);
//              }
//             return false;

//         default:
//             return true;
// 	}
// }

// Place `KC_CYCLE_LAYERS` as a keycode in your keymap

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_TAB, SFT_T(KC_A), CTL_T(KC_S), CMD_T(KC_D), OPT_T(KC_F), KC_G,       KC_H,   OPT_T(KC_J), CMD_T(KC_K), CTL_T(KC_L), SFT_T(KC_SCLN), KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      XXXXXXX,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  DF(_GAMINGALPHA),
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         MO(5), HYPR_T(KC_NO), KC_SPC,        KC_ENT, MO(3), MO(4)
                                      //`--------------------------'  `--------------------------'

  ),

  [_GAMINGALPHA] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_TAB,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,                          KC_H,       KC_J,        KC_K,      KC_L,       KC_SCLN,      KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      KC_LCTL,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LALT, KC_LGUI, KC_SPC,     KC_ENT,  MO(3),   MO(4)
                                      //`--------------------------'  `--------------------------'

  ),

  [_GAMING] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |-----------+-----------+-----------+------------+-------------+----------|
      KC_LSFT,   KC_A,    KC_S,    KC_D,   KC_F,    KC_G,                          KC_H,       KC_J,        KC_K,      KC_L,       KC_SCLN,      KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |----------+----------+-----------+-------------+-------------+-----------|
      KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_V,   KC_LCTL,   KC_SPC,    KC_ENT,  MO(6),  KC_RGUI
                                      //`--------------------------'  `--------------------------'

  ),

  [_NUMS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, SFT_T(KC_A), CTL_T(KC_S), CMD_T(KC_D), OPT_T(KC_F), KC_LCBR,     KC_RCBR,  OPT_T(KC_J), CMD_T(KC_K), CTL_T(KC_L), SFT_T(KC_SCLN), KC_NUHS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, KC_GRV, KC_UNDS, XXXXXXX, KC_LBRC, KC_RBRC,                      KC_PLUS, KC_MINS, KC_PEQL, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,  KC_SPC,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DT_PRNT,                      XXXXXXX, XXXXXXX, KC_UP,  XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, DT_UP,                        XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DT_DOWN,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,  KC_SPC,     KC_ENT, MO(5),  _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LIGHTS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      RGB_TOG, RGB_MOD, RGB_HUI, RGB_SPI, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_VOLD, KC_MUTE, KC_VOLU, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, RGB_RMOD, RGB_HUD, RGB_SPD, XXXXXXX, XXXXXXX,                     XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, XXXXXXX,  KC_SPC,     KC_ENT, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, KC_F1,   KC_F2,    KC_F3,   KC_F4,  KC_F5,                        KC_F6,   KC_F7,   KC_F8,    KC_F9,  KC_F10, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, KC_PSCR, XXXXXXX, KC_F11, KC_F12,   XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, _______, XXXXXXX
                                      //`--------------------------'  `--------------------------'
  )
};