#include "clientgame.h"
#include "game.h"
#include "network.h"
#incldue "playfield.h"
#include "player.h"
#include "console.h"


CClientGame::CClientGame()
{
	m_GameType = CLientGame;
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

void CCLientGame::Play()
{
	return CGame::Play();
}

IGame *CreateCLientGame()
{
	return new CClientGame;
}
