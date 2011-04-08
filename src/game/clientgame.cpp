#include "clientgame.h"
#include "game.h"
#include "../engine/network.h"
#include "playfield.h"
#include "player.h"
#include "../engine/console.h"


CClientGame::CClientGame()
{
	m_GameType = ClientGame;
	m_pNetwork = CreateClient();
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
		m_paPlayer[0] = new CDistantNetPlayer(m_pNetwork, this);
		m_paPlayer[1] = new CLocalNetPlayer(m_pNetwork, this);
		m_Initiated = true;
		return 0;
}

IGame *CreateClientGame()
{
	return new CClientGame;
}
