#include "distantnetplayer.h"
#include "player.h"
#include "game.h"
#include "network.h"
#include "gui.h"

CDistantNetPlayer::CDistantNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow) : CPlayer(pGame, pInfoWindow, pInputWindow)
{
	m_pNetwork = pNetwork;
	m_PlayerType = DistantNetPlayer;
}

int CDistantNetPlayer::Turn(int *pStackNumber, int *pAmount)
{
	if((Network()->Recv(pStackNumber, sizeof (int)) <= 0) || (Network()->Recv(pAmount, sizeof (int)) <= 0))
		return -1;
	else
		return 0;
}

IPlayer *CreateDistantNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow)
{
	return new CDistantNetPlayer(pNetwork, pGame, pInfoWindow, pInputWindow);
}