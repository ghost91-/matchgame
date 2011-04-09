#ifndef GAME_DEFINED
#define GAME_DEFINED

class CPlayfield;
class INetwork;
class IPlayer;
class IVisualisation;

enum GameType
{
	Unknown,
	LocalGame,
	ServerGame,
	ClientGame
} ;

class IGame
{
	public:
	virtual ~IGame() {}
	virtual int Init() = 0;
	virtual void Play() = 0;
} ;

class CGame : public IGame
{
	protected:
	GameType m_GameType;
	bool m_Initiated;
	int m_StackNumber, m_MaxAmount;
	CPlayfield *m_pField;
	IPlayer *m_paPlayer[2];
	IVisualisation *m_pVisualisation;

	IPlayer **Player() { return m_paPlayer; }
	CPlayfield *Field() { return m_pField; }
	IVisualisation *Visualisation() { return m_pVisualisation; }

	bool ValidTurn(int StackNumber, int Amount);
	bool AllowedToTakeMatches(int Amount);
	void ShowPlayfield();

	public:
	CGame();
	virtual ~CGame();
	virtual int Init();
	virtual void Play();
} ;

extern IGame *CreateGame();
extern IGame *CreateLocalGame();
extern IGame *CreateServerGame();
extern IGame *CreateClientGame();

#endif

