#include QMK_KEYBOARD_H // Incluye el archivo principal de QMK para obtener todas las funciones, macros, constantes necesarias para compilar el keymap correctamente.

extern keymap_config_t keymap_config; // Se crea una instancia de keymap_config_t (la cual viene de otro archivo)

/*#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif  // al parecer no se usa porque tengo la opcion desactivada en mi rules.mk
*/

enum layers { // enumera cada elemento secuencialmente comenzanod en 0, aquí usa un nombre para el enum porque lo referenciará
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum { // aquí al parecer no lo referenciará por lo que no le da el nombre, la numeración es opcional
  TD_LGUI_ALTSPC = 0,
  TD_LSFT_TAB = 1,
  TD_2_F2 = 2,
  TD_4_F4 = 3,
  TD_5_F5 = 4,
  TD_0_F10 = 5,
  TD_LSFTTAB_CAPS = 6
};

//Aquí se definen los tap_dance ACTION_TAP_DANCE_DOUBLE(1toque,2toques), 
tap_dance_action_t tap_dance_actions[] = {
  [TD_LGUI_ALTSPC]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LALT(KC_SPC)),
  [TD_LSFT_TAB] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT,KC_TAB), 
  [TD_2_F2] = ACTION_TAP_DANCE_DOUBLE(KC_2,KC_F2),
  [TD_4_F4] = ACTION_TAP_DANCE_DOUBLE(KC_4,KC_F4),
  [TD_5_F5] = ACTION_TAP_DANCE_DOUBLE(KC_5,KC_F5),
  [TD_0_F10] = ACTION_TAP_DANCE_DOUBLE(KC_0,KC_F10),
  [TD_LSFTTAB_CAPS] = ACTION_TAP_DANCE_DOUBLE(KC_CAPS,LSFT(KC_TAB))
};

// Apretar rapido = Windows(KC_LGUI) , Mantener = Alt Izq (LALT). el _T al final la convierte en la macro de mod_tap. Hay pocas teclas que tienen esta macro disponible
#define KC_LGALT LALT_T(KC_LGUI)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST,
  BSPC_DEL,

  //Excel
  EXC_F,
  EXC_V
};

// Las distintas capas de mi teclado definidas como matrices de teclas.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //+----------------+-----+-----+-----+-----+-----+    +-----+-----+--------+-------+--------+----------+
         KC_ESC,      KC_Q, KC_W, KC_E, KC_R, KC_T,      KC_Y, KC_U,   KC_I,   KC_O,    KC_P,   BSPC_DEL,
  //|----------------+-----+-----+-----+-----+-----+    +-----+-----+--------+-------+--------+----------|
     TD(TD_LSFT_TAB), KC_A, KC_S, KC_D, KC_F, KC_G,      KC_H, KC_J,   KC_K,   KC_L,  KC_SCLN,  KC_QUOT,
  //|----------------+-----+-----+-----+-----+-----+    +-----+-----+--------+-------+--------+----------|
         KC_LCTL,     KC_Z, KC_X, KC_C, KC_V, KC_B,      KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,  KC_RALT,
  //|----------------------------------------------+    +------------------------------------------------|
                 TD(TD_LGUI_ALTSPC), LOWER, KC_SPC,      KC_ENT, RAISE, KC_LALT
  //            |-------------------+------+-------+    +-------+------+-------|
  ),

  [_LOWER] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
    KC_ESC, KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,                   KC_HOME, KC_PGUP, KC_UP, KC_PGDN, KC_NO, BSPC_DEL,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    TD(TD_LSFT_TAB), KC_1,   TD(TD_2_F2),   KC_3,  TD(TD_4_F4), TD(TD_5_F5), KC_END, KC_LEFT, KC_DOWN, KC_RIGHT, KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    KC_LCTL, KC_6,   KC_7,   KC_8,  KC_9, TD(TD_0_F10),              KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                                  //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
    KC_ESC,KC_EXLM,KC_AT,KC_HASH,KC_DLR,KC_PERC,              KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,BSPC_DEL,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    TD(TD_LSFTTAB_CAPS), KC_NO, KC_NO, KC_NO, EXC_F, KC_NO,                KC_MINS,KC_PLUS,KC_LCBR,KC_RCBR,KC_PIPE,KC_GRV,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_LCTL, KC_NO, KC_NO, KC_NO, EXC_V,KC_NO,                KC_UNDS,KC_EQL,KC_LBRC,KC_RBRC,KC_BSLS,KC_TILD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                ,-----------------------------------------.
    QK_BOOT,RGBRST, KC_NO, KC_NO, KC_NO, KC_NO,                KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,KC_NO,               KC_BRIU, KC_MPRV,KC_MPLY, KC_MNXT, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,KC_NO,               KC_BRID, KC_VOLD, KC_MUTE, KC_VOLU, KC_NO, RGB_RMOD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_LGUI, LOWER, KC_SPC,  KC_ENT, RAISE, KC_LALT
                              //`--------------------'  `--------------------'
  )
};

// Función para activar la tercera capa al presionar las 2 primeras.
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}


int RGB_current_mode;

// Imprime 5 espacios en blanco en el oled, sin saltar linea (false) 
void render_space(void) {
    static const char PROGMEM space[] = {

        // PLANTILLA DE CARACTERES PARA CORNE EN HORIZONTAL
        /*0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 
        0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F, 0x40, 0x41, 0x42, 0x43, 0x44, 0x44, 0x45, 0x46, 0x47, 0x48,
        0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 
        0x5E, 0x5F, 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0*/
        
        // DISTRIBUCIÓN DE LOGO CORNE
        0x94, 0x95, 0x96, 0x97, 0x98, 
        0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 
        0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0

        // DISTRIBUCION DE LAYER BUTTONS
        
    };

    static const char PROGMEM corne[] = {
        // corne
        0x9A, 0x9B, 0x9C, 0x9D, 0x9E, 
        0x0A, 0
    };
    oled_write(space, false); //false
    oled_write(corne, false);

}

// Esta función se llama una vez al iniciar el teclado, justo después de encender o resetear.
// Puede inicializar variables, configurar capas, capturar el estado del RGB, OLED, etc.
void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //render_space();
}

// Define la rotación en 270 nada más activarse la pantalla
// Esta rotación afecta todo el contenido, por lo que habrá que probarlo sin la rotacion.
#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { 
  return OLED_ROTATION_270;//OLED_ROTATION_270; 
}



// función del logo corne.
void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,192,224,240,240,240,240,240,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,112,112,112,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,128,192,224,240,  0,  0,240,252,254,255,255,255,  1,240,252,255,255,255,255,255,255,255,255,127, 31,  7,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,254,254,254,  0,  0,240,248,252, 30, 14, 14, 14, 14, 14, 14, 30,252,248,240,  0,  0,254,254,252, 28, 14, 14, 14, 14,  0,  0,254,254,252, 28, 14, 14, 14, 14, 30,252,248,240,  0,  0,240,248,252,222,206,206,206,206,206,206,222,252,248,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0, 63,255,255,255,254,240,255,255,255,255,255,255,248,255,255,255,255,255,255,255,255,255,193,128,128,128,192,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,255,255,255,  0,  0, 15, 31, 63,120,112,112,112,112,112,112,120, 63, 31, 15,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0,  0,  0,  0,  0,127,127,127,  0,  0, 15, 31, 63,121,113,113,113,113,113,113,121, 61, 29, 13,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  3,  3,  3,  3,  1,  1,  3,  3,  7,  7,  7,  3,  3,  1,  3,  7,  7,  7,  7,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  7,  7,  7,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 255
    };

    oled_write_raw_P(qmk_logo, sizeof(qmk_logo));
}

void render_layer_state(void) {
    static const char PROGMEM default_raise[] = { //default_layer
        0x60, 0x61, 0x62, 0x63, 0x64,
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0};
    static const char PROGMEM press_raise[] = { //raise_layer
        0x65, 0x66, 0x67, 0x68, 0x69,
        0x85, 0x86, 0x87, 0x88, 0x89,
        0xA5, 0xA6, 0xA7, 0xA8, 0xA9,
        0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0};
    static const char PROGMEM default_lower[] = { //lower_layer
        0x6A, 0x6B, 0x6C, 0x6D, 0x6E,
        0x8A, 0x8B, 0x8C, 0x8D, 0x8E,
        0xAA, 0xAB, 0xAC, 0xAD, 0xAE,
        0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0};
    static const char PROGMEM press_lower[] = { //adjust_layer
        0x6F, 0x70, 0x71, 0x72, 0x73,
        0x8F, 0x90, 0x91, 0x92, 0x93,
        0xAF, 0xB0, 0xB1, 0xB2, 0xB3,
        0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(press_raise, false);
        oled_write_P(press_lower, false);
    } else if(layer_state_is(_LOWER)) {
        oled_write_P(default_raise, false);
        oled_write_P(press_lower, false);
    } else if(layer_state_is(_RAISE)) {
        oled_write_P(press_raise, false);
        oled_write_P(default_lower, false);
    } else {
        oled_write_P(default_raise, false);
        oled_write_P(default_lower, false);
    }
}

bool oled_task_user(void) {
    // Renders the current keyboard state (layers and mods)
    // render_logo();
    render_space();
    render_layer_state();
    // render_space();
    // render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    // render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    return false;
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static uint8_t saved_mods   = 0;

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
        rgb_matrix_set_color_all(0, 0, 255);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case EXC_F:
        if (record->event.pressed) {
          SEND_STRING(SS_DOWN(X_LCTL) SS_TAP(X_UP));
          clear_keyboard();
          SEND_STRING(SS_DOWN(X_LALT) SS_TAP(X_DOWN));
          clear_keyboard();
          SEND_STRING(SS_TAP(X_B));

        } else {
          clear_keyboard();
        }
        return false;
    case EXC_V:
        if (record->event.pressed) {
          SEND_STRING(SS_TAP(X_APP) SS_TAP(X_R) SS_TAP(X_ENT) SS_TAP(X_V));
        } else {
          clear_keyboard();
        }
        return false;
    case BSPC_DEL:
        if (record->event.pressed) {
          saved_mods = get_mods() & MOD_MASK_SHIFT;

          if (saved_mods == MOD_MASK_SHIFT) { // Both shifts pressed
            register_code(KC_DEL);
          } else if (saved_mods) {  // One shift pressed
            del_mods(saved_mods); // Remove any Shifts present
            register_code(KC_DEL);
            add_mods(saved_mods); // Add shifts again
          } else {
            register_code(KC_BSPC);
          }
        } else {
          unregister_code(KC_DEL);
          unregister_code(KC_BSPC);
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif

