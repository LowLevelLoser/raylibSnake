#ifndef GAME_H_
#define GAME_H_

#define SCREEN_SIDES 800
#define SCORE_MARGIN 25
#define CELLS 16
#define CELL_SIZE SCREEN_SIDES/CELLS

#define UP 3
#define DOWN 5
#define LEFT 7
#define RIGHT 9

#define APPLE -1

#define RUNNING_STATE 0
#define GAME_OVER_STATE 1
#define WIN_STATE 2

#include <raylib.h>

typedef struct {
    int head_max;
    int head_X;
    int head_Y;
    int board [CELLS][CELLS];
    int direction;
    int prev_direction;
    int queued_direction;
    int state;
    char score_c[50];
    Sound score_beep;
    Sound game_over_beep;
} game_t;

#endif
