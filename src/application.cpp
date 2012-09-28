#include "application.h"
#include "menu.h"
#include <ncurses.h>

CApplication::CApplication() : m_Running(true)
{
	m_pMenu = CreateMenu();
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::Quit, "Quit"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, LocalGame, "Localgame"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, ServerGame, "Netgame: wait for client to connect"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, ClientGame, "Netgame: connect to server"));
}

CApplication::~CApplication()
{
	delete m_pMenu;
}

void CApplication::Run()
{
	while(m_Running)
	{
		Menu()->Select();
	}
	return;
}

void CApplication::StartGame(GameType GameType)
{
	IGame *pGame;
	switch(GameType)
	{
		case LocalGame:
		pGame = CreateLocalGame();
		break;

		case ServerGame:
		pGame = CreateServerGame();
		break;

		case ClientGame:
		pGame = CreateClientGame();
		break;
		
		default:
		pGame = CreateGame();
		break;
	}
	if(pGame->Init() == 0)
		pGame->Play();
	delete pGame;
	return;
}

void CApplication::Quit()
{
	m_Running = false;
	return;
}
