/* Copyright 2020 tominabox1, 2025 mkalinski
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
    MYLY_BASE,
    // Layer for games that work on WSAD controls.
    // It shifts the whole left side one letter right,
    // and adds some usual functional keys to the leftmost column.
    // It's meant to be toggled.
    MYLY_GAMER,
    // Layer for numeric and symbolic keys, expected to be triggered by left hand.
    MYLY_LEFT_NUMSYM,
    // Layer for F-keys and other special keys, expected to be triggered by right hand.
    // This keyboard also has some very active RGB underglow, as it turns out,
    // so controlling them is not optional.
    MYLY_RIGHT_FUNCSPEC
};

enum my_keycodes {
    // Fake diabling of underight,
    // so that indicators can still work.
    MY_RGBT = SAFE_RANGE
};

//
// Space Row
//
// Spaces will act as "major" keys and alts (for symmetry, as AltGr outside alphas is mandatory).
// mod switches will double as "missing" keys.
#define MY_LMOD LT(MYLY_LEFT_NUMSYM, KC_TAB)
#define MY_LSPC MT(MOD_LALT, KC_SPACE)

#define MY_RSPC MT(MOD_RALT, KC_ENTER)
#define MY_RMOD LT(MYLY_RIGHT_FUNCSPEC, KC_QUOTE)

//
// Home Row Mods
//
// Shift is on the raised column in this keyboard, as mnemonic.
#define MY_CS MT(MOD_LCTL, KC_S)
#define MY_SD MT(MOD_LSFT, KC_D)
#define MY_GF MT(MOD_LGUI, KC_F)

#define MY_GJ MT(MOD_RGUI, KC_J)
#define MY_SK MT(MOD_RSFT, KC_K)
#define MY_CL MT(MOD_RCTL, KC_L)

// On the second layer, the mods are mostly transparent,
// but this one needs to be explicitly stated.
#define MY_CMI MT(MOD_RCTL, KC_MINUS)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [MYLY_BASE] = LAYOUT(
    KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,  KC_MPLY,     KC_Y,   KC_U,    KC_I,   KC_O,     KC_P,
    KC_A,  MY_CS,  MY_SD,  MY_GF,   KC_G,               KC_H,  MY_GJ,   MY_SK,  MY_CL,  KC_SCLN,
    KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,               KC_N,   KC_M, KC_COMM, KC_DOT,  KC_SLSH,
                         MY_LMOD,MY_LSPC,            MY_RSPC,MY_RMOD
  ),

  [MYLY_GAMER] = LAYOUT(
     KC_ESC,  KC_Q,  KC_W,  KC_E,  KC_R,  TG(MYLY_GAMER),  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_LSFT,  KC_A,  KC_S,  KC_D,  KC_F,                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_LCTL,  KC_Z,  KC_X,  KC_C,  KC_V,                   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
                         KC_TRNS,KC_SPC,                   KC_TRNS,KC_TRNS
  ),

  [MYLY_LEFT_NUMSYM] = LAYOUT(
       KC_1,   KC_2,     KC_3,     KC_4,      KC_5,  KC_MUTE,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,   MY_CMI, KC_EQUAL,
    KC_DEL , KC_INS,  KC_LCBR,  KC_LBRC,   KC_LPRN,            KC_RPRN,  KC_RBRC,  KC_RCBR,  KC_BSLS,   KC_GRV,
                                KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_TRNS
  ),

  [MYLY_RIGHT_FUNCSPEC] = LAYOUT(
      KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  TG(MYLY_GAMER),    KC_F6,    KC_F7,    KC_UP,    KC_F8,    KC_F9,
    MY_RGBT,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_PSCR,                   KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    UG_NEXT,  UG_HUEU,  UG_SATU,  UG_VALU, UG_SPDU,                   KC_PGUP,   KC_F10,   KC_F11,   KC_F12,  KC_PGDN,
                                  KC_TRNS, KC_TRNS,                    KC_SPC,  KC_TRNS
  )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MYLY_BASE] = {ENCODER_CCW_CW(KC_MRWD, KC_MFFD)},
    [MYLY_GAMER] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [MYLY_LEFT_NUMSYM] = {ENCODER_CCW_CW(KC_MPRV, KC_MNXT)},
    [MYLY_RIGHT_FUNCSPEC] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)}
};
#endif

#ifdef COMBO_ENABLE
enum combo_events {
    COMBO_ESC,
    COMBO_BSPC
};

// These combos are on the fist layer, pressed with middle two fingers.
// Because it's more convenient for me to use these fingers, rather than outermost ones.
const uint16_t PROGMEM combo_esc[] = {KC_W, KC_E, COMBO_END};
const uint16_t PROGMEM combo_bspc[] = {KC_I, KC_O, COMBO_END};

combo_t key_combos[] = {
    [COMBO_ESC] = COMBO(combo_esc, KC_ESC),
    [COMBO_BSPC] = COMBO(combo_bspc, KC_BSPC)
};
#endif

//
// RGB matrix helpers and indicators.
//
static void my_pseudo_toggle_rgb(void) {
    static uint8_t saved_mode = RGB_MATRIX_SOLID_COLOR;
    static hsv_t saved_hsv = {HSV_OFF};

    uint8_t current_mode = rgb_matrix_get_mode();
    hsv_t current_hsv = rgb_matrix_get_hsv();

    // Only value really matters for lighting to be OFF.
    if (current_hsv.v == 0) {
        // I'm not sure how saving the current effect works on poweroff.
        // If the current and saved settings somehow both get zeroed,
        // try to restore defaults.
        if (saved_hsv.v == 0) {
            rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
            rgb_matrix_sethsv_noeeprom(
                RGB_MATRIX_DEFAULT_HUE,
                RGB_MATRIX_DEFAULT_SAT,
                RGB_MATRIX_DEFAULT_VAL
            );
        } else {
            rgb_matrix_mode_noeeprom(saved_mode);
            rgb_matrix_sethsv_noeeprom(saved_hsv.h, saved_hsv.s, saved_hsv.v);
        }
    } else {
        saved_mode = current_mode;
        saved_hsv = current_hsv;
        rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
        rgb_matrix_sethsv_noeeprom(HSV_OFF);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_RGBT:
            if (record->event.pressed) {
                my_pseudo_toggle_rgb();
            }
            return false;

        default:
            return true;
    }
}

// The two leds on the keyboard's face are, from top:
// RGB_MATRIX_LED_COUNT - 2 and RGB_MATRIX_LED_COUNT - 1.
#define MY_LED_TOP (RGB_MATRIX_LED_COUNT - 2)

// For indicators, I want to match the brightness of effects,
// but not let them to be completely turned off
#define MY_INDICATOR_MINIMUM_BRIGHTNESS 10

static uint8_t my_scale_color_by_val(uint8_t color, uint8_t val) {
    // Don't let the indicator be completely turned off.
    if (val < MY_INDICATOR_MINIMUM_BRIGHTNESS) {
        val = MY_INDICATOR_MINIMUM_BRIGHTNESS;
    }

    // Value is between 0 and 255 instead of 0 and 100%.
    // This scales color magnitude by value,
    // while avoiding introducing floating point maths.
    // This sets the color's brightness in practice.
    return color * val / 255;
}

#define MY_SCALED_RED my_scale_color_by_val(0xFF, rgb_matrix_get_val()), 0, 0
#define MY_SCALED_GREEN 0, my_scale_color_by_val(0xFF, rgb_matrix_get_val()), 0
#define MY_SCALED_BLUE 0, 0, my_scale_color_by_val(0xFF, rgb_matrix_get_val())

// This callback is called on every matrix update,
// and sets the state of each LED.
bool rgb_matrix_indicators_user(void) {
    // Use the top front LED for indicator of the active layer,
    // otherwise keep it off no matter the active effect.
    if (IS_LAYER_ON(MYLY_RIGHT_FUNCSPEC)) {
        rgb_matrix_set_color(MY_LED_TOP, MY_SCALED_BLUE);
    } else if (IS_LAYER_ON(MYLY_LEFT_NUMSYM)) {
        rgb_matrix_set_color(MY_LED_TOP, MY_SCALED_GREEN);
    } else if (IS_LAYER_ON(MYLY_GAMER)) {
        rgb_matrix_set_color(MY_LED_TOP, MY_SCALED_RED);
    } else {
        rgb_matrix_set_color(MY_LED_TOP, RGB_OFF);
    }

    return true;
}
