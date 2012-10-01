#include "clientgame.h"
#include "game.h"
#include "network.h"
#include "playfield.h"
#include "player.h"
#include "gui.h"


CClientGame::CClientGame(CGui *pGui) : CGame(pGui)
{
	m_pNetwork = CreateClient();
	m_GameType = ClientGame;
}

CClientGame::~CClientGame()
{
	delete m_pNetwork;
}

int CClientGame::Init()
{
		if(m_pNetwork->Init() == -1)
			return -1;
		if(m_pNetwork->Recv(&m_StackNumber, sizeof (int)) <= 0)
			return -1;
		if(m_pNetwork->Recv(&m_MaxAmount, sizeof (int)) <= 0)
			return -1;
		m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
		m_paPlayer[0] = CreateDistantNetPlayer(m_pNetwork, this, m_pInfoWindow, m_pInputWindow);
		m_paPlayer[1] = CreateLocalNetPlayer(m_pNetwork, this, m_pInfoWindow, m_pInputWindow);
		m_Initiated = true;
		return 0;
}

IGame *CreateClientGame(CGui *pGui)
{
	return new CClientGame(pGui);
}
