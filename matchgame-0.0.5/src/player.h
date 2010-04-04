#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

class CNet;
class IGame;

enum PlayerType
{
	LocalPlayer,
	LocalNetPlayer,
	DistantNetPlayer
} ;

class IPlayer
{
	protected:
	int m_StackNumber, m_Amount;
	PlayerType m_PlayerType;
	IGame *m_pGame;

	IGame *Game() { return m_pGame; }
	virtual bool DoTurn(int *pStackNumber, int *pAmount) = 0;
	void TurnInput(int *pStackNumber, int *pAmount);

	public:
	virtual ~IPlayer() {}
	bool Turn(int *pStackNumber, int *pAmount) { return DoTurn(pStackNumber, pAmount); }
} ;

class CLocalPlayer : public IPlayer
{
	protected:
	bool DoTurn(int *pStackNumber, int *pAmount);

	public:
	CLocalPlayer(IGame *pGame);
} ;

class CLocalNetPlayer : public IPlayer
{
	protected:
	bool DoTurn(int *pStackNumber, int *pAmount);

	private:
	CNet *m_pNet;

	CNet *Net() { return m_pNet; }

	public:
	CLocalNetPlayer(CNet *pNet, IGame *pGame);
} ;

class CDistantNetPlayer : public IPlayer
{
	protected:
	bool DoTurn(int *pStackNumber, int *pAmount);

	private:
	CNet *m_pNet;

	CNet *Net() { return m_pNet; }

	public:
	CDistantNetPlayer(CNet *pNet, IGame *pGame);
} ;

extern IPlayer *CreatePlayer(PlayerType PlayerType);

#endif

