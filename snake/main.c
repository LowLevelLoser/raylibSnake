#include <raylib.h>

#include "game.h"
#include "rendering.h"
#include "logic.h"

int main(){
    
    InitWindow(SCREEN_SIDES, SCREEN_SIDES + SCORE_MARGIN + SCORE_MARGIN, "Snake");
    InitAudioDevice();
    SetTargetFPS(15);
    int frame = 0;

    game_t game = {
        .head_max = 1,
        .head_X = 4,
        .head_Y = 7,
        .board = {{0}},
        .direction = RIGHT,
        .prev_direction = RIGHT,
        .queued_direction = -1,
        .state = RUNNING_STATE,
        .score_c = "score: 1",
        .score_beep = LoadSound("beep-02.mp3"),
        .game_over_beep = LoadSound("beep-03.mp3"),
    };

    game.board[game.head_X][game.head_Y] = game.head_max;
    game.board[12][7] = -1;

    while(!WindowShouldClose()){
        frame++;
        run_game(&game, frame);
        BeginDrawing();
            ClearBackground(RAYWHITE);
            render_game(&game);
        EndDrawing();
    }
    //StopMusicStream(game.music);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}
