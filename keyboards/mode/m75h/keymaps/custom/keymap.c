/*
Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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


enum custom_keycodes {
    MAC_VOICE = QK_KB_0,
    MAC_MCTL,
    MAC_LPAD,
    MAC_DND,
    MAC_SEARCH,
    WIN_TASK,
    WIN_VOICE,
//    CK_RBT
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MAC_VOICE:
            if (record->event.pressed) {
                host_consumer_send(0xCF);  // Send Mac voice command
            } else {
                host_consumer_send(0);     // Release Mac voice command
            }
            return false;
        case MAC_MCTL:
            if (record->event.pressed) {
                tap_code16(KC_MCTL);
            } else {
                host_system_send(0);       // Release Mac media control command
            }
            return false;
        case MAC_LPAD:
            if (record->event.pressed) {
                tap_code16(KC_LPAD);
            } else {
                host_system_send(0);       // Release Mac Launchpad command
            }
            return false;
        case MAC_DND:
            if (record->event.pressed) {
                host_system_send(0x9B);
            } else {
                host_system_send(0);       // Release Mac DND command
            }
            return false;
        case MAC_SEARCH:
            if (record->event.pressed) {
                tap_code16(G(KC_SPC));     // Send Cmd + Space (Spotlight)
            }
            return false;
        case WIN_TASK:
            if (record->event.pressed) {
                tap_code16(G(KC_TAB));     // Send Win + Tab (Task View)
            }
            return false;
        case WIN_VOICE:
            if (record->event.pressed) {
                tap_code16(KC_ASST);     // Send Keycode for Windows Voice
            }
            return false;
//        case CK_RBT: Neither of the following methods actually work. Only if they're in the keymap directly
//            if (record->event.pressed) {
//                tap_code16(QK_RBT);    // Reboot the keyboard
//                host_system_send(0x7C01);
//            }
//            return false;
    }
    return true;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [0] = LAYOUT_ansi_blocker(
        KC_ESC  , KC_BRID, KC_BRIU, MAC_MCTL, MAC_SEARCH,          MAC_VOICE,  MAC_DND, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,          KC_DEL,
        KC_GRV  , KC_1   , KC_2   , KC_3    , KC_4      , KC_5   , KC_6     ,  KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,          KC_PGUP,
        KC_TAB  , KC_Q   , KC_W   , KC_E    , KC_R      , KC_T   , KC_Y     ,  KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS , KC_A   , KC_S   , KC_D    , KC_F      , KC_G   , KC_H     ,  KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,                   KC_HOME,
        KC_LSFT ,          KC_Z   , KC_X    , KC_C      , KC_V   , KC_B     ,  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , KC_END ,
        KC_LCTL , KC_LALT, KC_LCMD,                                    KC_SPC,                           KC_RCMD, MO(1)  ,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT_ansi_blocker(
        KC_TRNS, KC_F1  , KC_F2  , KC_F3   , KC_F4      ,          KC_F5    ,  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS    , KC_TRNS, KC_TRNS  ,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, TO(2),   KC_TRNS , QK_RBT     , KC_TRNS, KC_TRNS  ,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS    , KC_TRNS, KC_TRNS  ,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS , EE_CLR     , KC_TRNS, QK_BOOT  ,  KC_TRNS, TO(0)  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS,                          KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [2] = LAYOUT_ansi_blocker(
        KC_ESC  , KC_BRID, KC_BRIU, WIN_TASK, KC_WSCH   ,          WIN_VOICE,  KC_F6  , KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE, KC_VOLD, KC_VOLU,           KC_DEL ,
        KC_GRV  , KC_1   , KC_2   , KC_3    , KC_4      , KC_5   , KC_6     ,  KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL , KC_BSPC,          KC_PGUP,
        KC_TAB  , KC_Q   , KC_W   , KC_E    , KC_R      , KC_T   , KC_Y     ,  KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS , KC_A   , KC_S   , KC_D    , KC_F      , KC_G   , KC_H     ,  KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT ,                   KC_HOME,
        KC_LSFT ,          KC_Z   , KC_X    , KC_C      , KC_V   , KC_B     ,  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,          KC_UP  , KC_END ,
        KC_LCTL , KC_LGUI, KC_LALT,                                    KC_SPC,                           KC_RALT, MO(3)  ,          KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [3] = LAYOUT_ansi_blocker(
        KC_TRNS, KC_F1  , KC_F2  , KC_F3   , KC_F4      ,          KC_F5    , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12,           KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS    , KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, TO(2),   KC_TRNS , QK_RBT     , KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS , KC_TRNS    , KC_TRNS, KC_TRNS  , KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS,
        KC_TRNS,          KC_TRNS, KC_TRNS , EE_CLR     , KC_TRNS, QK_BOOT  , KC_TRNS, TO(0),   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,                                     KC_TRNS,                         KC_TRNS, KC_TRNS,          KC_TRNS, KC_TRNS, KC_TRNS
    )
};
