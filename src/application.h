#ifndef APP_DEFINED
#define APP_DEFINED

#include "game.h"
#include "gui.h"

class IMenu;

class CApplication
{
	private:
	IMenu *m_pMenu;
	CGui *m_pGui;
	CGui *Gui() { return m_pGui; }
	IMenu *Menu() { return m_pMenu; }

	bool m_Running;

	public:
	CApplication();
	~CApplication();
	void Run();
	void Quit();
	void StartGame(GameType GameType);
} ;

#endif
