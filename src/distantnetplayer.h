#ifndef DISTANTNETPLAYER_DEFINED
#define DISTANTNETPLAYER_DEFINED

#include "player.h"

class IGame;
class INetwork;

class CDistantNetPlayer : public CPlayer
{
	private:
	INetwork *m_pNetwork;
	INetwork *Network() { return m_pNetwork; }

	public:
	CDistantNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
	int Turn(int *pStackNumber, int *pAmount);
} ;

#endif