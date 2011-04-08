#ifndef APP_DEFINED
#define APP_DEFINED

#include "../game/game.h"

class IMenu;

class CApplication
{
	private:
	IMenu *m_pMenu;
	IMenu *Menu() { return m_pMenu; }
	bool m_Running;
	void DoAction(int Action);

	public:
	CApplication();
	~CApplication();
	void Run();
	void Quit();
	void StartGame(GameType GameType);
} ;

#endif
