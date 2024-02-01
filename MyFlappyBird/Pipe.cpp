#include "Pipe.h"
#include "graphics.h"
#include "config.h"

// Κατασκευαστής της κλάσης Pipe
Pipe::Pipe(GameState& mygame)
    : GameObject(mygame), pos_x(0), pos_y(0), top(0), bottom(0), pipe_width(0), speed(baseSpeed) {
    // Καλεί τη μέθοδο init για να αρχικοποιήσει το εμπόδιο
    init();
}

// Καταστροφέας της κλάσης Pipe
Pipe::~Pipe() {
    // Καθαρισμός και απελευθέρωση πόρων, εάν χρειάζεται
    // Σημείωση: Σε αυτήν την περίπτωση, δεν είναι απαραίτητος λόγω της χρήσης smart pointers
}

// Ενημέρωση της κατάστασης του Pipe σε κάθε κύκλο του παιχνιδιού
void Pipe::update() {
    // Αυξάνει την ταχύτητα του εμποδίου ανάλογα με τη δυσκολία του παιχνιδιού
    speed = baseSpeed + m_state.getDifficulty() * 0.1f;

    // Μετακινεί το εμπόδιο προς τα αριστερά
    pos_x -= speed;

    // Επαναφέρει τη θέση του εμποδίου όταν φτάσει στο αριστερό άκρο της οθόνης
    if (pos_x < -pipe_width) {
        init();
    }
}

// Σχεδιάζει το εμπόδιο στην οθόνη
void Pipe::draw() {
    graphics::Brush br;

    // Σχεδιάζει το πρώτο μέρος του εμποδίου
    br.texture = std::string(ASSET_PATH) + "pipe1.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(pos_x + pipe_width / 2.0f, pos_y, pipe_width, 400.0f, br);

    // Σχεδιάζει το δεύτερο μέρος του εμποδίου
    br.texture = std::string(ASSET_PATH) + "pipe2.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(pos_x + pipe_width / 2.0f, pos_y + 600.0f, pipe_width, 400.0f, br);
}

// Αρχικοποιεί τη θέση και τις διαστάσεις του εμποδίου
void Pipe::init() {
    // Τοποθετεί το εμπόδιο στη δεξιά άκρη της οθόνης
    pos_x = CANVAS_WIDTH;
    // Ρυθμίζει τυχαία την κάθετη θέση του εμποδίου
    pos_y = -100.0f + 200.0f * rand0to1();
    top = 200.0f + pos_y;
    bottom = top + 200.0f;
    pipe_width = CANVAS_HEIGHT / 4.0f;
    // Ρυθμίζει την αρχική ταχύτητα του εμποδίου
    speed = baseSpeed;
}

// Αυξάνει την ταχύτητα του εμποδίου
void Pipe::speedup(float s) {
    baseSpeed += s;
}
