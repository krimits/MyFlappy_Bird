#include "Pipe.h"
#include "graphics.h"
#include "config.h"

Pipe::Pipe(GameState& mygame)
    : GameObject(mygame), pos_x(0), pos_y(0), top(0), bottom(0), pipe_width(0), speed(baseSpeed) {
    init();
}

Pipe::~Pipe() {
    // Καθαρισμός και απελευθέρωση πόρων, εάν χρειάζεται
}

void Pipe::update() {
    speed = baseSpeed + m_state.getDifficulty() * 0.1f; // Αύξηση της ταχύτητας ανάλογα με τη δυσκολία

    pos_x -= speed;

    if (pos_x < -pipe_width) {
        init();
    }
}

void Pipe::draw() {
    graphics::Brush br;

    // Σχεδίαση του πρώτου pipe
    br.texture = std::string(ASSET_PATH) + "pipe1.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(pos_x + pipe_width / 2.0f, pos_y, pipe_width, 400.0f, br);

    // Σχεδίαση του δεύτερου pipe
    br.texture = std::string(ASSET_PATH) + "pipe2.png";
    br.outline_opacity = 0.0f;
    graphics::drawRect(pos_x + pipe_width / 2.0f, pos_y + 600.0f, pipe_width, 400.0f, br);
}

void Pipe::init() {
    pos_x = CANVAS_WIDTH;
    pos_y = -100.0f + 200.0f * rand0to1();
    top = 200.0f + pos_y;
    bottom = top + 200.0f;
    pipe_width = CANVAS_HEIGHT / 4.0f;
    speed = baseSpeed; // Χρησιμοποιείται η αρχική ταχύτητα
}

void Pipe::speedup(float s) {
    baseSpeed += s; // Δυναμική αύξηση της ταχύτητας
}
