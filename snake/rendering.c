#include <raylib.h>

#include "game.h"
#include "rendering.h"

void render_running_game(const game_t *game);
void render_game_over(const game_t *game);
void render_win(const game_t *game);


void render_game(const game_t *game){
    DrawText(game->score_c, 0, 0, 30, BLACK);
    switch(game->state){
        case RUNNING_STATE:
            render_running_game(game);
            break;
        case GAME_OVER_STATE:
            render_game_over(game);
            break;
    }
}

void render_running_game(const game_t *game){
    for(int i = 0; i < CELLS; i++){
        for(int j = 0; j < CELLS; j++){
            if(game->board[i][j] > 0)
                DrawRectangle(i*CELL_SIZE, j*CELL_SIZE+SCORE_MARGIN, CELL_SIZE, CELL_SIZE, GREEN);
            else if(game->board[i][j] < 0)
                DrawRectangle(i*CELL_SIZE, j*CELL_SIZE+SCORE_MARGIN, CELL_SIZE, CELL_SIZE, RED);
        }
    }
}

void render_game_over(const game_t *game){
    for(int i = 0; i < CELLS; i++){
        for(int j = 0; j < CELLS; j++){
            if(game->board[i][j] > 0)
                DrawRectangle(i*CELL_SIZE, j*CELL_SIZE+SCORE_MARGIN, CELL_SIZE, CELL_SIZE, RED);
        }
    }
}

void render_win(const game_t *game){
    DrawRectangle(0, SCORE_MARGIN, SCREEN_SIDES, SCREEN_SIDES, GREEN);
    DrawText("YOU WIN", 400, 0, 30, GREEN);
}
