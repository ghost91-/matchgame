#include "visualisation.h"
#include "playfield.h"
#include "gui.h"

CVisualisation::CVisualisation(CWindow *pWindow) : m_pWindow(pWindow)
{

}

void CVisualisation::ShowField(CPlayfield *pField)
{	
	m_pWindow->Clear();
	for(int i = 0; i < pField->NumberOfStacks();i++)
	{
		m_pWindow->MovePrint(i, 0, "%d: ", i+1);
		for(int j = 0; j < pField->ShowField()[i];j++)
			m_pWindow->Print("|");
	}
	m_pWindow->Update();
	return;
}

IVisualisation *CreateVisualisation(CWindow *pWindow)
{
	return new CVisualisation(pWindow);
}

