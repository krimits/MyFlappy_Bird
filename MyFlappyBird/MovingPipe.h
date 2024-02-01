#pragma once
#include "Pipe.h"

class MovingPipe : public Pipe {
    float movementSpeed;
    float movementRange;
    bool verticalMovement; // true για κίνηση πάνω-κάτω, false για αριστερά-δεξιά
    float originalPosX;    // Αρχική θέση X
    float originalPosY;    // Αρχική θέση Y

public:
    MovingPipe(GameState& mygame, bool vertical = true, float speed = 0.5f, float range = 50.0f);
    void update() override;
    void draw() override;
    void setMovement(bool vertical, float speed, float range);
};
