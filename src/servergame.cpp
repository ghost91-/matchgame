#include "servergame.h"
#include "game.h"
#include "network.h"
#include "playfield.h"
#include "player.h"
#include "gui.h"

CServerGame::CServerGame(CGui *pGui) : CGame(pGui)
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
	if(m_pNetwork->Init() == -1)
		return -1;
	if(m_pNetwork->Send(&m_StackNumber, sizeof (int)) == -1)
		return -1;
	if(m_pNetwork->Send(&m_MaxAmount, sizeof (int)) == -1)
		return -1;
	m_pField = CreatePlayfield(m_StackNumber, m_MaxAmount);
	m_paPlayer[0] = CreateLocalNetPlayer(m_pNetwork, this, m_pInfoWindow, m_pInputWindow);
	m_paPlayer[1] = CreateDistantNetPlayer(m_pNetwork, this, m_pInfoWindow, m_pInputWindow);
	m_Initiated = true;
	return 0;
}

IGame *CreateServerGame(CGui *pGui)
{
	return new CServerGame(pGui);
}
