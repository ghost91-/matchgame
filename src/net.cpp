#include "net.h"
#include "client.h"
#include "server.h"

CNet::CNet()
{
	m_pServer = CreateServer();
	m_pClient = CreateClient();
	m_NetType = NoNet;
}

CNet::~CNet()
{
	delete m_pServer;
	delete m_pClient;
	}

int CNet::Startup()
{
	m_NetType = ServerNet;
	return Server()->StartupServer();
}

int CNet::Startup(char *pIpString)
{
	m_NetType = ClientNet;
	return Client()->StartConnecting(pIpString);
}

bool CNet::Recv(void *pData, unsigned Maxsize)
{
	if (m_NetType == ServerNet)
		return Server()->Recv(pData, Maxsize);
	else if (m_NetType == ClientNet)
		return Client()->Recv(pData, Maxsize);
	else
		return false;
}

bool CNet::Send(const void *pData, unsigned Size)
{
	if (m_NetType == ServerNet)
		return Server()->Send(pData, Size);
	else if (m_NetType == ClientNet)
		return Client()->Send(pData, Size);
	else
		return false;
}

void CNet::ShutDown()
{
	if (m_NetType == ServerNet)
		Server()->CloseConnection();
	else if (m_NetType == ClientNet)
		Client()->CloseConnection();
	m_NetType = NoNet;
}

CNet *CreateNet() 
{
	return new CNet;
}

