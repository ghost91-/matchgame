#ifndef LOCALGAME_DEFINED
#define LOCALGAME_DEFINED

#include "game.h"

class CLocalGame : public CGame
{	
	public:
	CLocalGame();
	int Init();
	void Play();
} ;