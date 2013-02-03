#ifndef LOCALPLAYER_DEFINED
#define LOCALPLAYER_DEFINED

#include "player.h"

class IGame;
class CWindow;

class CLocalPlayer : public CPlayer
{
	public:
	CLocalPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
} ;

#endif