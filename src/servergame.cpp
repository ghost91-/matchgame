#include "servergame.h"
#include "game.h"
#include "network.h"
#incldue "playfield.h"
#include "player.h"
#include "console.h"

CServerGame::CServerGame()
{
	m_GameType = ServerGame;
	m_pNetwork = CreateServer();
}

CServerGame::~CServerGame()
{
	delete m_pNetwork;
}

int CServerGame::Init()
{
		CConsole::Print("Number of stacks: ");
		CConsole::GetInteger(&m_StackNumber);
		CConsole::Print("Maximum number of matches takable: ");
		CConsole::GetInteger(&m_MaxAmount);
		if(m_pNetwork->Init() == -1)
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

void CServerGame::Play()
{
	return CGame::Play();
}

IGame *CreateServerGame()
{
	return new CServerGame;
}
