#ifndef SERVERGAME_DEFINED
#define SERVERGAME_DEFINED

#include "game.h"


class INetwork;
class CGui;

class CServerGame : public CGame
{
	private:
	INetwork *m_pNetwork;

	public:
	CServerGame(CGui *pGui);
	~CServerGame();
	int Init();
} ;

#endif
