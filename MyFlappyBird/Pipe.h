#pragma once
#include "GameObject.h"
#include "GameState.h"

class Pipe : public GameObject {
    float pos_x;
    float pos_y;
    float top;
    float bottom;
    float pipe_width;
    float speed;
    float baseSpeed = 1.8f;

public:
    Pipe(GameState& mygame);
    ~Pipe();

    void update() override;
    void draw() override;
    void init() override;
    void speedup(float s);

    float getPosX() const { return pos_x; }
    float getPosY() const { return pos_y; }
    float getTop() const { return top; }
    float getBottom() const { return bottom; }
    float getWidth() const { return pipe_width; }
};
