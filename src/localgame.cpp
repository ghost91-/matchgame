#include "localgame.h"
#include "game.h"

CLocalGame::CLocalGame(CGui *pGui) : CGame(pGui)
{
	m_GameType = ClientGame;
}

IGame *CreateLocalGame(CGui *pGui)
{
	return new CLocalGame(pGui);
}
