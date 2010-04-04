#include "game.h"
#include "net.h"
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
			if(!Player()[i]->Turn(&StackNumber, &Amount))
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
	delete m_pVisualisation;
	m_Initiated = false;
	m_pNet = CreateNet();;
	m_pVisualisation = CreateVisualisation();
}

CServerGame::~CServerGame()
{
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
	delete m_pNet;
}

int CServerGame::DoInit()
{
		int Error;
		bool Error2;
		CConsole::Print("Number of stacks: ");
		CConsole::GetInteger(&m_StackNumber);
		CConsole::Print("Maximum number of matches takable: ");
		CConsole::GetInteger(&m_MaxAmount);
		Error = m_pNet->Startup();
		if(Error == -1)
			return -1;
		Error2 = m_pNet->SendNumber(&m_StackNumber);
		if(Error2 == false)
			return -1;
		Error2 = m_pNet->SendNumber(&m_MaxAmount);
		if(Error2 == false)
			return -1;
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = new CLocalNetPlayer(m_pNet, this);
		m_paPlayer[1] = new CDistantNetPlayer(m_pNet, this);
		m_Initiated = true;
		return 0;
}

CClientGame::CClientGame()
{
	delete m_pVisualisation;
	m_Initiated = false;
	m_pNet = CreateNet();
	m_pVisualisation = CreateVisualisation();
}

CClientGame::~CClientGame()
{
	if(m_Initiated)
	{
		delete m_paPlayer[0];
		delete m_paPlayer[1];
		delete m_pField;
	}
	delete m_pNet;
}

int CClientGame::DoInit()
{
		int Error;
		bool Error2;
		char aIpString[100];
		CConsole::Print("Serveraddress: ");
		CConsole::GetString(aIpString);
		Error = m_pNet->Startup(aIpString);
		if(Error == -1)
			return -1;
		Error2 = m_pNet->RecieveNumber(&m_StackNumber);
		if(Error2 == false)
			return -1;
		Error2 = m_pNet->RecieveNumber(&m_MaxAmount);
		if(Error2 == false)
			return -1;
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = new CDistantNetPlayer(m_pNet, this);
		m_paPlayer[1] = new CLocalNetPlayer(m_pNet, this);
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


