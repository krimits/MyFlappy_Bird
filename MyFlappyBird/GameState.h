#pragma once

#include "player.h"
#include "Pipe.h"
#include "Movi#pragma once

#include <memory>
#include "Player.h"
#include "Pipe.h"
#include "MovingPipe.h"

// Κλάση GameState για τη διαχείριση της κατάστασης του παιχνιδιού
class GameState {
    typedef enum { START, PLAY, END } status_g; // Καταστάσεις του παιχνιδιού

    std::unique_ptr<Player> player; // Έξυπνος δείκτης για τον παίκτη
    std::unique_ptr<Pipe> pipe; // Έξυπνος δείκτης για το εμπόδιο
    bool withinX;
    bool withinY;
    bool withinX_old;
    bool collision; // Μεταβλητή για τον έλεγχο σύγκρουσης
    int scoreCounter = 0; // Μετρητής σκορ
    int highScore = 0; // Υψηλότερο σκορ
    int difficulty = 1; // Επίπεδο δυσκολίας
    status_g status; // Τρέχουσα κατάσταση του παιχνιδιού

    void spawnPipe(); // Δημιουργία εμποδίου
    bool checkCollision(); // Έλεγχος για σύγκρουση
    void updateStart(); // Ενημέρωση κατάστασης START
    void updatePlay(); // Ενημέρωση κατάστασης PLAY
    void updateEnd(); // Ενημέρωση κατάστασης END
    void drawStart(); // Σχεδίαση κατάστασης START
    void drawPlay(); // Σχεδίαση κατάστασης PLAY
    void drawEnd(); // Σχεδίαση κατάστασης END

public:
    GameState();
    ~GameState();
    void update(); // Ενημέρωση της κατάστασης του παιχνιδιού
    void draw(); // Σχεδίαση του παιχνιδιού
    void init(); // Αρχικοποίηση της κατάστασης του παιχνιδιού
	
    void increaseDifficulty() { difficulty++; } // Αύξηση της δυσκολίας
    int getDifficulty() const { return difficulty; } // Λήψη του επιπέδου δυσκολίας
};
ngPipe.h"

class GameState
{
	typedef enum { START, PLAY, END } status_g;
	Player* player = nullptr;
	Pipe* pipe = nullptr;
	void spawnPipe();
	bool withinX;
	bool withinY;
	bool withinX_old;
	bool collision;
	int scoreCounter = 0;
	int highScore = 0;
	int difficulty = 1;
	status_g status;

	void updateStart();
	void updatePlay();
	void updateEnd();

	void drawStart();
	void drawPlay();
	void drawEnd();


public:
	void update();
	void draw();
	void init();
	void increaseDifficulty() { difficulty++; }
	int getDifficulty() const { return difficulty; }
	GameState();
	~GameState();
};
