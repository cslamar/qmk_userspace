/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
#    include "timer.h"
#endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

enum charybdis_keymap_layers {
    LAYER_BASE = 0,
    LAYER_LOWER,
    LAYER_RAISE,
    LAYER_POINTER,
};

enum custom_keycodes {
     HOLO_WINDOW = SAFE_RANGE,
     CHRIS_WINDOW,
     NEW_TERM,
     TOGGLE_FULL,
     SLACK_PIKA,
     SLACK_MEETING,
     NEW_INCOG,
     SIGNAL_TOGGLE,
     COPY_URL,
     NEW_DEV_WINDOW,
     NEW_CODE_WINDOW,
     RAYCAST,
     BACK_COMBO,
     FORWARD_COMBO,
     RAYCAST2,
     MOVE_WINDOW,
     RESIZE_WINDOW,
};

/** \brief Automatically enable sniping-mode on the pointer layer. */
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
static uint16_t auto_pointer_layer_timer = 0;

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 1000
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS

#    ifndef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#        define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 8
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD
#endif     // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#define LOWER MO(LAYER_LOWER)
#define RAISE MO(LAYER_RAISE)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮ ╭──────────────────────────────────────────────────────╮
        KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,       KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
        KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_MINS,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  // ├──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────┤
       KC_LCTL,    PT_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,    KC_M, KC_COMM,  KC_DOT, PT_SLSH, KC_LALT,
  // ╰──────────────────────────────────────────────────────┤ ├──────────────────────────────────────────────────────╯
                               KC_BSPC, KC_SPACE, KC_LGUI,        KC_LALT,  KC_ENT,
                                        KC_LCTL,  LOWER,          RAISE
  //                            ╰───────────────────────────╯ ╰──────────────────╯
  ),

  [LAYER_LOWER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮                           ╭──────────────────────────────────────────────────────╮
       KC_GRAVE,       KC_EXLM,   KC_AT,           KC_HASH,           KC_DLR,  KC_PERC,        KC_CIRC,      KC_AMPR, KC_ASTR, KC_LPRN, KC_F12, KC_UNDS,
  // ├──────────────────────────────────────────────────────┤                    
       RGB_MOD,       XXXXXXX,   KC_LEFT_BRACKET, KC_RIGHT_BRACKET,  XXXXXXX, NEW_TERM,       KC_LBRC,      BACK_COMBO,   KC_UP,   FORWARD_COMBO,   SLACK_PIKA, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤                           ├──────────────────────────────────────────────────────┤
       KC_LSFT, KC_LGUI,   SIGNAL_TOGGLE,    NEW_DEV_WINDOW, TOGGLE_FULL, XXXXXXX,             HOLO_WINDOW,  KC_LEFT, KC_DOWN, KC_RGHT, KC_EQUAL, KC_PGUP,
  // ├──────────────────────────────────────────────────────┤                           ├──────────────────────────────────────────────────────┤
      _______, XXXXXXX, COPY_URL, CHRIS_WINDOW, NEW_CODE_WINDOW, XXXXXXX,                     NEW_INCOG,    SLACK_MEETING,   KC_P2,   KC_P3, KC_PSLS, KC_PGDN,
  // ╰──────────────────────────────────────────────────────┤                           ├──────────────────────────────────────────────────────╯
                                KC_DELETE, KC_PAGE_UP, _______,                               XXXXXXX,   _______,
                                           _______, _______,                                  KC_P0
  //                            ╰───────────────────────────╯                           ╰──────────────────╯
  ),

  [LAYER_RAISE] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮                   ╭──────────────────────────────────────────────────────╮
        KC_GRAVE,   KC_F1,   KC_F2,   KC_MEDIA_PREV_TRACK,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK,                      KC_F6,       KC_F7,   KC_F8,   KC_F9,  KC_F12,   KC_F11,
  // ├──────────────────────────────────────────────────────┤                   ├──────────────────────────────────────────────────────┤
       _______, XXXXXXX, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, XXXXXXX, NEW_TERM,     XXXXXXX,   BACK_COMBO, XXXXXXX, FORWARD_COMBO, SLACK_PIKA, KC_VOLU,
  // ├──────────────────────────────────────────────────────┤                   ├──────────────────────────────────────────────────────┤
       _______, KC_LEFT,   SIGNAL_TOGGLE, NEW_DEV_WINDOW, TOGGLE_FULL,  KC_PGUP,                  HOLO_WINDOW, KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_MUTE,
  // ├──────────────────────────────────────────────────────┤                   ├──────────────────────────────────────────────────────┤
       _______, KC_HOME, COPY_URL, CHRIS_WINDOW,  NEW_CODE_WINDOW, KC_PGDN,                  NEW_INCOG,   SLACK_MEETING, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLD,
  // ╰──────────────────────────────────────────────────────┤                   ├──────────────────────────────────────────────────────╯
                                  KC_DELETE, RAYCAST2, _______,                        KC_PAGE_UP, _______,
                                           _______,  _______,                        _______
  //                            ╰───────────────────────────╯                   ╰──────────────────╯
  ),

  [LAYER_POINTER] = LAYOUT(
  // ╭──────────────────────────────────────────────────────╮           ╭──────────────────────────────────────────────────────╮
       QK_BOOT,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      EE_CLR,         EE_CLR,      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  QK_BOOT,
  // ├──────────────────────────────────────────────────────┤           ├──────────────────────────────────────────────────────┤
       XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, DPI_MOD,      S_D_MOD,        S_D_MOD,     DPI_MOD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤           ├──────────────────────────────────────────────────────┤
       XXXXXXX, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT,       XXXXXXX,        XXXXXXX,     KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, XXXXXXX,
  // ├──────────────────────────────────────────────────────┤           ├──────────────────────────────────────────────────────┤
       XXXXXXX, _______, DRGSCRL, SNIPING, RESIZE_WINDOW, MOVE_WINDOW,    MOVE_WINDOW, RESIZE_WINDOW, SNIPING, DRGSCRL, _______, XXXXXXX,   // May put MOVE_WINDOW and RESIZE_WINDOW on the first to cols of this row.
  // ╰──────────────────────────────────────────────────────┤           ├──────────────────────────────────────────────────────╯
                                  KC_BTN2, KC_BTN1, KC_BTN3,                KC_BTN2, KC_BTN1,
                                           _______, KC_BTN2,                KC_BTN3
  //                            ╰───────────────────────────╯           ╰──────────────────╯
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
            rgb_matrix_mode_noeeprom(RGB_MATRIX_NONE);
            rgb_matrix_sethsv_noeeprom(HSV_GREEN);
#        endif // RGB_MATRIX_ENABLE
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(LAYER_POINTER);
#        ifdef RGB_MATRIX_ENABLE
        rgb_matrix_mode_noeeprom(RGB_MATRIX_DEFAULT_MODE);
#        endif // RGB_MATRIX_ENABLE
    }
}
#    endif // CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_ENABLE

#    ifdef CHARYBDIS_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // CHARYBDIS_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t raycast_timer;

    switch (keycode) {
    case HOLO_WINDOW:
        if (record->event.pressed) {
            // when keycode HOLO_WINDOW is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_H);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode HOLO_WINDOW is released
        }
        break;

     case CHRIS_WINDOW:
        if (record->event.pressed) {
            // when keycode CHRIS_WINDOW is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_C);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode CHRIS_WINDOW is released
        }
        break;

     case NEW_TERM:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LGUI);
            tap_code(KC_T);
            unregister_code(KC_LGUI);
        } else {
            // when keycode is released
        }
        break;

     case TOGGLE_FULL:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LGUI);
            tap_code(KC_V);
            unregister_code(KC_LGUI);
        } else {
            // when keycode is released
        }
        break;

     case SLACK_PIKA:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_P);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;

     case SLACK_MEETING:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_M);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;

     case NEW_INCOG:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_I);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;


     case COPY_URL:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_X);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;

     case NEW_DEV_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            tap_code(KC_D);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;

     case BACK_COMBO:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LCTL);
            tap_code(KC_PGUP);
            unregister_code(KC_LCTL);
        } else {
            // when keycode is released
        }
        break;

     case FORWARD_COMBO:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LCTL);
            tap_code(KC_PGDN);
            unregister_code(KC_LCTL);
        } else {
            // when keycode is released
        }
        break;

     case RAYCAST2:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LGUI);
            tap_code(KC_SPC);
            unregister_code(KC_LGUI);

        } else {
            // when keycode is released
        }
        break;

     case NEW_CODE_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LALT);
            register_code(KC_LCTL);
            register_code(KC_LSFT);
            tap_code(KC_V);
            unregister_code(KC_LSFT);
            unregister_code(KC_LCTL);
            unregister_code(KC_LALT);
        } else {
            // when keycode is released
        }
        break;

     case MOVE_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LGUI);
            // register_mouse_button(KC_BTN1);
            // register_mouse_button(MOUSE_BTN1);
            register_code(KC_BTN1);
        } else {
            // when keycode is released
            // unregister_mouse_button(KC_BTN1);
            // unregister_mouse_button(MOUSE_BTN1);
            unregister_code(KC_BTN1);
            unregister_code(KC_LGUI);
        }
        break;

     case RESIZE_WINDOW:
        if (record->event.pressed) {
            // when keycode is pressed
            register_code(KC_LGUI);
            register_code(KC_BTN2);
            // register_mouse_button(MOUSE_BTN2);
            // register_mouse_button(c);
        } else {
            // when keycode is released
            unregister_code(KC_BTN2);
            unregister_code(KC_LGUI);
            // unregister_mouse_button(MOUSE_BTN2);
            
        }
        break;

     case RAYCAST:
        if (record->event.pressed) {
            // when keycode is pressed
            // start keypress timer
            raycast_timer = timer_read();
        } else {
            // when keycode is released
            // if keypress timer is shorter than predefined hold timer in ms, it's a tap
            if (timer_elapsed(raycast_timer) < 300) {
               // send the tap version of the key
               tap_code(KC_SPC);
            } else {
               // otherwise preform the macro combo once the held timer has passed the predefined value.
               // Cmd - Space
               register_code(KC_LGUI);
               tap_code(KC_SPC);
               unregister_code(KC_LGUI);
            }
        }
        break;
    }
    return true;
};
