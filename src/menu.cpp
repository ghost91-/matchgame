#include "menu.h"

#include "gui.h"
  
CMenu::CMenu(CGui *pGui)
{
	m_pGui = pGui;
}

void CMenu::DoSelect()
{
	unsigned int Highlight = 0;
	int Selection = -1, c;

	int StartX = (m_pGui->GetMaxX() - 40) / 2;
	int StartY = (m_pGui->GetMaxY() - 6) / 2;
	CWindow * pWindow = m_pGui->CreateWindow(6, 40, StartY, StartX);

	m_pGui->GetMainWindow()->MovePrint(0, 0, "Use arrow keys to go up and down, press enter to select a menu entry");
	m_pGui->GetMainWindow()->Update();

	Print(pWindow, Highlight);

	while(1)
	{	
		c = pWindow->GetCh();
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
			delete pWindow;
			m_Entries[Selection]->Action();
			break;
		}
		else
			Print(pWindow, Highlight);
	}	
	return;
}

void CMenu::Print(CWindow *pMenuWin, unsigned int Highlight)
{
	int x = 1, y = 1;
	for(unsigned int i = 0; i < m_Entries.size(); i++)
	{	if(Highlight == i) /* High light the present choice */
		{	pMenuWin->ActivateAttribute(Reverse); 
			pMenuWin->MovePrint(y, x, "%s", m_Entries[i]->GetName());
			pMenuWin->DeactivateAttribute(Reverse);
		}
		else
			pMenuWin->MovePrint(y, x, "%s", m_Entries[i]->GetName());
		y++;
	}
	pMenuWin->Update();
}

IMenu *CreateMenu(CGui *pGui)
{
	return new CMenu(pGui);
}

