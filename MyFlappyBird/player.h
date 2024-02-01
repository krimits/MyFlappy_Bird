#pragma once
#include "GameObject.h"
#include <string>

// Κλάση Player που κληρονομεί από GameObject και αντιπροσωπεύει τον παίκτη στο παιχνίδι
class Player : public GameObject {
    float pos_x; // Η οριζόντια θέση του παίκτη
    float pos_y; // Η κάθετη θέση του παίκτη
    float gravity; // Η επίδραση της βαρύτητας στον παίκτη
    float lift; // Η δύναμη ανύψωσης όταν ο παίκτης πατάει το πλήκτρο για να ανέβει
    float speed; // Η ταχύτητα κίνησης του παίκτη
    float maxSpeed; // Η μέγιστη ταχύτητα του παίκτη
    float height; // Το ύψος του παίκτη

public:
    // Κατασκευαστής της κλάσης Player
    Player(GameState& gameState);

    // Ενημερώνει την κατάσταση του παίκτη σε κάθε κύκλο του παιχνιδιού
    void update(float dt) override;

    // Σχεδιάζει τον παίκτη στην οθόνη
    void draw() override;

    // Αρχικοποιεί τον παίκτη
    void init() override;

    // Επιτρέπει στον παίκτη να ανέβει όταν πατηθεί το αντίστοιχο πλήκτρο
    void liftUp();
};
