#include "localplayer.h"
#include "player.h"
#include "game.h"

CLocalPlayer::CLocalPlayer(IGame *pGame):CPlayer(pGame)
{
	m_PlayerType = LocalPlayer;
}

IPlayer *CreateLocalPlayer(IGame *pGame)
{
	return new CLocalPlayer(pGame);
}