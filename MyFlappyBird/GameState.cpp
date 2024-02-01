#include "GameState.h"
#include "graphics.h"
#include "config.h"
#include "MovingPipe.h"


GameState::GameState() : status(START), player(nullptr), pipe(nullptr) {
    // Αρχικοποιήσεις
}

GameState::~GameState() {
    // Χρήση unique_ptr αυτοματοποιεί τη διαχείριση μνήμης
}


void GameState::spawnPipe() {
    // Ελέγχει αν υπάρχει ήδη εμπόδιο στη σκηνή
    if (!pipe) {
        // Δημιουργεί ένα νέο εμπόδιο με βάση το επίπεδο δυσκολίας
        // Για δυσκολία μεγαλύτερη του 3, δημιουργεί ένα κινούμενο εμπόδιο
        if (getDifficulty() > 3) {
            pipe = std::make_unique<MovingPipe>(*this, true);
        } else {
            // Διαφορετικά δημιουργεί ένα στατικό εμπόδιο
            pipe = std::make_unique<Pipe>(*this);
        }
    }
}

void GameState::updateStart() {
    // Ελέγχει αν ο χρήστης πάτησε το πλήκτρο "UP" για να ξεκινήσει το παιχνίδι
    if (graphics::getKeyState(graphics::SCANCODE_UP)) {
        status = PLAY; // Αλλαγή κατάστασης σε PLAY
        player = std::make_unique<Player>(*this); // Δημιουργεί ένα νέο αντικείμενο Player
    }

    // Ενημερώνει τον παίκτη και το εμπόδιο (αν υπάρχουν)
    if (player) {
        player->update();
    }

    spawnPipe();

    if (pipe) {
        pipe->update();
    }
}

// ...
void GameState::updatePlay() {
    // Έλεγχος για σύγκρουση μεταξύ του παίκτη και του εμποδίου
    bool withinX = (player->getPosX() > pipe->getPosX() - 13.0f) && (player->getPosX() < pipe->getPosX() + pipe->getWidth() + 13.0f);
    bool withinY = (player->getPosY() < pipe->getTop() + 13.0f) || (player->getPosY() > pipe->getBottom() - 13.0f);
    bool notInFrame = (player->getPosY() <= 15.0f) || (player->getPosY() >= CANVAS_HEIGHT - 13.0f);
    bool collision = (withinX && withinY) || notInFrame;

    // Ενέργειες σε περίπτωση σύγκρουσης
    if (collision) {
        // Παίξιμο ήχου σύγκρουσης
        graphics::Brush br;
        br.texture = std::string(ASSET_PATH) + "boom.mp3";
        graphics::playSound(br.texture, 0.3, false);

        // Επαναφορά του παίκτη και του εμποδίου
        player.reset();
        pipe.reset();

        // Ενημέρωση του υψηλότερου σκορ
        if (scoreCounter > highScore) {
            highScore = scoreCounter;
        }
        status = END;
    }

    // Ενημέρωση σκορ αν ο παίκτης περάσει το εμπόδιο
    if (withinX) {
        withinX_old = withinX;
    }
    if (withinX_old && !withinX) {
        scoreCounter++;
        if (scoreCounter % 3 == 0) {
            increaseDifficulty();
        }

        // Αύξηση ταχύτητας του εμποδίου
        pipe->speedup(0.05 + getDifficulty() * 0.01);

        // Παίξιμο ήχου επιτυχίας
        graphics::Brush br;
        br.texture = std::string(ASSET_PATH) + "ok.mp3";
        graphics::playSound(br.texture, 0.3, false);
        withinX_old = false;
    }

    // Συνεχής ενημέρωση του παίκτη και του εμποδίου
    if (player) {
        player->update();
    }

    spawnPipe();

    if (pipe) {
        pipe->update();
    }
}

void GameState::updateEnd() {
    // Μετάβαση στην αρχική κατάσταση όταν ο χρήστης πατήσει SPACE
    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        scoreCounter = 0;
        withinX_old = false;
        status = START;
    }
}

void GameState::update() {
    // Ενημέρωση της κατάστασης του παιχνιδιού ανάλογα με την τρέχουσα κατάσταση
    if (status == START) {
        updateStart();
    }
    if (status == PLAY) {
        updatePlay();
    }
    if (status == END) {
        updateEnd();
    }
}

// Οι μέθοδοι drawStart(), drawPlay(), και drawEnd() σχεδιάζουν την κατάσταση του παιχνιδιού
// ανάλογα με την τρέχουσα κατάσταση: Έναρξη, Παιχνίδι, Τέλος
// ...

void GameState::draw() {
    // Επιλογή της κατάλληλης σκηνής για σχεδίαση βάσει της τρέχουσας κατάστασης του παιχνιδιού
    if (status == START) {
        drawStart();
    }
    if (status == PLAY) {
        drawPlay();
    }
    if (status == END) {
        drawEnd();
    }
}

void GameState::init() {
    // Αρχικοποίηση γραφικών και άλλων στοιχείων του παιχνιδιού
    graphics::setFont(std::string(ASSET_PATH) + "Theroar.otf");
}

GameState::GameState() {
    // Κατασκευαστής
}

GameState::~GameState() {
    // Καταστροφέας - η διαχείριση της μνήμης γίνεται αυτόματα λόγω της χρήσης unique_ptr
}
