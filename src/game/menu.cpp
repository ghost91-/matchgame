#include "menu.h"
#include "../engine/console.h"

void CMenu::DoDisplay()
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
}
  
void CMenu::DoSelect()
{
	unsigned Select;
	CConsole::GetUnsigned(&Select);
	if(Select<m_Entries.size())
	{
		m_Entries[Select]->Action();
	}
	else
	{
		CConsole::Print("Please select a valid menuentry!\n");
	}
	return;
}

IMenu *CreateMenu()
{
	return new CMenu;
}

