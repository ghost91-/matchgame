#ifndef CLIENTGAME_DEFINED
#define CLIENTGAME_DEFINED

#include "game.h"

class INetwork;

class CClientGame : public CGame
{
	private:
	INetwork *m_pNetwork;

	public:
	CClientGame();
	~CClientGame();
	int Init();
	void Play();
} ;

#endif