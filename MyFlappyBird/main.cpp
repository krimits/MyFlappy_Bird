#include "graphics.h"
#include "gamestate.h"
#include "config.h"
#include "util.h"

void update(float ms)
{
	GameState* gameState = reinterpret_cast<GameState*>(graphics::getUserData());
	gameState->update();
}

void draw()
{
	GameState* gameState = reinterpret_cast<GameState*>(graphics::getUserData());
	gameState->draw();
}

int main()
{
	GameState mygame;

	graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "MyFlappyBird");

	graphics::setUserData(&mygame);

	graphics::setDrawFunction(draw);
	graphics::setUpdateFunction(update);

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	mygame.init();
	graphics::startMessageLoop();

	return 0;
}
