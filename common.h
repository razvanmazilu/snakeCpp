#pragma once

#include <raylib.h>
#include<deque>

namespace constants {
    extern Color green;
    extern Color darkGreen;
    extern int cellSize;
    extern int cellCount;
    extern int offset;
    extern double lastUpdateTime;
}

void InitConstants();
bool operator == (const Vector2 &v1, const Vector2 &v2);
Vector2 operator +(const Vector2 &v1, const Vector2 &v2);
double eventTriggered(double interval); 
bool ElementInDeque(Vector2 elem, std::deque<Vector2> deque);
