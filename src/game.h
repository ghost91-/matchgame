#ifndef GAME_DEFINED
#define GAME_DEFINED

class CPlayfield;
class INetwork;
class IPlayer;
class IVisualisation;
class CGui;
class CWindow;

enum GameType
{
	Notknown,
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
	bool m_Initiated;
	CGui *m_pGui;
	GameType m_GameType;
	int m_StackNumber, m_MaxAmount;
	CPlayfield *m_pField;
	IPlayer *m_paPlayer[2];
	IVisualisation *m_pVisualisation;

	CWindow  *m_pInfoWindow;
	CWindow *m_pGameWindow;
	CWindow *m_pInputWindow;

	IPlayer **Player() { return m_paPlayer; }
	CPlayfield *Field() { return m_pField; }
	IVisualisation *Visualisation() { return m_pVisualisation; }

	bool ValidTurn(int StackNumber, int Amount);
	bool AllowedToTakeMatches(int Amount);
	void ShowPlayfield();

	public:
	CGame(CGui *pGui);
	virtual ~CGame();
	virtual int Init();
	virtual void Play();
} ;

extern IGame *CreateGame(CGui *pGui);
extern IGame *CreateLocalGame(CGui *pGui);
extern IGame *CreateServerGame(CGui *pGui);
extern IGame *CreateClientGame(CGui *pGui);

#endif

