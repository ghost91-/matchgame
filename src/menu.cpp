#include "menu.h"
#include "console.h"

#include <ncurses.h>

/*void CMenu::DoDisplay()
{
	CConsole::Print("Menu:\n");
	int Number = 0;
	std::vector<IMenuEntry*>::iterator Iterator = m_Entries.begin();
	while(Iterator != m_Entries.end())
	{
		CConsole::Print("%d - %s\n", Number, (*Iterator)->GetName());
		++Iterator;
		++Number;
	}
	return;
}*/
  
void CMenu::DoSelect()
{
	WINDOW *pMenuWin;
	int c;
	unsigned int Highlight = 0;
	int Selection = -1;
	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */

	int StartX = (COLS - 40) / 2;
	int StartY = (LINES - 6) / 2;
	pMenuWin = newwin(6, 40, StartY, StartX);
	keypad(pMenuWin, TRUE);

	mvprintw(0, 0, "Use arrow keys to go up and down, press enter to select a menu entry");
	refresh();

	Print(pMenuWin, Highlight);

	while(1)
	{	
		c = wgetch(pMenuWin);
		switch(c)
		{	case KEY_UP:
				if(Highlight == 0)
					Highlight = m_Entries.size() - 1;
				else
					Highlight--;
				break;
			case KEY_DOWN:
				if(Highlight == m_Entries.size() - 1)
					Highlight = 0;
				else 
					Highlight++;
				break;
			case 10:
					Selection = Highlight;
				break;
			default:
				break;
		}

		if(Selection >= 0)
		{
			clrtoeol();
			refresh();
			endwin();
			m_Entries[Selection]->Action();
			break;
		}
		else
			Print(pMenuWin, Highlight);
	}	
	return;
}

void CMenu::Print(WINDOW *pMenuWin, unsigned int Highlight)
{
	int x = 1, y = 1;
	box(pMenuWin, 0, 0);
	for(unsigned int i = 0; i < m_Entries.size(); i++)
	{	if(Highlight == i) /* High light the present choice */
		{	wattron(pMenuWin, A_REVERSE); 
			mvwprintw(pMenuWin, y, x, "%s", m_Entries[i]->GetName());
			wattroff(pMenuWin, A_REVERSE);
		}
		else
			mvwprintw(pMenuWin, y, x, "%s", m_Entries[i]->GetName());
		y++;
	}
	wrefresh(pMenuWin);
}

IMenu *CreateMenu()
{
	return new CMenu;
}

