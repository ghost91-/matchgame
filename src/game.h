#ifndef GAME_DEFINED
#define GAME_DEFINED

class CPlayfield;
class INetwork;
class IPlayer;
class IVisualisation;

enum GameType
{
	LocalGame,
	ServerGame,
	ClientGame
} ;

class IGame
{
	protected:
	bool m_Initiated;
	int m_StackNumber, m_MaxAmount;
	CPlayfield *m_pField;
	IPlayer *m_paPlayer[2];
	IVisualisation *m_pVisualisation;

	virtual int DoInit() = 0;
	IPlayer **Player() { return m_paPlayer; }
	CPlayfield *Field() { return m_pField; }
	IVisualisation *Visualisation() { return m_pVisualisation; }

	bool ValidTurn(int StackNumber, int Amount);
	bool AllowedToTakeMatches(int Amount);
	void ShowPlayfield();

	public:
	virtual ~IGame() {}
	int Init() { return DoInit(); }
	void Play();
} ;

class CLocalGame : public IGame
{
	protected:
	int DoInit();

	public:
	CLocalGame();
	~CLocalGame();

} ;

class CServerGame : public IGame
{
	private:
	INetwork *m_pNetwork;

	protected:
	int DoInit();

	public:
	CServerGame();
	~CServerGame();

} ;

class CClientGame : public IGame
{
	private:
	INetwork *m_pNetwork;

	protected:
	int DoInit();

	public:
	CClientGame();
	~CClientGame();

} ;

extern IGame *CreateGame(GameType GameType);

#endif

