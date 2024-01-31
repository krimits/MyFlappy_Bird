#include "GameState.h"
#include "graphics.h"
#include "config.h"
#include "MovingPipe.h"

void GameState::spawnPipe() {
    if (!pipe) {
        // Εδώ αποφασίζουμε αν θα δημιουργήσουμε ένα στατικό ή κινούμενο εμπόδιο
        if (getDifficulty() > 3) { // Για παράδειγμα, αν η δυσκολία είναι μεγάλη, δημιουργούμε MovingPipe
            pipe = new MovingPipe(*this, true); // Δημιουργία κινούμενου εμποδίου
        } else {
            pipe = new Pipe(*this); // Δημιουργία στατικού εμποδίου
        }
    }
}

void GameState::updateStart()
{
	if (graphics::getKeyState(graphics::SCANCODE_UP))
	{
		status = PLAY;
	}

	player = new Player(*this);

	if (player)
		player->update();

	spawnPipe();

	if (pipe)
		pipe->update();

}

void GameState::updatePlay()
{
	bool withinX = (player->getPosX() > pipe->getPosX() - 13.0f) && (player->getPosX() < pipe->getPosX() + pipe->getWidth() + 13.0f);
	bool withinY = (player->getPosY() < pipe->getTop() + 13.0f) || (player->getPosY() > pipe->getBottom() - 13.0f);
	bool notInFrame = (player->getPosY() <= 15.0f) || player->getPosY() >= CANVAS_HEIGHT - 13.0f;
	bool collision = (withinX && withinY) || notInFrame;

	if (collision)
	{
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "boom.mp3";
		graphics::playSound(br.texture, 0.3, false);

		delete player;
		player = nullptr;
		delete pipe;
		pipe = nullptr;

		if (scoreCounter > highScore)
			highScore = scoreCounter;
		status = END;
	}

	if (withinX)
	{
		withinX_old = withinX;
	}
	if (withinX_old && !withinX)
	{
		scoreCounter++;
        if (scoreCounter % 3 == 0) // Αυξάνουμε τη δυσκολία κάθε φορά που ο παίκτης πετυχαίνει 3 πόντους
		{
            increaseDifficulty();
        }

        // Υπάρχουσα λογική για την αύξηση της ταχύτητας του Pipe
        pipe->speedup(0.05 + getDifficulty() * 0.01);

		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "ok.mp3";
		graphics::playSound(br.texture, 0.3, false);
		withinX_old = false;
	}
	if (player)
		player->update();

	spawnPipe();

	if (pipe)
		pipe->update();
}

void GameState::updateEnd()
{
	if (graphics::getKeyState(graphics::SCANCODE_SPACE))
	{
		scoreCounter = 0;
		withinX_old = false;
		status = START;
	}
}


void GameState::update()
{
	if (status == START)
	{
		updateStart();
	}
	if (status == PLAY)
	{
		updatePlay();
	}
	if (status == END)
	{
		updateEnd();
	}
}
void GameState::drawStart()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "background.png";
	graphics::drawText(40.0f, 80.f, 70.0f, "MyFlappyBird", br);
	graphics::drawText(55.0f, 125.0f, 50.0f, "Press UP to start", br);
	graphics::drawText(55.0f, 500.0f, 50.0f, "Press ESC to exit", br);
	graphics::drawText(80.0f, 570.0f, 40.0f, "Highscore is: " + std::to_string(highScore), br);

	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, CANVAS_WIDTH, CANVAS_WIDTH * 16.0f / 9.0f, br);

	if (pipe)
		pipe->draw();

	if (player)
		player->draw();
}

void GameState::drawPlay()
{
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "background.png";
	std::string s = std::to_string(scoreCounter);
	graphics::drawText(184.0f, 180.0f, 70.0f, s, br);

	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, CANVAS_WIDTH, CANVAS_WIDTH * 16.0f / 9.0f, br);

	if (pipe)
		pipe->draw();

	if (player)
		player->draw();
}
void GameState::drawEnd()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "ending.png";
	graphics::drawText(85.0f, 100.0f, 70.0f, "GAME OVER", br);
	std::string s = std::to_string(scoreCounter);
	graphics::drawText(185.0f, 200.0f, 70.0f, s, br);
	graphics::drawText(80.0f, 530.0f, 40.0f, "Press ESC to exit", br);
	graphics::drawText(5.0f, 480.0f, 45.0f, "Press SPACE to play again", br);
	graphics::drawText(80.0f, 570.0f, 40.0f, "Highscore is: " + std::to_string(highScore), br);

	delete pipe;
	pipe = nullptr;

	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2.0f, CANVAS_HEIGHT / 2.0f, CANVAS_WIDTH, CANVAS_WIDTH * 16.0f / 9.0f, br);

}
void GameState::draw()
{
	graphics::Brush br;
	if (status == START)
	{
		drawStart();
	}
	if (status == PLAY)
	{
		drawPlay();
	}
	if (status == END)
	{
		drawEnd();
	}

}

void GameState::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "Theroar.otf");
}

GameState::GameState()
{
}

GameState::~GameState()
{
	if (player)
	{
		delete player;
	}
}
