#include "player.h"
#include "game.h"
#include "console.h"
#include "playfield.h"

CPlayer::CPlayer(IGame *pGame)
{
	m_PlayerType = Unknown;
	m_pGame = pGame;
}

void CPlayer::TurnInput(int *pStackNumber, int *pAmount)
{
	CConsole::Print("Enter from which stack, and how how many matches you want to take!\n");
	CConsole::Print("Stack: ");
	CConsole::GetInteger(pStackNumber);
	CConsole::Print("Number of matches: ");
	CConsole::GetInteger(pAmount);
	return;
}

int CPlayer::Turn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	return 0;
}

IPlayer *CreatePlayer(IGame *pGame)
{
	return new CPlayer(pGame);
}
