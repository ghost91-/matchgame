#include "player.h"
#include "game.h"
#include "gui.h"
#include "playfield.h"

CPlayer::CPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow) : m_PlayerType(Unknown), m_pGame(pGame), m_pInfoWindow(pInfoWindow), m_pInputWindow(pInputWindow)
{
}

void CPlayer::TurnInput(int *pStackNumber, int *pAmount)
{
	m_pInfoWindow->Clear();
	m_pInfoWindow->MovePrint(0, 0, "Enter from which stack you want to take matches!");
	m_pInfoWindow->Update();
	m_pInputWindow->Move(0, 0);
	*pStackNumber = m_pInputWindow->GetInt();
	m_pInputWindow->Clear();
	m_pInputWindow->Update();
	m_pInfoWindow->Clear();
	m_pInfoWindow->MovePrint(0, 0, "Enter how many matches you want to take!");
	m_pInfoWindow->Update();
	m_pInputWindow->Move(0, 0);
	*pAmount = m_pInputWindow->GetInt();
	m_pInputWindow->Clear();
	m_pInputWindow->Update();
	return;
}

int CPlayer::Turn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	return 0;
}

IPlayer *CreatePlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow)
{
	return new CPlayer(pGame, pInfoWindow, pInputWindow);
}
