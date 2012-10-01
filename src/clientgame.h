#ifndef CLIENTGAME_DEFINED
#define CLIENTGAME_DEFINED

#include "game.h"

class INetwork;
class CGui;

class CClientGame : public CGame
{
	private:
	INetwork *m_pNetwork;

	public:
	CClientGame(CGui *pGui);
	~CClientGame();
	int Init();
} ;

#endif
