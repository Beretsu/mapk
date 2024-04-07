#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "./qk/modifiers.h"
#include "./qk/quantum_keycodes.h"
#include "./renegade/keydef.h"
#include "shared.h"
#include "translation.h"
#include "combomap.h"
#include "combotab.h"
#include "./renegade/layouts.h"
#define YES 1
#define NO 0
#define MAXPRESS 1000
#define MAXKEYS 1000
#define MAXWORD 1000

int sides;
int rows;
int rowlens[SIDES][ROWS];
int found;
const uint16_t *arr[LAYERS][SIDES][ROWS];
uint16_t chords[MAXPRESS][MAXKEYS];
uint16_t base[MAXPRESS][MAXKEYS];
int count;

int writecombos(struct combotab *t);

int main()
{
	writecombos(tabs);
	return 0;
}

void query(struct combotab t, int layer, uint16_t (*chords)[MAXKEYS]);
int fixtable(struct combotab t);
void cmpcols(struct press *p, int (*b)[ROWS]);
char *reach(uint16_t a);
int namecount;

int writecombos(struct combotab *t)
{
	int i, j, k, l, m, pass, trans, ntabs;

	pass = YES;
	for (i = 0; i < LAYERS; i++)
		for (j=0; j < MATRIX_ROWS; j++) {
			arr[i][0][j] = keymaps[i][j];
			for (k=1; k < SIDES; k++)
				arr[i][k][j] = keymaps[i][j]+COLS;
		}
	ntabs = sizeof tabs / sizeof tabs[0];
	for (i = 0; i < ntabs; i++) {
		printf("/* %s */\n", t[i].name);
		fixtable(t[i]);
		query(t[i], _BS, base);
		for (j=0; j < t[i].nlayers; j++) {
			printf("/* layer: %s */\n", laykey[t[i].layers[j]]);
			query(t[i], t[i].layers[j], chords);
			for (k=0, m=0; k < count; k++) {
				pass = YES;
				trans = 0;
			/*	if (t[i].keymap[m] == _______ || t[i].keymap[m] == KC_TRNS
						|| t[i].keymap[m] == KC_TRANSPARENT)
					t[i].keymap[m] = base[l][k] */
				for (l=0; l<t[i].npresses; l++) {
					if (chords[l][k] == KC_NO || chords[l][k] == XXXXXXX) {
						pass = NO;
						break;
					} else if (chords[l][k]==KC_TRANSPARENT || chords[l][k]==KC_TRNS
						|| chords[l][k]==_______) {
						trans++;
						chords[l][k] = base[l][k];
					}
				}
				if (pass == NO) {
					continue;
				}
				if (trans == t[i].npresses || t[i].keymap[m] == KC_NO) {
					m++;
					continue;
				}
				printf("COMB(v%d, %-7s, ", namecount++, reach(t[i].keymap[m++]));
				for (l=0; l<t[i].npresses-1; l++)
					printf("%-7s, ", reach(chords[l][k]));
				printf("%-7s)\n", reach(chords[l][k]));
			}
			putchar('\n');
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

	if (lsearch(a, symkeys, 0)) {
		return key[a][0];
	} else if (IS_QK_MODS(a)) {
		qk = QK_MODS_GET_MODS(a) << 8;
		sprintf(s, "%s(%s)", key[qk][0], key[QK_MODS_GET_BASIC_KEYCODE(a)][0]);
	} else if (IS_QK_ONE_SHOT_MOD(a)) {
		sprintf(s, "%s(%s)", key[QK_ONE_SHOT_MOD][0], modkey[QK_ONE_SHOT_MOD_GET_MODS(a)]);
	} else if (a >= QK_TO && a <= QK_LAYER_TAP_TOGGLE_MAX) {
		qk = a & (~0x1F);
		sprintf(s, "%s(%s)", key[qk][0], laykey[QK_TO_GET_LAYER(a)]);
	} else if (IS_QK_LAYER_MOD(a)) {
		sprintf(s, "%s(%s,%s)", key[QK_LAYER_MOD][0], laykey[QK_LAYER_MOD_GET_LAYER(a)],
				modkey[QK_LAYER_MOD_GET_MODS(a)]);
	} else if (IS_QK_LAYER_TAP(a)) {
		sprintf(s, "%s(%s,%s)", key[QK_LAYER_TAP][0], laykey[QK_LAYER_TAP_GET_LAYER(a)],
				key[QK_LAYER_TAP_GET_TAP_KEYCODE(a)][0]);
	} else if (IS_QK_MOD_TAP(a)) {
		sprintf(s, "%s(%s,%s)", key[QK_MOD_TAP][0], modkey[QK_MOD_TAP_GET_MODS(a)],
				key[QK_MOD_TAP_GET_TAP_KEYCODE(a)][0]);
	} else 
		return key[a][0];
	return s;
}

int cmp(int a, int b, int incr)
{
	return (incr >= 0) ? a <= b : a <= b;
}

int add(int a, int b, int incr)
{
	return (incr >= 0) ? a + b : a - b;
}

int get_minor_chords(struct press *p, uint16_t *chords, int (*fun1)(int,int), int (*fun2)(int,int), int);
int get_mayor_chords(struct press *p, uint16_t *chords, int (*fun1)(int,int), int (*fun2)(int,int), int);

void query(struct combotab t, int layer, uint16_t (*chords)[MAXKEYS])
{
	int i, (*fun1)(int, int), (*fun2)(int, int);
	struct press *p;

	for (i=0; i < t.npresses; i++) {
		p = t.presses+i;
		if (p->wheight == MINOR)
			get_minor_chords(p, chords[i], fun1, fun2, layer);
		else
			count = get_mayor_chords(p, chords[i], fun1, fun2, layer);
	}
}

int get_minor_chords(struct press *p, uint16_t *chords, int (*fun1)(int,int), int (*fun2)(int,int), int layer)
{
	int r, k, c, rr, kk, cc, count;

	count = 0;
	for (r=0, rr=p->r[FST]; r<=rows; r++) {
		for (k=0, kk=p->k[FST]; k <= sides; k++) {
			for (c=0, cc=p->c[kk][rr][FST]; c <= rowlens[kk][rr]; c++) {
				chords[count++] = arr[layer][kk][rr][cc];
				if (cmp(cc+p->c[kk][rr][INCR], p->c[kk][rr][LST], p->c[kk][rr][INCR]))
					cc += p->c[kk][rr][INCR];
			}
			if (cmp(kk+p->k[INCR], p->k[LST], p->k[INCR]))
				kk += p->k[INCR];
		}
		if (cmp(rr+p->r[INCR], p->r[LST], p->r[INCR]))
			rr += p->r[INCR];
	}
	return count;
}

int get_mayor_chords(struct press *p, uint16_t *chords, int (*fun1)(int,int), int (*fun2)(int,int), int layer)
{
	int r, k, c, count;

	count = 0;
	for (r=p->r[FST]; cmp(r,add(p->r[FST],rows,p->k[INCR]),p->r[INCR]); r += p->r[INCR])
		for (k=p->k[FST]; cmp(k,add(p->k[FST],sides,p->k[INCR]),p->k[INCR]); k += p->k[INCR])
			for (c=p->c[k][r][FST]; cmp(c,add(p->c[k][r][FST],
			rowlens[k][r],p->c[k][r][INCR]),p->c[k][r][INCR]); c += p->c[k][r][INCR])
				chords[count++] = arr[layer][k][r][c];
	return count;
}

int fixtable(struct combotab t)
{
	int i, j, tmp;
	struct press *p;
	int (*b)[ROWS] = rowlens;

	found = NO;
	for (i=0; i < t.npresses; i++) {
		p = t.presses+i;
		if (p->wheight == MINOR)
			continue;
		tmp = abs(p->k[FST] - p->k[LST])/p->k[INCR];
		sides = (found == NO || tmp < sides) ? tmp : sides;
		tmp = abs(p->r[FST] - p->r[LST])/p->r[INCR];
		rows = (found == NO || tmp < rows) ? tmp : rows;
		for (j=0; j<ROWS*SIDES; j++) {
			tmp = abs(p->c[0][j][FST] - p->c[0][j][LST])/p->c[0][j][INCR];
			b[0][j] = (found==NO || tmp < b[0][j]) ? tmp : b[0][j];
		}
		found = YES;
	}
	return 0;
}

