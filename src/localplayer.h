#ifndef LOCALPLAYER_DEFINED
#define LOCALPLAYER_DEFINED

#include "player.h"

class IGame;

class CLocalPlayer : public CPlayer
{
	public:
	CLocalPlayer(IGame *pGame);
} ;

#endif