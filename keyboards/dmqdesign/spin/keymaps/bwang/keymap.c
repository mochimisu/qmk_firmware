#include QMK_KEYBOARD_H
// Raw HID communication
#include "raw_hid.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(/* Base */
                KC_7, KC_8, KC_9, KC_TRNS,
                KC_4, KC_5, KC_6, KC_TRNS,
                KC_1, KC_2, KC_3, KC_TRNS,
                KC_0, RGB_TOG, KC_ENTER
                ),
};

#if OLED_DRIVER_ENABLE
// HID input, using node-hid, following example from BlankSourceCode:
// https://github.com/BlankSourceCode/qmk-hid-display
bool is_hid_connected = false;
uint8_t screen_max_count = 0;
uint8_t screen_show_index = 0;
uint8_t screen_data_buffer[OLED_MATRIX_SIZE] = {0};
int screen_data_index = 0;

void raw_hid_send_screen_index(void) {
    // Send the current info screen index to the connected node script so that it can pass back the new data
    uint8_t send_data[32] = {0};
    send_data[0] = screen_show_index + 1; // Add one so that we can distinguish it from a null byte
    raw_hid_send(send_data, sizeof(send_data));
}
void raw_hid_receive(uint8_t *data, uint8_t length) {
    // PC connected, so set the flag to show a message on the master display
    is_hid_connected = true;

    // Initial connections use '1' in the first byte to indicate this
    if (length > 1 && data[0] == 1) {
        // New connection so restart screen_data_buffer
        screen_data_index = 0;

        // The second byte is the number of info screens the connected node script allows us to scroll through
        screen_max_count = data[1];
        if (screen_show_index >= screen_max_count) {
            screen_show_index = 0;
        }

        // Tell the connection which info screen we want to look at initially
        raw_hid_send_screen_index();
        return;
    }

    // Otherwise the data we receive is one line of the screen to show on the display
    if (length >= 21) {
        // Copy the data into our buffer and increment the number of lines we have got so far
        memcpy((char*)&screen_data_buffer[screen_data_index * 21], data, 21);
        screen_data_index++;

        // Once we reach 4 lines, we have a full screen
        if (screen_data_index == 4) {
            // Reset the buffer back to receive the next full screen data
            screen_data_index = 0;
        }
    }
}

const char *read_logo(void) {
  static char logo[] = {
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};

  return logo;
}

void oled_task_user(void) {
    if (is_hid_connected)
    {
        oled_write((char*)screen_data_buffer, false);
    } else {
        oled_write(read_logo(), false);
    }
}
void next_screen(void)
{
    if (screen_show_index + 1 < screen_max_count)
    {
        screen_show_index++;
        raw_hid_send_screen_index();
    }
}
void prev_screen(void)
{
    if (screen_show_index > 0)
    {
        screen_show_index--;
        raw_hid_send_screen_index();
    }
}
#else
void next_screen(void)
{
}
void prev_screen(void)
{
}
#endif

// Encoder
void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
      if (clockwise) {
        tap_code(KC_VOLU); //Example of using tap_code which lets you use keycodes outside of the keymap
      } else {
        tap_code(KC_VOLD);
      }
  } else if (index == 1) { /* Second encoder */
    if (clockwise) {
        next_screen();
    } else {
        prev_screen();
    }
  } else if (index == 2) { /* Third encoder */
    if (clockwise) {
        tap_code(KC_MS_WH_DOWN);
    } else {
        tap_code(KC_MS_WH_UP);
    }
  }
}

