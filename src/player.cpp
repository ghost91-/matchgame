#include "player.h"
#include "net.h"
#include "game.h"
#include "console.h"
#include "playfield.h"

CLocalPlayer::CLocalPlayer(IGame *pGame)
{
	m_pGame = pGame;
	m_PlayerType = LocalPlayer;
}

bool CLocalPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	return true;
}

CLocalNetPlayer::CLocalNetPlayer(CNet *pNet, IGame *pGame)
{
	m_pGame = pGame;
	m_pNet = pNet;
	m_PlayerType = LocalNetPlayer;
}

bool CLocalNetPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	return (Net()->Send(pStackNumber, sizeof (int)) && Net()->Send(pAmount, sizeof (int)));
}

CDistantNetPlayer::CDistantNetPlayer(CNet *pNet, IGame *pGame)
{
	m_pGame = pGame;
	m_pNet = pNet;
	m_PlayerType = DistantNetPlayer;
}

bool CDistantNetPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	return (Net()->Recv(pStackNumber, sizeof (int)) && Net()->Recv(pAmount, sizeof (int)));
}

void IPlayer::TurnInput(int *pStackNumber, int *pAmount)
{
	CConsole::Print("Enter from which stack, and how how many matches you want to take!\n");
	CConsole::Print("Stack: ");
	CConsole::GetInteger(pStackNumber);
	CConsole::Print("Number of matches: ");
	CConsole::GetInteger(pAmount);
	return;
}

