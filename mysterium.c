/* Copyright 2019 coseyfannitutti
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
#include "mysterium.h"
#include "oled.h"

bool win_key = false;
bool ctrl_key = false;

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    oled_request_wakeup();

    //fn + encoder is windows desktop change
    if (win_key) {
        if (clockwise) {
            tap_code16(G(C(KC_RIGHT)));
        } else {
            tap_code16(G(C(KC_LEFT)));
        }
        return false;
    }

    //ctrl + encoder is ctrl + z/y
    if (ctrl_key) {
        if (clockwise) {
            tap_code(KC_Z);
        } else {
            tap_code(KC_Y);
        }
        return false;
    }

    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }

    return true;
}

void matrix_init_kb(void){
  matrix_init_user();
  oled_request_wakeup();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
  oled_request_wakeup();

  switch (keycode) {
    case OLED_UP:
      if (record->event.pressed) {
        oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
      }
      return false;

    case OLED_DOWN:
      if (record->event.pressed) {
        oled_mode = (oled_mode + _NUM_OLED_MODES - 1) % _NUM_OLED_MODES;
      }
      return false;

    case KC_LGUI:
      win_key = record->event.pressed;
      return true;
      
    case KC_LCTL:
      ctrl_key = record->event.pressed;
      return true;
  }

  return process_record_user(keycode, record);
}