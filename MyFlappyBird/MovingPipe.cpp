#include "MovingPipe.h"
#include "GameState.h"
#include "util.h"
#include "graphics.h"

MovingPipe::MovingPipe(GameState& mygame, bool vertical, float speed, float range)
    : Pipe(mygame), movementSpeed(speed), movementRange(range), verticalMovement(vertical) {
    originalPosX = pos_x; // Αποθηκεύστε την αρχική θέση
    originalPosY = pos_y; // Αποθηκεύστε την αρχική θέση
}

void MovingPipe::update() {
    Pipe::update(); // Καλεί την update της βάσης κλάσης

    // Προσθήκη λογικής για την κίνηση
    if (verticalMovement) {
        pos_y += movementSpeed;
        if (pos_y > originalPosY + movementRange || pos_y < originalPosY - movementRange) {
            movementSpeed = -movementSpeed; // Αντιστροφή της κίνησης
        }
    } else {
        pos_x += movementSpeed;
        if (pos_x > originalPosX + movementRange || pos_x < originalPosX - movementRange) {
            movementSpeed = -movementSpeed; // Αντιστροφή της κίνησης
        }
    }
}

void MovingPipe::draw() {
    Pipe::draw(); // Καλεί την draw της βάσης κλάσης
    // Επιπλέον λογική εδώ, αν χρειάζεται
}

void MovingPipe::setMovement(bool vertical, float speed, float range) {
    verticalMovement = vertical;
    movementSpeed = speed;
    movementRange = range;
}
