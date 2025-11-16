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
    // Layer for numeric and symbolic keys, expected to be triggered by left hand.
    MYLY_LEFT_NUMSYM,
    // Layer for F-keys and other special keys, expected to be triggered by right hand.
    // This keyboard also has some very active RGB underglow, as it turns out,
    // so controlling them is not optional.
    MYLY_RIGHT_FUNCSPEC
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

  [MYLY_LEFT_NUMSYM] = LAYOUT(
       KC_1,   KC_2,     KC_3,     KC_4,      KC_5,  KC_TRNS,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
    KC_TRNS,KC_TRNS,  KC_TRNS,  KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_TRNS,  KC_TRNS,   MY_CMI, KC_EQUAL,
    KC_DEL , KC_INS,  KC_LCBR,  KC_LBRC,   KC_LPRN,            KC_RPRN,  KC_RBRC,  KC_RCBR,   KC_GRV,  KC_BSLS,
                                KC_TRNS,   KC_TRNS,            KC_TRNS,  KC_TRNS
  ),

  [MYLY_RIGHT_FUNCSPEC] = LAYOUT(
      KC_F1,    KC_F2,    KC_F3,    KC_F4,   KC_F5,  KC_MUTE,    KC_F6,    KC_F7,    KC_UP,    KC_F8,    KC_F9,
    UG_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_PSCR,            KC_HOME,  KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_END,
    UG_NEXT,  UG_HUEU,  UG_SATU,  UG_VALU, UG_SPDU,            KC_PGUP,   KC_F10,   KC_F11,   KC_F12,  KC_PGDN,
                                  KC_TRNS, KC_TRNS,             KC_SPC,  KC_TRNS
  )
};
// clang-format on

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [MYLY_BASE] =  {ENCODER_CCW_CW(KC_MRWD, KC_MFFD)},
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

#ifdef OLED_ENABLE

// Add additional layer names here if desired. Only first 5 characters will be copied to display.
const char PROGMEM layer_base[]    = "BASE";
const char PROGMEM layer_num_sym[] = " SYM";
const char PROGMEM layer_nav[]     = " NAV";
// Add layer name variables to array here. Make sure these are in order.
const char* const PROGMEM layer_names[] = {
    layer_base,
    layer_num_sym,
    layer_nav
};

static char oled_layer_buf[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
static layer_state_t top_layer_cache;

/* BEGIN STANDARD QMK FUNCTIONS */
bool oled_task_user(void) {
    oled_write_raw_P(lechiffre_logo, sizeof(lechiffre_logo));
    // Renders the current keyboard state (layer, lock, caps, scroll, etc);
    oled_set_cursor(0, 3);
    oled_write_P(oled_section_break, false);
    render_layer_status(oled_layer_buf);
    oled_write_P(oled_section_break, false);
    render_mod_status(get_mods() | get_oneshot_mods());
    oled_write_P(oled_section_break, false);
    render_keylock_status(host_keyboard_led_state());
    oled_write_P(oled_section_break, false);
    render_keylogger_status();

    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    if (record->event.pressed) {
        add_keylog(keycode, record);
    }

    return true;
}

// If we don't force an update during initialization, the layer name buffer will start out blank.
layer_state_t default_layer_state_set_user(layer_state_t state) {
    update_layer_namebuf(get_highest_layer(state), true);
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    update_layer_namebuf(get_highest_layer(state | default_layer_state), false);
    return state;
}

/* END STANDARD QMK FUNCTIONS */
/* BEGIN CUSTOM HELPER FUNCTION FOR OLED */
// Avoid excessive copying by only updating the layer name buffer when the layer changes
void update_layer_namebuf(layer_state_t layer, bool force_update) {
    if (force_update || layer != top_layer_cache) {
        top_layer_cache = layer;
        if (layer < ARRAY_SIZE(layer_names)) {
            memcpy_P(oled_layer_buf, pgm_read_ptr(&layer_names[layer]), ARRAY_SIZE(oled_layer_buf) - 1);
        } else {
            memcpy(oled_layer_buf, get_u8_str(layer, ' '), ARRAY_SIZE(oled_layer_buf) - 1);
        }
    }
}
#endif
