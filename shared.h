#define MATRIX_ROWS 4
#define MATRIX_COLS 10
#define PROGMEM

#define LAYOUT( \
    a11    , a12    , a13    , a14    , a15    ,         b11    , b12    , b13    , b14    , b15    ,	\
    a21    , a22    , a23    , a24    , a25    ,         b21    , b22    , b23    , b24    , b25    ,	\
    a31    , a32    , a33    , a34    , a35    ,         b31    , b32    , b33    , b34    , b35    ,	\
                                    a41    , a42    , b41    , b42    ) 				\
{ 													\
  { a11    , a12    , a13    , a14    , a15    ,         b11    , b12    , b13    , b14    , b15    },	\
  { a21    , a22    , a23    , a24    , a25    ,         b21    , b22    , b23    , b24    , b25    },	\
  { a31    , a32    , a33    , a34    , a35    ,         b31    , b32    , b33    , b34    , b35    },	\
  { XXXXXXX, XXXXXXX, XXXXXXX, a41    , a42    ,         b41    , b42    , XXXXXXX, XXXXXXX, XXXXXXX},  \
}

