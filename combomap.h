/* define max ranges */
#define SIDES 2
#define ROWS 4
#define COLS 5
#define LAYERS 5
#define COMBOLAYOUTS 10
#define AAAAAAA KC_NO

enum combolayouts {
	_SS,
	_TT,
	_S1S,
	_S2S,
	_S3S,
	_OI,
	_OM,
	_OBM,
	_OT1,
	_OT2,
};

const uint16_t combomaps[][SIDES*ROWS*COLS] = {
  [_SS] = {
    AAAAAAA, KC_LT  , KC_LBRC, KC_AMPR,         KC_COLN, KC_RBRC, KC_GT  , AAAAAAA,
    KC_Z   , KC_ESC , KC_LPRN, KC_PIPE,         KC_HASH, KC_RPRN, KC_TAB , ST_UPDR,
    AAAAAAA, ST_LCMT, KC_LCBR, KC_GRV ,         KC_DLR , KC_RCBR, ST_RCMT, AS_TOGG,
                               QK_BOOT,         QK_MAKE, 
  },

  [_TT] = {
    OS_LALT, OS_LSFT, OS_LCTL, OS_LGUI, AAAAAAA,         AAAAAAA, OS_RGUI, OS_RCTL, OS_RSFT, OS_RALT,
    AS_DOWN, TG(_MS), TG(_NU), TG(_NV), AAAAAAA,         AAAAAAA, TG(_NV), CW_TOGG, TG(_MS), AS_UP  ,
  },

  [_S1S] = {
    KC_A, WT_LEFT, KC_C,   KC_D, WT_RGHT, KC_F,
    KC_G, WN_BAK , KC_I,   KC_J, WN_FWD , KC_L,
    KC_M, WT_CLSE, KC_O,   KC_P, WT_REOP, KC_R,
  },

  [_S2S] = {
    KC_A, KC_B,   KC_C, KC_D,
    KC_E, KC_F,   KC_G, KC_H,
    KC_I, KC_J,   KC_K, KC_L,
  },

  [_S3S] = {
    KC_A,   KC_B,
    KC_C,   KC_D,
    KC_E,   KC_F,
  },

  [_OI] = {
    AAAAAAA, ST_LEQL, ST_OR  , KC_BSLS, ST_MNMN,         ST_PLPL, KC_SLSH, ST_AND , ST_GEQL, AAAAAAA,
    KC_EXLM, KC_MINS, KC_ASTR, KC_EQL , ST_ARRW,         AAAAAAA, XXXXXXX, XXXXXXX, KC_PLUS, KC_QUES,
    KC_PERC, ST_MNEQ, XXXXXXX, ST_EQL , KC_CIRC,         KC_TILD, ST_NEQL, ST_COMM, ST_PLEQ, KC_AT  ,
  },

  [_OM] = {
    AAAAAAA, AAAAAAA, KC_UP  , KC_PGUP, KC_HOME,         AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA,
    AAAAAAA, KC_LEFT, KC_DOWN, KC_RGHT, AAAAAAA,         AAAAAAA, XXXXXXX, XXXXXXX, AAAAAAA, AAAAAAA,
    AAAAAAA, AAAAAAA, XXXXXXX, KC_PGDN, KC_END ,         AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA,
  },

  [_OBM] = {
    AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA,         AAAAAAA, KC_WH_U, KC_MS_U, AAAAAAA, AAAAAAA,
    AAAAAAA, AAAAAAA, XXXXXXX, XXXXXXX, AAAAAAA,         KC_WH_L, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_R,
    AAAAAAA, AAAAAAA, XXXXXXX, AAAAAAA, AAAAAAA,         AAAAAAA, KC_WH_D, AAAAAAA, AAAAAAA, AAAAAAA,
  },

  [_OT1] = {
    AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA,         AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA, AAAAAAA,
    KC_6   , KC_4   , KC_0   , KC_2   , AAAAAAA,         AAAAAAA, KC_3   , KC_1   , KC_5   , KC_7   ,
    AAAAAAA, AAAAAAA, AAAAAAA, KC_8   , AAAAAAA,         AAAAAAA, KC_9   , AAAAAAA, AAAAAAA, AAAAAAA,
  },
 
  [_OT2] = {
    KC_MUTE, KC_VOLD, KC_VOLU, KC_MPLY, KC_MSTP,         KC_MSEL, KC_MPRV, KC_MNXT, KC_MRWD, KC_MFFD,
    KC_F6  , KC_F4  , KC_F10 , KC_F2  , AAAAAAA,         AAAAAAA, KC_F3  , KC_F1  , KC_F5  , KC_F7  ,
    AAAAAAA, AAAAAAA, KC_F12 , KC_F8  , AAAAAAA,         AAAAAAA, KC_F9  , KC_F11 , AAAAAAA, AAAAAAA,
  },
};
