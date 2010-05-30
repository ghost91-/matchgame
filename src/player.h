#ifndef PLAYER_DEFINED
#define PLAYER_DEFINED

class INetwork;
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
	virtual int DoTurn(int *pStackNumber, int *pAmount) = 0;
	void TurnInput(int *pStackNumber, int *pAmount);

	public:
	virtual ~IPlayer() {}
	int Turn(int *pStackNumber, int *pAmount) { return DoTurn(pStackNumber, pAmount); }
} ;

class CLocalPlayer : public IPlayer
{
	protected:
	int DoTurn(int *pStackNumber, int *pAmount);

	public:
	CLocalPlayer(IGame *pGame);
} ;

class CLocalNetPlayer : public IPlayer
{
	protected:
	int DoTurn(int *pStackNumber, int *pAmount);

	private:
	INetwork *m_pNetwork;

	INetwork *Network() { return m_pNetwork; }

	public:
	CLocalNetPlayer(INetwork *pNetwork, IGame *pGame);
} ;

class CDistantNetPlayer : public IPlayer
{
	protected:
	int DoTurn(int *pStackNumber, int *pAmount);

	private:
	INetwork *m_pNetwork;

	INetwork *Network() { return m_pNetwork; }

	public:
	CDistantNetPlayer(INetwork *pNetwork, IGame *pGame);
} ;

extern IPlayer *CreatePlayer(PlayerType PlayerType);

#endif

