#include "gameobject.h"
#include "gamestate.h"

int GameObject::m_next_id = 0;

GameObject::GameObject(GameState& gs, const std::string& name)
    : m_state(gs), m_name(name), m_id(m_next_id++), m_active(true) {
    // Αρχικοποίηση του αντικειμένου
}

GameObject::GameObject(GameState* gs, const std::string& name)
    : m_state(*gs), m_name(name), m_id(m_next_id++), m_active(true) {
    // Αρχικοποίηση του αντικειμένου με δείκτη GameState
    // Εξασφαλίστε ότι το gs δεν είναι nullptr πριν το ακολουθήσετε
}

GameObject::~GameObject() {
    // Καταστροφέας - καθαρισμός πόρων, εάν χρειάζεται
}

bool GameObject::isActive() const {
    return m_active;
}

void GameObject::setActive(bool active) {
    m_active = active;
}

// Υπόλοιπες μέθοδοι και λογική
