#include "playfield.h" 

CPlayfield::CPlayfield(int NumberOfStacks, int MaxAmount)
{
	m_NumberOfStacks = NumberOfStacks;
	m_MaxAmount = MaxAmount;
	m_pStack = new int[m_NumberOfStacks];
	for(int i = 0;i < m_NumberOfStacks;i++)
		m_pStack[i]= 2*i+1;
}

CPlayfield::~CPlayfield()
{
	delete [] m_pStack;
}

int* CPlayfield::ShowField()
{
	return m_pStack;
}

void CPlayfield::RemoveMatches(int StackNumber, int Amount)
{
	m_pStack[StackNumber-1] = m_pStack[StackNumber-1] - Amount;
	return;
}

bool CPlayfield::CanTakeMatches(int StackNumber, int Amount)
{
	if((StackNumber < 1)||(StackNumber > m_NumberOfStacks)||(Amount > m_pStack[StackNumber-1]))
		return false;
	else
		return true;
}

int CPlayfield::NumberOfStacks()
{
	return m_NumberOfStacks;
}

bool CPlayfield::MatchExist()
{
	int NumberOfMatches = 0;
	for(int i = 0;i < m_NumberOfStacks;i++)
		NumberOfMatches += m_pStack[i];
	if(NumberOfMatches > 0)
		return true;
	else
		return false;
}

CPlayfield *CreatePlayfield(int NumberOfStacks, int MaxAmount)
{
	return new CPlayfield(NumberOfStacks, MaxAmount);
}

