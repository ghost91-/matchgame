#include "localgame.h"
#include "game.h"

CLocalGame::CLocalGame()
{
	m_GameType = ClientGame;
}

IGame *CreateLocalGame()
{
	return new CLocalGame;
}
