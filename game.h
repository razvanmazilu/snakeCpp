#pragma once
#include <raylib.h>
#include <raymath.h>
#include"snake.h"
#include"food.h"
#include"common.h"
class Game {

public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game();
    ~Game();

    void Draw();
    void Update();
    void CheckColisionWithFood();
    void CheckColisionWithEdges(); 
    void CheckColisionWithTail();
    void GameOver(); 
};