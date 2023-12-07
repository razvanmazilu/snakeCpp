 #include"snake.h"
 
void Snake::Draw() {
    for (unsigned i = 0; i < body.size(); i++) {
        float x = body[i].x;
        float y = body[i].y;
        Rectangle segment = {constants::offset + x * constants::cellSize, constants::offset + y * constants::cellSize , static_cast<float>(constants::cellSize), static_cast<float>(constants::cellSize)};
        DrawRectangleRounded(segment, 0.5, 6, constants::darkGreen);

    }
}

void Snake::Update() {

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
void Snake::Reset() {
    body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    direction = {1, 0};
}

