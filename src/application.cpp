#include "application.h"
#include "menu.h"
#include "gui.h"

CApplication::CApplication() : m_Running(true)
{
	m_pGui = CreateGui();
	m_pMenu = CreateMenu(m_pGui);
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::Quit, "Quit"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, LocalGame, "Localgame"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, ServerGame, "Netgame: wait for client to connect"));
	Menu()->AddEntry(CreateMenuEntry(this, &CApplication::StartGame, ClientGame, "Netgame: connect to server"));
}

CApplication::~CApplication()
{
	delete m_pMenu;
	delete m_pGui;
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
		pGame = CreateLocalGame(m_pGui);
		break;

		case ServerGame:
		pGame = CreateServerGame(m_pGui);
		break;

		case ClientGame:
		pGame = CreateClientGame(m_pGui);
		break;
		
		default:
		pGame = CreateGame(m_pGui);
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
