#ifndef NET_DEFINED
#define NET_DEFINED

class CServer;
class CClient;

enum NetType
{
	ServerNet,
	ClientNet,
	NoNet
} ;

class CNet
{
	private:
	CServer *m_pServer;
	CClient *m_pClient;
	NetType m_NetType;

	CServer *Server() { return m_pServer; }
	CClient *Client() { return m_pClient; }

	public:
	CNet();
	~CNet();
	int Startup();
	int Startup(char *pIpString);
	bool Recv(void *pData, unsigned Maxsize);
	bool Send(const void *pData, unsigned Size);
	void ShutDown();	
} ;

extern CNet *CreateNet();

#endif
	
