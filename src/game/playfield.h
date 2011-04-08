#ifndef PLAYFIELD_DEFINED
#define PLAYFIELD_DEFINED

class CPlayfield
{
	private:
	int m_NumberOfStacks, m_MaxAmount, *m_pStack;
	
	public:
	CPlayfield(int NumberOfStacks, int MaxAmount);
	~CPlayfield();
	int *ShowField();
	int NumberOfStacks();
	void RemoveMatches(int StackNumber, int Amount);
	bool CanTakeMatches(int StackNumber, int Amount);
	bool MatchExist();
} ;

extern CPlayfield *CreatePlayfield(int NumberOfStacks, int MaxAmount);

#endif

