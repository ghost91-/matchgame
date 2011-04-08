#include "visualisation.h"
#include "playfield.h"
#include "../engine/console.h"

class CVisualisation : public IVisualisation
{
	protected:

	void DoShowField(CPlayfield *pField)
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
} ;

IVisualisation *CreateVisualisation()
{
	return new CVisualisation;
}

