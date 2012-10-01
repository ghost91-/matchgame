#include "localnetplayer.h"
#include "player.h"
#include "game.h"
#include "network.h"

CLocalNetPlayer::CLocalNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow) : CPlayer(pGame, pInfoWindow, pInputWindow), m_pNetwork(pNetwork)
{
	m_PlayerType = LocalNetPlayer;
}

int CLocalNetPlayer::Turn(int *pStackNumber, int *pAmount)
{
	TurnInput(pStackNumber, pAmount);
	if((Network()->Send(pStackNumber, sizeof (int)) == -1) || (Network()->Send(pAmount, sizeof (int)) == -1))
		return -1;
	else
		return 0;
}

IPlayer *CreateLocalNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow)
{
	return new CLocalNetPlayer(pNetwork, pGame, pInfoWindow, pInputWindow);
}
