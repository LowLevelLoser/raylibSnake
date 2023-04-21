#include <raylib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "game.h"
#include "logic.h"

void spawn_apple(game_t *game);
void move_snake(game_t *game);
void restart(game_t *game);

void run_game(game_t *game, int frame){


    if(game->queued_direction != -1 && abs(game->queued_direction - game->prev_direction) != 2){
        game->direction = game->queued_direction;
        game->queued_direction = -1;
    }

    switch(GetKeyPressed()){
        case KEY_UP:
            if (game->prev_direction != DOWN){
                game->direction = UP;
                game->queued_direction = -1;
            }
            else
                game->queued_direction = UP;
            break;
        case KEY_DOWN:
            if (game->prev_direction != UP){
                game->direction = DOWN;
                game->queued_direction = -1;
            }
            else
                game->queued_direction = DOWN;
            break;
        case KEY_RIGHT:
            if (game->prev_direction != LEFT){
                game->direction = RIGHT;
                game->queued_direction = -1;
            }
            else
                game->queued_direction = RIGHT;
            break;
        case KEY_LEFT:
            if (game->prev_direction != RIGHT){
                game->direction = LEFT;
                game->queued_direction = -1;
            }
            else
                game->queued_direction = LEFT;
            break;
        case KEY_R:
            restart(game);
            break;
    }

    if(frame % 2 == 0 && game->state == RUNNING_STATE){
        move_snake(game);
        game->prev_direction = game->direction;
    }
}


void move_snake(game_t *game){
    switch(game->direction){
        case UP:
            game->head_Y--;
            break;
        case DOWN:
            game->head_Y++;
            break;
        case LEFT:
            game->head_X--;
            break;
        case RIGHT:
            game->head_X++;
            break;
    }

    if(game->head_X == -1) game->head_X = CELLS - 1;
    game->head_X = game->head_X%CELLS;
    if(game->head_Y == -1) game->head_Y = CELLS - 1;
    game->head_Y = game->head_Y%CELLS;

    if(game->board[game->head_X][game->head_Y] < 0){
        game->head_max++;
        snprintf(game->score_c, 50, "score: %d", game->head_max);
        game->board[game->head_X][game->head_Y] = game->head_max;
        PlaySound(game->score_beep);
        if(game->head_max == 256)
            game->state = WIN_STATE;
        else
            spawn_apple(game);
    }

    else if(game->board[game->head_X][game->head_Y] > 1){
        game->state = GAME_OVER_STATE;
        PlaySound(game->game_over_beep);
    }

    else{
        for(int i = 0; i < CELLS*CELLS; i++)
            if(game->board[i%CELLS][i/CELLS] > 0)
                game->board[i%CELLS][i/CELLS]--;
        game->board[game->head_X][game->head_Y] = game->head_max;
    }
}

void spawn_apple(game_t *game){
    srand(time(NULL));
    int r = rand()%(CELLS*CELLS);
    while(game->board[r%CELLS][r/CELLS] != 0){
        r = (r+1)%(CELLS*CELLS);
    }
    game->board[r%CELLS][r/CELLS] = -1;
}


void restart(game_t *game){
    for(int i = 0; i < CELLS*CELLS; i++)
            game->board[i%CELLS][i/CELLS] = 0;
    strcpy(game->score_c, "score: 1");
    game->head_max = 1;
    game->board[12][7] = -1;
    game->head_X = 4;
    game->head_Y = 7;
    game->direction = RIGHT;
    game->prev_direction = RIGHT;
    game->board[game->head_X][game->head_Y] = game->head_max;
    game->state = RUNNING_STATE;

}
