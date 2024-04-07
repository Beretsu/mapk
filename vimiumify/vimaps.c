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
#include "vimium.h"
#define MAXWORD 1000

const char *vimaps[LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
  [_BS] = LAYOUT(
    VU_NWMK, VF_BK  , VU_UP  , VU_PGUP, VU_TOP ,        VU_OPN  , VO_CURR, VO_NEW , VO_BK  , VO_BKN ,
    VU_BEGG, VU_LEFT, VU_DOWN, VU_RGHT, VU_END ,        VU_OPC  , VU_VIS , VU_LKC , VU_LKN , VU_FOIN,
    VU_GOMK, VF_FW  , VF_ENT , VU_PGDN, VU_BOTT,        VU_CP   , VU_VISL, VU_LKSW, VU_CPLK, VW_HELP,
                               VH_GOBK, VH_GOFW,        NULL    , VU_RLOD
  ),
};

const char *combovimaps[COMBOLAYOUTS][SIDES*ROWS*COLS] = {
  [_SS] = NULL,
};

char *reach(uint16_t a);

int main()
{
	int i, j;

	printf("unmapall\n");
	for (i=0; i < LAYERS; i++) {
		if (vimaps[i] == NULL)
			continue;
		for (j=0; j<SIDES*ROWS*COLS; j++) {
			if (keymaps[i][0][j] == KC_NO || vimaps[i][0][j] == NULL)
				continue;
			printf("map %s %s\n", reach(keymaps[i][0][j]), vimaps[i][0][j]);
		}
	}
	for (i=0; i < COMBOLAYOUTS; i++) {
		if (combovimaps[i] == NULL)
			continue;
		for (j=0; j<SIDES*ROWS*COLS; j++) {
			if (combomaps[i][j] == KC_NO || combovimaps[i][j] == NULL)
				continue;
			printf("map %s %s\n", reach(combomaps[i][j]), combovimaps[i][j]);
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

