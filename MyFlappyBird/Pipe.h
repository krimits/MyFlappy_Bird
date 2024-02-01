#pragma once
#include "GameObject.h"
#include "GameState.h"

// Η κλάση Pipe αντιπροσωπεύει τα στατικά εμπόδια στο παιχνίδι
class Pipe : public GameObject {
    float pos_x; // Η οριζόντια θέση του εμποδίου
    float pos_y; // Η κάθετη θέση του εμποδίου
    float top; // Το ανώτερο σημείο του εμποδίου
    float bottom; // Το κατώτερο σημείο του εμποδίου
    float pipe_width; // Το πλάτος του εμποδίου
    float speed; // Η ταχύτητα κίνησης του εμποδίου
    float baseSpeed = 1.8f; // Η βασική ταχύτητα του εμποδίου

public:
    Pipe(GameState& mygame); // Κατασκευαστής
    ~Pipe(); // Καταστροφέας

    void update() override; // Ενημερώνει τη θέση του εμποδίου
    void draw() override; // Σχεδιάζει το εμπόδιο
    void init() override; // Αρχικοποιεί το εμπόδιο
    void speedup(float s); // Αυξάνει την ταχύτητα του εμποδίου

    // Getters για την ανάκτηση πληροφοριών του εμποδίου
    float getPosX() const { return pos_x; }
    float getPosY() const { return pos_y; }
    float getTop() const { return top; }
    float getBottom() const { return bottom; }
    float getWidth() const { return pipe_width; }
};
