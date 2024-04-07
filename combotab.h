#define MAYOR 1
#define MINOR 0
#define FORLOOPVALS 3

typedef struct press {
	int k[FORLOOPVALS];
	int r[FORLOOPVALS];
	int c[SIDES][ROWS][FORLOOPVALS];
	int wheight;
} Press;

typedef struct combotab {
	const uint16_t *keymap;
	char *name;
	uint16_t layers[LAYERS];
	int nlayers;
	Press *presses;
	int npresses;
} const Tab;

enum LOOPVALS { FST, LST, INCR };

#define _MBR(a,b) {{{a},{a},{a},{a}},{{b},{b},{b},{b}}}
#define _BRC(a)   {{{a},{a},{a},{a}},{{a},{a},{a},{a}}}
#define	CM ,
#define BRC(fst,lst,incr) _BRC(fst CM lst CM incr)
#define MBR(fst0,lst0,incr0,fst1,lst1,incr1) \
	_MBR(fst0 CM lst0 CM incr0, fst1 CM lst1 CM incr1)

#define ALL_SIDES {0,SIDES-1,1}
#define ALL_ROWS {0,ROWS-1,1}
#define ALL_COLS BRC(0,4,1)
#define ALL_LAYERS { _BS, _MS, _NV, _NU }
#define COMPLETE ALL_SIDES, ALL_ROWS, ALL_COLS, MAYOR
#define NOTHUMBS ALL_SIDES, {0,ROWS-2,1}, ALL_COLS, MAYOR

struct combotab tabs[] = {
  [_SS] = {combomaps[_SS], "horizontal side by side (2)", {_BS, _NU}, 2,
	(Press[]){{COMPLETE}, {ALL_SIDES, ALL_ROWS, BRC(1,4,1), MAYOR}}, 2},

  [_TT] = {combomaps[_TT], "vertical side by side (2)", ALL_LAYERS, LAYERS,
	(Press[]){{COMPLETE}, {ALL_SIDES, {1,3,1} , ALL_COLS, MAYOR}}, 2},

  [_S1S] = {combomaps[_S1S], "horizontal side skip one (2)", ALL_LAYERS, LAYERS,
	(Press[]){{COMPLETE}, {ALL_SIDES, ALL_ROWS, BRC(2,4,1), MAYOR}}, 2},

  [_S2S] = {combomaps[_S2S], "horizontal side skip two (2) ", ALL_LAYERS, LAYERS,
	(Press[]){{COMPLETE}, {ALL_SIDES, ALL_ROWS, BRC(3,4,1), MAYOR}}, 2},

  [_S3S] = {combomaps[_S3S], "horizontal side skip three (2)", ALL_LAYERS, LAYERS,
	(Press[]){{COMPLETE}, {ALL_SIDES, ALL_ROWS, BRC(4,4,1), MAYOR}}, 2},

  [_OI] = {combomaps[_OI], "oposite index; full keyboard (2)", {_BS,_NU}, 2,
	(Press[]){{NOTHUMBS}, {{1,0,-1}, {1,1,1}, MBR(3,3,1,1,1,1), MINOR}}, 2},

  [_OM] = {combomaps[_OM], "oposite middle; full keyboard (2)", {_BS,_NU}, 2,
	(Press[]){{NOTHUMBS}, {{1,0,-1}, {1,1,1}, BRC(2,2,1), MINOR}}, 2},

  [_OBM] = {combomaps[_OBM], "oposite middle bottom; full keyboard (2)", {_BS,_NU}, 2,
	(Press[]){{NOTHUMBS}, {{1,0,-1}, {2,2,1}, BRC(2,2,1), MINOR}}, 2},

  [_OT1] = {combomaps[_OT1], "oposite thumb1; full keyboard (2)", {_BS,_NU}, 2,
	(Press[]){{NOTHUMBS}, {{1,0,-1}, {3,3,1}, MBR(3,3,1,1,1,1), MINOR}}, 2},
 
  [_OT2] = {combomaps[_OT2], "oposite thumb2; full keyboard (2)", {_BS,_NU}, 2,
	(Press[]){{NOTHUMBS}, {{1,0,-1}, {3,3,1}, MBR(4,4,1,0,0,1), MINOR}}, 2},
};

