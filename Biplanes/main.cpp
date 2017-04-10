#include "Game/Game.h"
#include "Game/GameProcessState.h"

int main()
{
	Game game;

	game.pushState(new GameProcessState(&game));
	game.gameLoop();

	return 0;
}