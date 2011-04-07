#include "localgame.h"
#include "game.h"

CLocalGame::CLocalGame()
{
	m_GameType = ClientGame;
}

int CLocalGame::Init()
{
	return CGame::Init();
}

void CLocalGame::Play()
{
	return CGame::Play()
}

IGame *CreateLocalGame()
{
	return new CLocalGame;
}