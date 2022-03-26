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

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    oled_request_wakeup();
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
  // switch (keycode) {
  //   case OLED_TOGG:
  //     if(!clock_set_mode){
  //       if (record->event.pressed) {
  //         oled_mode = (oled_mode + 1) % _NUM_OLED_MODES;
  //       }
  //     }
  //     return false;
  //   default:
  //     break;
  // }

  return process_record_user(keycode, record);
}