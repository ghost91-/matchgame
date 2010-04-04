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

bool CNet::RecieveNumber(int *pValue)
{
	if (m_NetType == ServerNet)
		return Server()->RecieveNumber(pValue);
	else if (m_NetType == ClientNet)
		return Client()->RecieveNumber(pValue);
	else
		return false;
}

bool CNet::SendNumber(int *pValue)
{
	if (m_NetType == ServerNet)
		return Server()->SendNumber(pValue);
	else if (m_NetType == ClientNet)
		return Client()->SendNumber(pValue);
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

