#include"food.h"
Vector2 Food::GenerateRandomCell() {

    int x = GetRandomValue(0, constants::cellCount - 1);
    int y = GetRandomValue(0, constants::cellCount - 1);
    Vector2 vct;
    vct.x = x;
    vct.y = y;

    return vct;
}

Food::Food(std::deque<Vector2> snakeBody) {
    Image image = LoadImage("Graphics/food.png");
    texture = LoadTextureFromImage(image);
    UnloadImage(image);
    position = GenerateRandomPos(snakeBody);
}

Food::~Food() {
    UnloadTexture(texture);
}

void Food::Draw() {
    DrawTexture(texture, constants::offset + position.x * constants::cellSize, constants::offset + position.y * constants::cellSize, WHITE);
}

Vector2 Food::GenerateRandomPos(std::deque<Vector2> snakeBody) {
    
    Vector2 position = GenerateRandomCell();

    while(ElementInDeque(position, snakeBody)){
        position = GenerateRandomCell();  
    }
    return position;
}

