#pragma once
#include <raylib.h>
#include <raymath.h>
#include <deque>
#include "common.h"

class Snake { 
public: 
    std::deque<Vector2> body = {Vector2{6,9}, Vector2{5,9}, Vector2{4,9}};
    Vector2 direction = {1, 0};
    bool addSegment = false;

    void Reset();
    void Update();
    void Draw(); 
};