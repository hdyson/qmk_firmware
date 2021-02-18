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

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _NUMBERS 1
#define _SYMBOLS 2
// Two identical movement layers, to work around issue with thumb toggles for
// layers.  If both number and symbol layers are toggled, this turns on the
// movement layer via layer_state_set_user.  But this disables the LT options
// on the T and Y keys.  So duplicate movement layer means one layer is for
// thumb toggles and one layer for hold to activate.
#define _MOVEMENT 3
#define _MOVEMENT2 4

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  MOVEMENT,
  NUMBERS,
  SYMBOLS,
  BACKLIT,
  RGBRST
};

// Tap Dance declarations
enum {
    TD_U_COMPILE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for u, twice for f12 (recompile in my emacs config).
    [TD_U_COMPILE] = ACTION_TAP_DANCE_DOUBLE(KC_U, KC_F12),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------------------------------------------.                   ,-----------------------------------------------------------------------------------------------.
         KC_GESC,         KC_Q,         KC_W,         KC_E,         KC_R,  LT(_MOVEMENT2, KC_T),                    LT(_MOVEMENT2, KC_Y), TD(TD_U_COMPILE),         KC_I,         KC_O,            KC_P,     KC_BSPC,\
  //|-----------+-------------+-------------+-------------+-------------+---------------------|                   |-------------------+-----------------+-------------+-------------+----------------+------------|
          KC_TAB, LGUI_T(KC_A), LALT_T(KC_S), LCTL_T(KC_D), LSFT_T(KC_F),   LT(_NUMBERS, KC_G),                     LT(_NUMBERS, KC_H),     LSFT_T(KC_J), LCTL_T(KC_K), LALT_T(KC_L), LGUI_T(KC_SCLN),     KC_QUOT,\
  //|-----------+-------------+-------------+-------------+-------------+---------------------|                   |-------------------+-----------------+-------------+-------------+----------------+------------|
     KC_LBRACKET,         KC_Z,         KC_X,         KC_C,         KC_V,   LT(_SYMBOLS, KC_B),                     LT(_SYMBOLS, KC_N),             KC_M,      KC_COMM,       KC_DOT,         KC_SLSH, KC_RBRACKET,\
  //|-----------+-------------+-------------+-------------+-------------+---------------------+-------|  |--------+-------------------+-----------------+-------------+-------------+----------------+------------|
                                                                 KC_LPRN,         TG(_NUMBERS), KC_SPC,     KC_ENT,      TG(_SYMBOLS),          KC_RPRN\
                                                          //`-----------------------------------------'  `----------------------------------------------'
  ),

  // Numbers and RGB controls
  // Relies on shift to decrease behaviour for hue, saturation and value controls
  [_NUMBERS] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        RESET,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGBRST,  KC_TRNS,                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),

  // Symbols and media controls
  [_SYMBOLS] = LAYOUT_split_3x6_3( \
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_TILD, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BRMU, VLK_TOG, KC_MFFD, KC_MUTE, KC_VOLU, KC_TRNS,                      KC_MINS,  KC_EQL, KC_TRNS, KC_TRNS, KC_PIPE, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BRMD, RGB_M_SW, KC_MPRV, KC_MPLY, KC_VOLD, KC_TRNS,                      KC_TRNS, KC_PLUS, KC_TRNS, KC_TRNS, KC_BSLS, KC_TRNS,\
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_TRNS, KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                      //`--------------------------'  `--------------------------'
  ),

  [_MOVEMENT2] = LAYOUT_split_3x6_3( \
  //,--------------------------------------------------------.                    ,--------------------------------------------------------.
      KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                      KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------|                    |--------+--------+---------+----------+--------+--------|
      KC_TRNS, KC_HOME,   KC_PGUP, KC_LEFT,   KC_UP, KC_RIGHT,                      KC_LEFT,   KC_UP, KC_RIGHT,   KC_PGUP, KC_HOME, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------|                    |--------+--------+---------+----------+--------+--------|
      KC_TRNS,  KC_END, KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT,                      KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN,  KC_END, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------+--------|  |--------+--------+--------+---------+----------+--------+--------|
                                            KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                        //`---------------------------'  `--------------------------'
    ),
  [_MOVEMENT] = LAYOUT_split_3x6_3( \
  //,--------------------------------------------------------.                    ,--------------------------------------------------------.
      KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,                      KC_TRNS, KC_TRNS,  KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------|                    |--------+--------+---------+----------+--------+--------|
      KC_TRNS, KC_HOME,   KC_PGUP, KC_LEFT,   KC_UP, KC_RIGHT,                      KC_LEFT,   KC_UP, KC_RIGHT,   KC_PGUP, KC_HOME, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------|                    |--------+--------+---------+----------+--------+--------|
      KC_TRNS,  KC_END, KC_PGDOWN, KC_LEFT, KC_DOWN, KC_RIGHT,                      KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN,  KC_END, KC_TRNS,\
  //|--------+--------+----------+--------+--------+---------+--------|  |--------+--------+--------+---------+----------+--------+--------|
                                            KC_TRNS,  KC_TRNS, KC_TRNS,    KC_TRNS, KC_TRNS, KC_TRNS\
                                        //`---------------------------'  `--------------------------'
    ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_master) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NUMBERS 2
#define L_SYMBOLS 4
#define L_MOVEMENT 8

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln_P(PSTR("Default"), false);
            break;
        case L_NUMBERS:
	  oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case L_SYMBOLS:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case L_MOVEMENT:
        case L_MOVEMENT|L_NUMBERS:
        case L_MOVEMENT|L_SYMBOLS:
        case L_MOVEMENT|L_SYMBOLS|L_NUMBERS:
            oled_write_ln_P(PSTR("Movement"), false);
            break;
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    state = update_tri_layer_state(state, _SYMBOLS, _NUMBERS, _MOVEMENT);
    return state;
}

char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  char name = ' ';
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
  if (keycode < 60) {
    name = code_to_name[keycode];
  }

  // update keylog
  snprintf(keylog_str, sizeof(keylog_str), "%dx%d, k%2d : %c",
           record->event.key.row, record->event.key.col,
           keycode, name);
}

void oled_render_keylog(void) {
    oled_write(keylog_str, false);
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_corne_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

void oled_render_ono_sendai_logo(void) {
  // Conversion from image to bytes as described here:
  // https://docs.splitkb.com/hc/en-us/articles/360013811280-How-do-I-convert-an-image-for-use-on-an-OLED-display-
    static const char PROGMEM ono_sendai_logo[] = {
      // 'Logo', 128x32px
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xf0, 0x18, 0x08, 0x08, 0x18, 0xf0, 0x00, 
0x00, 0xe0, 0xc0, 0x60, 0x20, 0x60, 0xc0, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x20, 0x20, 0xe0, 0xc0, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0xf8, 0x88, 0x88, 0x88, 0x08, 
0x00, 0x00, 0x00, 0x80, 0xc0, 0x20, 0x20, 0x60, 0xc0, 0x00, 0x00, 0x00, 0xe0, 0x40, 0x20, 0x20, 
0xc0, 0x00, 0x00, 0x00, 0xc0, 0x60, 0x20, 0x60, 0xe0, 0xfc, 0x00, 0x00, 0x00, 0x20, 0x20, 0x20, 
0x60, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0xec, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x0f, 0x18, 0x10, 0x10, 0x18, 0x0f, 0x00, 
0x00, 0x1f, 0x1f, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x0f, 0x18, 0x10, 0x10, 0x18, 0x0f, 
0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x10, 0x10, 0x10, 0x11, 0x1f, 
0x0e, 0x00, 0x00, 0x0f, 0x19, 0x11, 0x11, 0x11, 0x11, 0x01, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 
0x1f, 0x1f, 0x00, 0x00, 0x0f, 0x18, 0x10, 0x10, 0x1f, 0x1f, 0x00, 0x00, 0x0e, 0x1b, 0x11, 0x11, 
0x09, 0x1f, 0x00, 0x00, 0x00, 0x10, 0x10, 0x10, 0x1f, 0x10, 0x10, 0x10, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xce, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x04, 0x38, 
0xe0, 0x00, 0xc0, 0x78, 0x0c, 0x00, 0x00, 0xff, 0x98, 0x04, 0x04, 0x0c, 0xf8, 0x00, 0x00, 0xf0, 
0x38, 0x24, 0x24, 0x2c, 0x38, 0x20, 0x00, 0x00, 0x00, 0xfc, 0x38, 0x0c, 0x04, 0x04, 0x00, 0x00, 
0x00, 0x38, 0x24, 0x64, 0x44, 0xc0, 0x00, 0x00, 0x00, 0xfc, 0x08, 0x04, 0x0c, 0xb8, 0xf0, 0x00, 
0x00, 0xc0, 0x64, 0x24, 0x24, 0x2c, 0xf8, 0x00, 0x00, 0x00, 0xf8, 0x08, 0x0c, 0x04, 0x04, 0x00, 
0x00, 0x00, 0xf8, 0x2c, 0x24, 0x24, 0x2c, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x01, 0x1f, 0xf0, 0x80, 0xc0, 0x78, 0x0f, 0x01, 0x00, 0x01, 0x01, 0x01, 0xff, 0x01, 
0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0xff, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x10, 
0x19, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x01, 
0x03, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x02, 0x02, 0x02, 0x03, 0x01, 0x00, 0x00, 0x00, 0x1f, 0x03, 0x02, 0x02, 0x03, 0x00, 0x00, 
0x00, 0x01, 0x03, 0x02, 0x02, 0x01, 0x03, 0x00, 0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x02, 0x00, 
0x00, 0x00, 0x01, 0x03, 0x02, 0x02, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x03, 0x02, 
0x02, 0x00, 0x00, 0x00, 0x02, 0x02, 0x03, 0x02, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(ono_sendai_logo, sizeof(ono_sendai_logo));
}

void oled_task_user(void) {
    if (is_master) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        oled_render_ono_sendai_logo();
	//        oled_render_corne_logo();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    set_keylog(keycode, record);
  }
  return true;
}
#endif // OLED_DRIVER_ENABLE
