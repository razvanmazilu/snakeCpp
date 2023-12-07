#include <iostream>
#include"game.h"
#include"snake.h"
#include"food.h"
#include"common.h"

int main () {

    std::cout << "Starting the game ..." << std::endl;
    InitConstants();
    InitWindow(2*constants::offset + constants::cellSize * constants::cellCount, \
        2 * constants::offset + constants::cellSize * constants::cellCount, "Retro Snake");
    SetTargetFPS(60);

    Game game = Game();

    while(WindowShouldClose() == false){

        BeginDrawing();
       
        if(eventTriggered(0.2)){
            game.Update();
        }

        if(IsKeyPressed(KEY_UP) && game.snake.direction.y != 1) {
            game.snake.direction = {0, -1};
            game.running = true;
        }

        if(IsKeyPressed(KEY_DOWN) && game.snake.direction.y != -1) {
            game.snake.direction = {0, 1};
            game.running = true;
        }

        if(IsKeyPressed(KEY_LEFT) && game.snake.direction.x != 1) {
            game.snake.direction = {-1, 0};
            game.running = true;
        }

        if(IsKeyPressed(KEY_RIGHT) && game.snake.direction.x != -1) {
            game.snake.direction = {1, 0};
            game.running = true;
        }

        //Drawing
        ClearBackground(constants::green);
        Rectangle border = {static_cast<float>(constants::offset-5), static_cast<float>(constants::offset-5), \
            static_cast<float>(constants::cellSize * constants::cellCount+10), \
            static_cast<float>(constants::cellSize * constants::cellCount+10)};
        DrawRectangleLinesEx(border, 5, constants::darkGreen);
        DrawText("Retro Snake", constants::offset - 5, 20, 40, constants::darkGreen);
        DrawText(TextFormat("%i", game.score), constants::offset - 5, \
            constants::offset+constants::cellSize*constants::cellCount+10, 40, constants::darkGreen);
        game.Draw();


        EndDrawing();
    }
    CloseWindow();
    return 0;
}