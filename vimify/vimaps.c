#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../qk/modifiers.h"
#include "../qk/quantum_keycodes.h"
#include "../renegade/keydef.h"
#include "../shared.h"
#include "../translation.h"
#include "../combomap.h"
#include "../renegade/layouts.h"
#define MAXWORD 1000

const char *vimaps[LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT(
    "<C-g>"  ,"N"      ,"<Up>"   ,"<PageUp>","gg    ",    "<C-r>  ","u"      ,"O"      ,NULL     ,"r"      ,
    "0"      ,"<Left>" ,"<Down>" ,"<Right>" ,"$     ",    "p"      ,"v"      ,"i"      ,"a"      ,"A"      ,
    "%"      ,"n"      ,"/"      ,"<PageDown>","G   ",    "y"      ,"d"      ,"o"      ,NULL     ,"R"      ,
                                  "b"       ,"e"     ,    NULL     ,":"
  ),
/*  [_MS] = NULL,
  [_NV] = NULL,
  [_NU] = NULL,
  [_MC] = NULL,*/
};

const char *combovimaps[COMBOLAYOUTS][SIDES*ROWS*COLS] = {
  [_SS] = NULL,
};

char *reach(uint16_t a);

int main()
{
	int i, j;

	for (i=0; i < LAYERS; i++) {
		if (vimaps[i] == NULL)
			continue;
		for (j=0; j<SIDES*ROWS*COLS; j++) {
			if (keymaps[i][0][j] == KC_NO || vimaps[i][0][j] == NULL)
				continue;
			printf("noremap %s %s\n", reach(keymaps[i][0][j]), vimaps[i][0][j]);
		}
	}
	for (i=0; i < COMBOLAYOUTS; i++) {
		if (combovimaps[i] == NULL)
			continue;
		for (j=0; j<SIDES*ROWS*COLS; j++) {
			if (combomaps[i][j] == KC_NO || combovimaps[i][j] == NULL)
				continue;
			printf("noremap %s %s\n", reach(combomaps[i][j]), combovimaps[i][j]);
		}
	}
	return 0;
}

int lsearch(uint16_t a, uint16_t v[], int prog)
{
	int i, size;

	size = sizeof symkeys / sizeof(uint16_t);
	for (i = 0; i < size; i++)
		if (v[i] == a && key[a][prog] != NULL)
			return 1;
	return 0;
}

char s[MAXWORD];

char *reach(uint16_t a)
{
	uint16_t qk;

	if (lsearch(a, symkeys, 1)) {
		return key[a][1];
	} else if (IS_QK_MODS(a)) {
		qk = QK_MODS_GET_MODS(a) << 8;
		sprintf(s, "<%s-%s>", key[qk][1], key[QK_MODS_GET_BASIC_KEYCODE(a)][1]);
	} else if (IS_QK_LAYER_TAP(a)) {
		sprintf(s, "%s", key[QK_LAYER_TAP_GET_TAP_KEYCODE(a)][1]);
	} else if (IS_QK_MOD_TAP(a)) {
		sprintf(s, "%s", key[QK_MOD_TAP_GET_TAP_KEYCODE(a)][1]);
	} else
		return key[a][1];
	return s;
}


