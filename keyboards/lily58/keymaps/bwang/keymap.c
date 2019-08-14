#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif


extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _BASE 0
#define _GAME 1
#define _FN 2

enum custom_keycodes {
  BASE = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* BASE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  [   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  |BackSp|
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LCTRL |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   -   |    |   =   |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LGUI | LAlt |Space | /   `   /       \Enter \  |Space |  FN  |  ]   |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_BASE] = LAYOUT( \
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, \
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTRL, KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,   KC_MINS,  KC_EQL, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
                             KC_LGUI, KC_LALT, KC_SPC, KC_GRV,   KC_ENT, KC_SPC,  MO(_FN), KC_RBRC \
),
/* Gaming
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|   6   |    | RGUI  |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   | LAlt |      |      | /  ESC  /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_GAME] = LAYOUT( \
  KC_GRV,  _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,                     _______, _______, _______, _______, _______, _______,  \
  _______, _______, _______, _______, _______, _______,  KC_6,    KC_RGUI,  _______, _______, _______, _______, _______, _______, \
                             KC_LALT, _______, _______,  KC_ESC,  _______,  _______, _______, _______ \
),

/* FN
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
<<<<<<< HEAD
 * |      | Home |  Up  | End  | PgUp |      |                    |      |      |  Up  |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Left | Down | Right| PgDn |      |-------.    ,-------|      | Left | Down | Right|      |PrtScr|
 * |------+------+------+------+------+------|       |    |Gaming |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |  \   |      |
=======
 * |      | Home |  Up  | End  | PgUp |      |                    |      |      |      |      |      | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | Left | Down | Right| PgDn |      |-------.    ,-------|      |      |      |      |      |PrtScr|
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
>>>>>>> 46eb4c5b5... quefrency update, lily keymap
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_FN] = LAYOUT( \
  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  \
  _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______,                     _______, _______, KC_UP,   _______, _______, KC_F12,  \
  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,                     _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_PSCR, \
  _______, _______, _______, _______, _______, _______,  _______, TG(_GAME),_______, _______, _______, _______, KC_BSLS, _______, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
)
};

void matrix_init_user(void) {
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
const char *read_apm(void);

//const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
//void set_timelog(void);
//const char *read_timelog(void);
void record_apm_action(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_apm());
    //matrix_write_ln(matrix, read_keylog());
    //matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    //set_timelog();
    record_apm_action();
#endif
  }
  return true;
}
