#pragma once

#include "util.h"
#include "gamestate.h"


// Η βασική κλάση για όλα τα αντικείμενα του παιχνιδιού
class GameObject {
    static int m_next_id; // Στατική μεταβλητή για την ανάθεση μοναδικού ID σε κάθε αντικείμενο

protected:
    GameState& m_state; // Αναφορά στο GameState για πρόσβαση σε κοινές πληροφορίες
    std::string m_name; // Όνομα του αντικειμένου
    int m_id;           // Μοναδικό ID του αντικειμένου
    bool m_active;      // Κατάσταση ενεργοποίησης του αντικειμένου

public:
    GameObject(GameState& gs, const std::string& name = "");
    virtual ~GameObject();

    virtual void update(float dt) {}
    virtual void init() {}
    virtual void draw() {}

    bool isActive() const;
    void setActive(bool active);

    // Κατασκευαστής που δέχεται δείκτη GameState
    GameObject(GameState* gs, const std::string& name);
};

#endif // GAMEOBJECT_H
