#include "graphics.h"
#include "GameState.h"
#include "config.h"
#include "util.h"

// Ενημερώνει την κατάσταση του παιχνιδιού σε κάθε κύκλο
void update(float ms) {
    // Ανάκτηση του αντικειμένου GameState από τα δεδομένα του χρήστη
    GameState* game = reinterpret_cast<GameState *>(graphics::getUserData());
    if (game) {
        // Καλεί την ενημερωμένη μέθοδο της κλάσης GameState
        game->update();
    }
}

// Σχεδιάζει το παιχνίδι σε κάθε κύκλο
void draw() {
    // Ανάκτηση του αντικειμένου GameState από τα δεδομένα του χρήστη
    GameState* game = reinterpret_cast<GameState *>(graphics::getUserData());
    if (game) {
        // Καλεί την μέθοδο σχεδίασης της κλάσης GameState
        game->draw();
    }
}

int main() {
    // Δημιουργία αντικειμένου της κλάσης GameState
    GameState mygame;

    // Δημιουργία παραθύρου για το παιχνίδι
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MyFlappyBird");

    // Ρύθμιση του αντικειμένου GameState ως δεδομένα χρήστη
    graphics::setUserData(&mygame);

    // Ορισμός των λειτουργιών σχεδίασης και ενημέρωσης
    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    // Ρύθμιση των διαστάσεων και της κλίμακας του καμβά
    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    // Αρχικοποίηση του παιχνιδιού
    mygame.init();
    // Έναρξη του βρόχου ενημέρωσης και σχεδίασης
    graphics::startMessageLoop();

    return 0;
}
