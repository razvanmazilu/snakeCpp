#include <iostream>
#include <raylib.h>
#include <raymath.h>
#include <deque>

using namespace std;

Color green = {173, 204, 96, 255};
Color darkGreen = {43, 51, 24, 255};

int cellSize = 25;
int cellCount = 20;
int offset = 60;

double lastUpdateTime = 0;

bool operator == (const Vector2 &v1, const Vector2 &v2)
{
   if (v1.x == v2.x && v1.y == v2.y)
      return true;
  return false;
}

Vector2 operator +(const Vector2 &v1, const Vector2 &v2)
{
    Vector2 tmp;
    tmp.x = v1.x + v2.x;
    tmp.y = v1.y + v2.y;
    return tmp;
}
bool ElementInDeque(Vector2 elem, deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (deque[i] == elem) {
            return true;
        }
    }
    return false;
}

double eventTriggered(double interval) {
    double currentTime = GetTime();
    if(currentTime - lastUpdateTime >= interval) {
        lastUpdateTime = currentTime;
        return true;
    }
    return false;
}



class Snake { 
public: 
    deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Draw() {
        for (unsigned i = 0; i < body.size(); i++) {
            float x = body[i].x;
            float y = body[i].y;
            Rectangle segment = {offset + x * cellSize, offset + y * cellSize , static_cast<float>(cellSize), static_cast<float>(cellSize)};
            DrawRectangleRounded(segment, 0.5, 6, darkGreen);

        }
    }

    void Update() {

        //+ operator
        body.push_front(body[0] + direction);
        if(addSegment == true) {
            //eat food
            
            addSegment = false;
        } else { 
            //move
            body.pop_back();
        }
    }
    void Reset() {
        body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
        direction = {1, 0};
    }
};

class Food {
public:
    Vector2 position;
    Texture2D texture;
    Food(deque<Vector2> snakeBody) {
        Image image = LoadImage("Graphics/food.png");
        texture = LoadTextureFromImage(image);
        UnloadImage(image);
        position = GenerateRandomPos(snakeBody);
    }

    ~Food() {
        UnloadTexture(texture);
    }

    void Draw() {
        DrawTexture(texture, offset + position.x * cellSize, offset + position.y * cellSize, WHITE);
    }

    Vector2 GenerateRandomCell() {

        int x = GetRandomValue(0, cellCount - 1);
        int y = GetRandomValue(0, cellCount - 1);
        Vector2 vct;
        vct.x = x;
        vct.y = y;

        return vct;
    }
    Vector2 GenerateRandomPos(deque<Vector2> snakeBody) {
        
        Vector2 position = GenerateRandomCell();

        while(ElementInDeque(position, snakeBody)){
            position = GenerateRandomCell();  
        }
        return position;
    }
};

class Game {

public:
    Snake snake = Snake();
    Food food = Food(snake.body);
    bool running = true;
    int score = 0;
    Sound eatSound;
    Sound wallSound;

    Game() {
        InitAudioDevice();
        eatSound = LoadSound("Sounds/eat.mp3");
        wallSound = LoadSound("Sounds/wall.mp3");
    }
    ~Game() {
        UnloadSound(eatSound);
        UnloadSound(wallSound);
        CloseAudioDevice();
    }


    void Draw() {
        snake.Draw();
        food.Draw();
    }

    void Update() {
        if (running) {

            snake.Update();
            CheckColisionWithFood();
            CheckColisionWithEdges();
            CheckColisionWithTail();
        }
    }

    void CheckColisionWithFood(){
        if (snake.body[0] == food.position) {
            food.position = food.GenerateRandomPos(snake.body);
            snake.addSegment = true;
            score ++;
            PlaySound(eatSound);
        }
    }

    void CheckColisionWithEdges() {
        if(snake.body[0].x == cellCount || snake.body[0].x == -1) {
            GameOver();
        }
        if(snake.body[0].y == cellCount || snake.body[0].y == -1) {
            GameOver();
        }
    }

    void CheckColisionWithTail() {
        Vector2 head = snake.body[0];
        for(unsigned i = 1; i < snake.body.size(); i++) {
            if (head == snake.body[i]) {
                GameOver();
            }
        }
    }

    void GameOver() {
        snake.Reset();
        food.position = food.GenerateRandomPos(snake.body);
        running = false;
        score = 0;
        PlaySound(wallSound);
    }
};
int main () {

    cout << "Starting the game ..." << endl;
    InitWindow(2*offset + cellSize * cellCount, 2 * offset + cellSize*cellCount, "Retro Snake");
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
        ClearBackground(green);
        Rectangle border = {static_cast<float>(offset-5), static_cast<float>(offset-5), static_cast<float>(cellSize*cellCount+10), static_cast<float>(cellSize*cellCount+10)};
        DrawRectangleLinesEx(border, 5, darkGreen);
        DrawText("Retro Snake", offset - 5, 20, 40, darkGreen);
        DrawText(TextFormat("%i", game.score), offset - 5, offset+cellSize*cellCount+10, 40, darkGreen);
        game.Draw();


        EndDrawing();
    }
    CloseWindow();
    return 0;
}