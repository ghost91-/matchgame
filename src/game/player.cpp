#include "player.h"
#include "../engine/network.h"
#include "game.h"
#include "../engine/console.h"
#include "playfield.h"

CLocalPlayer::CLocalPlayer(IGame *pGame)
{
	m_pGame = pGame;
	m_PlayerType = LocalPlayer;
}

int CLocalPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	return 0;
}

CLocalNetPlayer::CLocalNetPlayer(INetwork *pNetwork, IGame *pGame)
{
	m_pGame = pGame;
	m_pNetwork = pNetwork;
	m_PlayerType = LocalNetPlayer;
}

int CLocalNetPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	if((Network()->Send(pStackNumber, sizeof (int)) == -1) || (Network()->Send(pAmount, sizeof (int)) == -1))
		return -1;
	else
		return 0;
}

CDistantNetPlayer::CDistantNetPlayer(INetwork *pNetwork, IGame *pGame)
{
	m_pGame = pGame;
	m_pNetwork = pNetwork;
	m_PlayerType = DistantNetPlayer;
}

int CDistantNetPlayer::DoTurn(int *pStackNumber, int *pAmount)
{
	if((Network()->Recv(pStackNumber, sizeof (int)) <= 0) || (Network()->Recv(pAmount, sizeof (int)) <= 0))
		return -1;
	else
		return 0;
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

