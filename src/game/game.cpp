#include "game.h"
#include "player.h"
#include "playfield.h"
#include "../engine/console.h"
#include "visualisation.h"

void CGame::Play()
{
	int StackNumber, Amount;
	CConsole::Print("You may take up to %d matches from one stack each turn!\n", m_MaxAmount);
	Visualisation()->ShowField(Field());
	int i = 1;

	while(1)
	{
		StackNumber = 0;
		Amount = 0;
		i = i==1 ? 0 : 1;
		CConsole::Print("Player %d's turn\n", i+1);
		while(!ValidTurn(StackNumber, Amount))
		{
			if(Player()[i]->Turn(&StackNumber, &Amount) == -1)
				return;
		}
		Field()->RemoveMatches(StackNumber, Amount);
		Visualisation()->ShowField(Field());
		if (!(Field()->MatchExist()))
		{
			CConsole::Print("Player %d won!\n", i = i==1 ? 1 : 2);
			return;
		}
	}
}

bool CGame::AllowedToTakeMatches(int Amount)
{
	if ((Amount > m_MaxAmount) || (Amount < 1))
		return false;
	else
		return true;
}

bool CGame::ValidTurn(int StackNumber, int Amount)
{
	return (AllowedToTakeMatches(Amount) && Field()->CanTakeMatches(StackNumber, Amount));
}

CGame::CGame()
{
	m_Initiated = false;
	m_pVisualisation = CreateVisualisation();
	m_GameType = Unknown;
}

CGame::~CGame()
{
	delete m_pVisualisation;
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
}

int CGame::Init()
{
		CConsole::Print("Number of stacks: ");
		CConsole::GetInteger(&m_StackNumber);
		CConsole::Print("Maximum number of matches takable: ");
		CConsole::GetInteger(&m_MaxAmount);
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = new CLocalPlayer(this);
		m_paPlayer[1] = new CLocalPlayer(this);
		m_Initiated = true;
		return 0;
}

IGame *CreateGame()
{
	return new CGame;
}



