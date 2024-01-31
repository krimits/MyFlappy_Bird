#include "player.h"
#include "graphics.h"
#include "GameState.h"

Player::Player(GameState& gameState)
    : GameObject(gameState), pos_x(120.0f), pos_y(CANVAS_HEIGHT / 2.0f), gravity(0.5f), lift(-1.3f), speed(0.0f) {
    // Πρόσθετες αρχικοποιήσεις εδώ, αν χρειάζονται
}

void Player::update() {
    if (graphics::getKeyState(graphics::SCANCODE_UP)) {
        liftUp(); // Αντίδραση στο πάτημα του κουμπιού - ταχύτερη αντίδραση
    }

    // Προσαρμογή της βαρύτητας ή άλλων παραμέτρων ανάλογα με τη δυσκολία
    float difficultyModifier = 1.0 + m_state.getDifficulty() * 0.05;
    speed += gravity * difficultyModifier;
    pos_y += speed;

    // Έλεγχος για τα όρια της οθόνης και αποφυγή συγκρούσεων
    if (pos_y > CANVAS_HEIGHT) {
        pos_y = CANVAS_HEIGHT;
        speed = 0.0f;
    }

    if (pos_y <  0.0f) {
        pos_y = 0.0f;
        speed = 0.0f;
    }
}

void Player::draw() {
    graphics::Brush br;

    if (speed >= 0)
        br.texture = std::string(ASSET_PATH) + "birdup.png";
    else
        br.texture = std::string(ASSET_PATH) + "bird.png";

    br.outline_opacity = 0.0f;

    graphics::drawRect(pos_x, pos_y, 50.0f, 50.0f, br);
    graphics::resetPose();
}

void Player::init() {
    // Αρχικοποίηση του παίκτη, αν χρειάζεται
}

void Player::liftUp() {
    speed += lift;
}
