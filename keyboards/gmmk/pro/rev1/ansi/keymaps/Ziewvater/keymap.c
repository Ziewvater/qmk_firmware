/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>

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

#include "rgb_matrix_map.h"

// DEFINE MACROS
#ifndef ARRAYSIZE
#define ARRAYSIZE(arr)  sizeof(arr)/sizeof(arr[0])
#endif // !ARRAYSIZE

enum layer_names {
    _MAC,
    _MFN,
    _MF2,
    _WIN,
    _WFN,
};

enum custom_keycodes {
    Z_NEXT = SAFE_RANGE,
    Z_PREV,
    ALT_BK,
};

// Inline custom keycode definitions
#define ESC_FN LT(_MFN, KC_CAPS)

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case Z_NEXT:
        if (record->event.pressed) {
            // Ctrl + Alt + Cmd + Right
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_DOWN(X_LCMD));
            SEND_STRING(SS_TAP(X_RIGHT));
            SEND_STRING(SS_UP(X_LCTL) SS_UP(X_LALT) SS_UP(X_LCMD));
        }
        break;

    case Z_PREV:
        if (record->event.pressed) {
            // Ctrl + Alt + Cmd + Left
            SEND_STRING(SS_DOWN(X_LCTL) SS_DOWN(X_LALT) SS_DOWN(X_LCMD));
            SEND_STRING(SS_TAP(X_LEFT));
            SEND_STRING(SS_UP(X_LCTL) SS_UP(X_LALT) SS_UP(X_LCMD));
        }
        break;
    case ALT_BK:
        if (record->event.pressed) {
            // Alt + Backspace
            SEND_STRING(SS_DOWN(X_RALT) SS_TAP(X_BACKSPACE) SS_UP(X_RALT));
        }
        break;
    }
    return true;
};

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case Z_NEXT:
        break;

    case Z_PREV:
        break;
    }
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the QK_BOOT key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+backslash. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [_MAC] = LAYOUT(
        KC_ESC,  KC_BRID, KC_BRIU, KC_MCTL, KC_LPAD, KC_F5,   KC_F6,   KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU, TG(_WIN),         KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_HOME,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_MCTL,
        ESC_FN,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_DEL,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LALT, KC_LGUI,                            KC_SPC,                             KC_RGUI, MO(_MFN),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_MFN] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TG(_MF2),         _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, ALT_BK,           _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, Z_PREV,  Z_NEXT,  QK_BOOT,          _______,
        _______, _______, RGB_VAD, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_MCTL,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            KC_BTN1,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    [_MF2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, TG(_MF2),         _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PMNS, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_WIN] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  TG(_WIN),         KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGUP,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_PGDN,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_WFN),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_WFN] = LAYOUT(
        _______, KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, KC_SLEP,          _______,
        _______, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          _______,
        _______, _______, RGB_VAD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, RGB_HUI, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

};
// clang-format on

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_MAC] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_MFN] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_MF2] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [_WIN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_WFN] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS) }
};
#endif

void keyboard_post_init_user(void) {
    // Start board off with matrix lights turned off
    rgb_matrix_mode(RGB_MATRIX_NONE);
}

#ifdef RGB_MATRIX_ENABLE

// keyboard state coloring

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // Change all lights to off to build state back up
    rgb_matrix_set_color_all(RGB_OFF);

    switch (get_highest_layer(layer_state)) {
    case _MAC:
        rgb_matrix_set_color(LED_INS, RGB_OFF);
        break;
    case _MFN:
        rgb_matrix_set_color(LED_INS, RGB_RED);

        // Highlight mouse keys
        rgb_matrix_set_color(LED_H, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_J, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_K, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_L, RGB_CHARTREUSE);
        break;
    case _MF2:
        rgb_matrix_set_color(LED_INS, RGB_GOLDENROD);

        // Highlight numpad
        for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_NUMPAD); i++) {
            rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_PURPLE);
        }
        break;
    case _WIN:
        rgb_matrix_set_color(LED_INS, RGB_PINK);
        break;
    case _WFN:
        rgb_matrix_set_color(LED_INS, RGB_TEAL);
        break;
    }
    return false;
}

#endif // RGB_MATRIX_ENABLE