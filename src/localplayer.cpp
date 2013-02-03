#include "localplayer.h"
#include "player.h"
#include "game.h"

CLocalPlayer::CLocalPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow) : CPlayer(pGame, pInfoWindow, pInputWindow)
{
	m_PlayerType = LocalPlayer;
}

IPlayer *CreateLocalPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow)
{
	return new CLocalPlayer(pGame, pInfoWindow, pInputWindow);
}