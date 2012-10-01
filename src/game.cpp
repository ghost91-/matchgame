#include "game.h"
#include "player.h"
#include "playfield.h"
#include "console.h"
#include "visualisation.h"
#include "gui.h"

void CGame::Play()
{
	int StackNumber, Amount;
	m_pInfoWindow->Clear();
	m_pInfoWindow->MovePrint(0, 0, "You may take up to %d matches from one stack each turn!\n", m_MaxAmount);
	m_pInfoWindow->Update();
	Visualisation()->ShowField(Field());
	int i = 1;

	while(1)
	{
		StackNumber = 0;
		Amount = 0;
		i = i==1 ? 0 : 1;
		m_pInfoWindow->Clear();
		m_pInfoWindow->MovePrint(0, 0,"Player %d's turn\n", i+1);
		m_pInfoWindow->Update();
		while(!ValidTurn(StackNumber, Amount))
		{
			if(Player()[i]->Turn(&StackNumber, &Amount) == -1)
				return;
		}
		Field()->RemoveMatches(StackNumber, Amount);
		Visualisation()->ShowField(Field());
		if (!(Field()->MatchExist()))
		{
			m_pInfoWindow->Clear();
			m_pInfoWindow->MovePrint(0, 0, "Player %d won!\n", i = i==1 ? 1 : 2);
			m_pGameWindow->Clear();
			m_pGameWindow->Update();
			m_pInfoWindow->Update();
			m_pInputWindow->Move(0, 0);
			m_pInputWindow->GetCh();
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

CGame::CGame(CGui *pGui) : m_Initiated(false), m_pGui(pGui), m_GameType(Notknown)
{
	m_pGui->Clear();
	m_pInfoWindow = m_pGui->CreateWindow(3, m_pGui->GetMaxX(), 0, 0);
	m_pGameWindow = m_pGui->CreateWindow(m_pGui->GetMaxY() - 4, m_pGui->GetMaxX(), 4, 0);
	m_pInputWindow = m_pGui->CreateWindow(1, m_pGui->GetMaxX(), m_pGui->GetMaxY() - 1, 0);
	m_pVisualisation = CreateVisualisation(m_pGameWindow);
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
	m_pInfoWindow->Clear();
	m_pInfoWindow->MovePrint(0, 0, "Please enter the number of stacks!");
	m_pInfoWindow->Update();
	m_pInputWindow->Move(0, 0);
	m_StackNumber = m_pInputWindow->GetInt();
	m_pInputWindow->Clear();
	m_pInputWindow->Update();
	m_pInfoWindow->Clear();
	m_pInfoWindow->MovePrint(0, 0, "Please enter the maximum number of matches one is allowed to take!");
	m_pInfoWindow->Update();
	m_pInputWindow->Move(0, 0);
	m_MaxAmount = m_pInputWindow->GetInt();
	m_pInputWindow->Clear();
	m_pInputWindow->Update();
	m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
	m_paPlayer[0] = CreateLocalPlayer(this, m_pInfoWindow, m_pInputWindow);
	m_paPlayer[1] = CreateLocalPlayer(this, m_pInfoWindow, m_pInputWindow);
	m_Initiated = true;
	return 0;
}

IGame *CreateGame(CGui *pGui)
{
	return new CGame(pGui);
}



