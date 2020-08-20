/* Copyright 2019-2020 DMQ Design
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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                KC_7, KC_8, KC_9, KC_TRNS,
                KC_4, KC_5, KC_6, KC_TRNS,
                KC_1, KC_2, KC_3, KC_TRNS,
                KC_0, RGB_TOG, KC_ENTER
                ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise) {
      rgblight_increase_hue(); //Cycle through the RGB hue
    } else {
      rgblight_decrease_hue();
    }
  } else if (index == 1) { /* Second encoder */  
    if (clockwise) {
      tap_code(KC_VOLU); //Example of using tap_code which lets you use keycodes outside of the keymap
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 2) { /* Third encoder */  
    if (clockwise) {
      rgblight_increase_val(); //Change brightness on the RGB LEDs
    } else {
      rgblight_decrease_val();
    }
  }
}

#if OLED_DRIVER_ENABLE
const char *read_logo(void) {
  static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

  return logo;
}


void oled_task_user(void) {
    oled_write(read_logo(), false);
}
#endif
