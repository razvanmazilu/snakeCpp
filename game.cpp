#include"game.h"

Game::Game() {
    InitAudioDevice();
    eatSound = LoadSound("Sounds/eat.mp3");
    wallSound = LoadSound("Sounds/wall.mp3");
}

Game::~Game() {
    UnloadSound(eatSound);
    UnloadSound(wallSound);
    CloseAudioDevice();
}

void Game::Draw() {
    snake.Draw();
    food.Draw();
}
void Game::Update() {
    if (running) {

        snake.Update();
        CheckColisionWithFood();
        CheckColisionWithEdges();
        CheckColisionWithTail();
    }
}
void Game::CheckColisionWithEdges() {
    if(snake.body[0].x == constants::cellCount || snake.body[0].x == -1) {
        GameOver();
    }
    if(snake.body[0].y == constants::cellCount || snake.body[0].y == -1) {
        GameOver();
    }
    }
void Game::CheckColisionWithTail() {
    Vector2 head = snake.body[0];
    for(unsigned i = 1; i < snake.body.size(); i++) {
        if (head == snake.body[i]) {
            GameOver();
        }
    }
}

void Game::CheckColisionWithFood(){
    if (snake.body[0] == food.position) {
        food.position = food.GenerateRandomPos(snake.body);
        snake.addSegment = true;
        score ++;
        PlaySound(eatSound);
    }
}

void Game::GameOver() {
    snake.Reset();
    food.position = food.GenerateRandomPos(snake.body);
    running = false;
    score = 0;
    PlaySound(wallSound);
}