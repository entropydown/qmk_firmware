#include "viterbi.h"
#include "action_layer.h"
#include "eeconfig.h"
#ifdef RGBLIGHT_ENABLE
#include "rgblight.h"
#endif

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _FN 1
#define _SHIFTFN 2

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  SHIFTFN
};

#define KC_ KC_TRNS
#define _______ KC_TRNS

#define KC_SWIN LGUI(KC_TILD)   // Switch between windows
#define KC_SAPP LGUI(KC_TAB)    // Switch between applications
#define KC_FN1 MO(_FN)
#define KC_FN2 MO(_SHIFTFN)
#define KC_LCAG LCAG(KC_NO)
#define KC_RST RESET
#define KC_U1 S(KC_1)
#define KC_SSHOT LGUI(KC_DLR)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
     ESC , 1  , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,BSPC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     TAB,   Q , W  , E  , R  , T  , Y  ,     Y  , U  , I  , O  , P,  LBRC, RBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     CAPS,  A , S  , D  , F  , G  , END,     H  , J  , K  , L  ,SCLN,QUOT,ENT,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
     FN2, Z , X  , C  , V  , B  ,   GRV,     N  , M  ,COMM,DOT ,SLSH,  FN2, FN1,
  //|----+----+----+----+----+----+----|    |----+----+-.---+----+----+----+----|
     FN1 ,LCTL,LALT,LGUI,SPC, SPC ,SSHOT,     SPC, RALT,LGUI, NO, PGDN,PGUP,RCTL
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_FN] = LAYOUT_kc(
  //,----+----+----+----+----+----+----.    ,----+----+----+----+----+----+----.
         , F1 , F2 , F3 , F4 , F5 , F6 ,      F7 , F8 , F9 ,F10 ,F11 ,F12 ,BSLS,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,RST ,    ,    ,         ,    ,    ,    ,    ,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,HOME,     ,    ,    ,    ,    ,    ,    PGUP,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,    ,    ,    ,    , UP ,PGDN,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,    ,    ,    ,    ,    ,    ,         ,MUTE,VOLD,VOLU,LEFT,DOWN,RGHT
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  ),

  [_SHIFTFN] = LAYOUT_kc(
         ,  1 , 2  , 3  , 4  , 5  , 6  ,      7  , 8  , 9  , 0  ,MINS,EQL ,PIPE,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,Q   , W ,  E , R   ,  T , Y  ,      Y  , U  , I  , O  , P,  LBRC,RBRC,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         , A  , S  , D  , F  , G  ,    ,     H   , J  , K  , L  ,SCLN,QUOT,    ,
  //|----+----+----+----+----+----+----|    |----+----+----+----+----+----+----|
         ,  Z , X  , C  , V  , B  ,GRV ,      N  , M  ,COMM,DOT ,SLSH,    ,    ,
  //|----+----+----+----+----+----+----|    |----+----+-.---+----+----+----+----|
     ,,,,,,,,,,,,,
  //`----+----+----+----+----+----+----'    `----+----+----+----+----+----+----'
  )
};

bool shift_held = false;

bool process_record_user(uint16_t kc, keyrecord_t *rec) {
  uint8_t layer;
  layer = biton32(layer_state);
  if (layer == _SHIFTFN) {
    if (kc >= KC_A && kc <= KC_SLASH) {
      if (rec->event.pressed) {
        if (shift_held != true) {
          register_mods(MOD_LSFT);
          shift_held = true;
        }
      } else {
        unregister_mods(MOD_LSFT);
        shift_held = false;
      }
    }
  } else {
    if (shift_held) {
      unregister_mods(MOD_LSFT);
    }
  }

  return true;
}
