#ifndef SERVERGAME_DEFINED
#define SERVERGAME_DEFINED

#include "game.h"

class INetwork;

class CServerGame : public CGame
{
	private:
	INetwork *m_pNetwork;

	public:
	CServerGame();
	~CServerGame();
	int Init();
} ;

#endif
