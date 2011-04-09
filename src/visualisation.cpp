#include "visualisation.h"
#include "playfield.h"
#include "console.h"

void CVisualisation::ShowField(CPlayfield *pField)
{	
	CConsole::Print("\n");
	for(int i = 0;i < pField->NumberOfStacks();i++)
	{
		CConsole::Print("%d: ", i+1);
		for(int j = 0;j < pField->ShowField()[i];j++)
			CConsole::Print("|");
		CConsole::Print("\n");
	}
	CConsole::Print("\n");
	return;
}

IVisualisation *CreateVisualisation()
{
	return new CVisualisation;
}

