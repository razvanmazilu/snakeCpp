#include"common.h"


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

double eventTriggered(double interval) {
    double currentTime = GetTime();
    if(currentTime - constants::lastUpdateTime >= interval) {
        constants::lastUpdateTime = currentTime;
        return true;
    }
    return false;
}

bool ElementInDeque(Vector2 elem, std::deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (deque[i] == elem) {
            return true;
        }
    }
    return false;
}
void InitConstants() {
    /*
    constants::green = {173, 204, 96, 255};
    constants::darkGreen = {43, 51, 24, 255};

    constants::cellSize = 25;
    constants::cellCount = 20;
    constants::offset = 60;

    constants::lastUpdateTime = 0;
    */

}

    Color constants::green = {173, 204, 96, 255};
    Color constants::darkGreen = {43, 51, 24, 255};

    int constants::cellSize = 25;
    int constants::cellCount = 20;
    int constants::offset = 60;

    double constants::lastUpdateTime = 0;