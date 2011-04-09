#ifndef LOCALNETPLAYER_DEFINED
#define LOCALNETPLAYER_DEFINED

#include "player.h"

class IGame;
class INetwork;

class CLocalNetPlayer : public CPlayer
{
	private:
	INetwork *m_pNetwork;
	INetwork *Network() { return m_pNetwork; }

	public:
	int Turn(int *pStackNumber, int *pAmount);
	CLocalNetPlayer(INetwork *pNetwork, IGame *pGame);
} ;

#endif