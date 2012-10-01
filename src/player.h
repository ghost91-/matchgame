#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

class INetwork;
class IGame;
class CWindow;

enum PlayerType
{
	Unknown,
	LocalPlayer,
	LocalNetPlayer,
	DistantNetPlayer
} ;

class IPlayer
{
	public:
	virtual ~IPlayer() {}
	virtual int Turn(int *pStackNumber, int *pAmount) = 0;
} ;

class CPlayer : public IPlayer
{
	protected:
	int m_StackNumber, m_Amount;
	PlayerType m_PlayerType;
	IGame *m_pGame;
	CWindow *m_pInfoWindow;
	CWindow *m_pInputWindow;

	IGame *Game() { return m_pGame; }
	void TurnInput(int *pStackNumber, int *pAmount);

	public:
	CPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
	virtual ~CPlayer() {}
	virtual int Turn(int *pStackNumber, int *pAmount);
} ;

extern IPlayer *CreatePlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
extern IPlayer *CreateLocalPlayer(IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
extern IPlayer *CreateLocalNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);
extern IPlayer *CreateDistantNetPlayer(INetwork *pNetwork, IGame *pGame, CWindow *pInfoWindow, CWindow *pInputWindow);


#endif

