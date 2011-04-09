#include "distantnetplayer.h"
#include "player.h"
#include "game.h"
#include "network.h"

CDistantNetPlayer::CDistantNetPlayer(INetwork *pNetwork, IGame *pGame):CPlayer(pGame)
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

IPlayer *CreateDistantNetPlayer(INetwork *pNetwork, IGame *pGame)
{
	return new CDistantNetPlayer(pNetwork, pGame);
}