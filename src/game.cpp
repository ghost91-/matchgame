#include "game.h"
#include "network.h"
#include "player.h"
#include "playfield.h"
#include "console.h"
#include "visualisation.h"

void IGame::Play()
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

bool IGame::AllowedToTakeMatches(int Amount)
{
	if ((Amount > m_MaxAmount) || (Amount < 1))
		return false;
	else
		return true;
}

bool IGame::ValidTurn(int StackNumber, int Amount)
{
	return (AllowedToTakeMatches(Amount) && Field()->CanTakeMatches(StackNumber, Amount));
}

CLocalGame::CLocalGame()
{
	m_Initiated = false;
	m_pVisualisation = CreateVisualisation();
}

CLocalGame::~CLocalGame()
{
	delete m_pVisualisation;
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
}

int CLocalGame::DoInit()
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

CServerGame::CServerGame()
{
	m_Initiated = false;
	m_pNetwork = CreateServer();
	m_pVisualisation = CreateVisualisation();
}

CServerGame::~CServerGame()
{
	delete m_pVisualisation;
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
	delete m_pNetwork;
}

int CServerGame::DoInit()
{
		CConsole::Print("Number of stacks: ");
		CConsole::GetInteger(&m_StackNumber);
		CConsole::Print("Maximum number of matches takable: ");
		CConsole::GetInteger(&m_MaxAmount);
		if(m_pNetwork->Init() == -1)
			return -1;
		if(m_pNetwork->Startup() == -1)
			return -1;
		if(m_pNetwork->Send(&m_StackNumber, sizeof (int)) == -1)
			return -1;
		if(m_pNetwork->Send(&m_MaxAmount, sizeof (int)) == -1)
			return -1;
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = new CLocalNetPlayer(m_pNetwork, this);
		m_paPlayer[1] = new CDistantNetPlayer(m_pNetwork, this);
		m_Initiated = true;
		return 0;
}

CClientGame::CClientGame()
{
	m_Initiated = false;
	m_pNetwork = CreateClient();
	m_pVisualisation = CreateVisualisation();
}

CClientGame::~CClientGame()
{
	delete m_pVisualisation;
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
	delete m_pNetwork;
}

int CClientGame::DoInit()
{
		char aIp[100];
		CConsole::Print("Serveraddress: ");
		CConsole::GetString(aIp);
		if(m_pNetwork->Init() == -1)
			return -1;
		if(m_pNetwork->Connect(aIp) == -1)
			return -1;
		if(m_pNetwork->Startup() == -1)
			return -1;
		if(m_pNetwork->Recv(&m_StackNumber, sizeof (int)) <= 0)
			return -1;
		if(m_pNetwork->Recv(&m_MaxAmount, sizeof (int)) <= 0)
			return -1;
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = new CDistantNetPlayer(m_pNetwork, this);
		m_paPlayer[1] = new CLocalNetPlayer(m_pNetwork, this);
		m_Initiated = true;
		return 0;
}

IGame *CreateGame(GameType GameType)
{
	switch(GameType)
	{
		case LocalGame:
		return new CLocalGame;
		break;

		case ClientGame:
		return new CClientGame;
		break;

		default:
		return new CServerGame;
		break;
	}
}



