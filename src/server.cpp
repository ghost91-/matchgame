#include "server.h"
#include "console.h"

void* CServer::GetInAddr(struct sockaddr *pSa)
{
	if (pSa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)pSa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)pSa)->sin6_addr);
}

int CServer::InitServInfo()
{
	int Ret;
	struct addrinfo	*pHints = new struct addrinfo;

	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;
	pHints->ai_flags = AI_PASSIVE; // use my IP

	if ((Ret = getaddrinfo(NULL, PORT, pHints, &m_pServInfo)) != 0)
	{
		delete pHints;
        	return -1;
	}
	delete pHints;
	return 0;
}

int CServer::BindToOwnSock()
{
	int yes = 1;
	struct addrinfo *pP;// = new struct addrinfo;
	for(pP = m_pServInfo; pP != NULL; pP = pP->ai_next)
	{
		if ((m_OwnSockfd = socket(pP->ai_family, pP->ai_socktype, pP->ai_protocol)) == -1)
		{
			continue;
		}
		if (setsockopt(m_OwnSockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			return -1;
		}
		if (bind(m_OwnSockfd, pP->ai_addr, pP->ai_addrlen) == -1)
		{
			close(m_OwnSockfd);
			continue;
		}
		break;
	}
	if (pP == NULL)
	{
		return -1;
	}
	freeaddrinfo(m_pServInfo);
	return 0;
}

int CServer::StartListening()
{
	if (listen(m_OwnSockfd, BACKLOG) == -1)
	{
		return -1;
	}
	CConsole::Print("Server: waiting for connections...\n");
	return 0;
}
	
int CServer::AcceptConnection()
{
	char aIp[INET6_ADDRSTRLEN];
	m_SinSize = sizeof m_TheirAddr;
	m_Sockfd = accept(m_OwnSockfd, (struct sockaddr *)&m_TheirAddr, &m_SinSize);
	if (m_Sockfd == -1)
	{
		return -1;
	}
	#ifdef _WIN32
	getnameinfo((struct sockaddr *)&m_TheirAddr, sizeof (struct sockaddr), aIp, sizeof aIp, 0, NI_MAXSERV, NI_NUMERICSERV);
	#else
	inet_ntop(m_TheirAddr.ss_family, GetInAddr((struct sockaddr *)&m_TheirAddr), aIp, sizeof aIp);
	#endif
	CConsole::Print("Server: got connection from %s\n\n", aIp);
	return 0;
}
	

int CServer::StartupServer()
{
	#ifdef _WIN32  
	/* Initialisiere TCP für Windows ("winsock") */
	short wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD (1, 1);
	if (WSAStartup (wVersionRequested, &wsaData) != 0)
	{
		return -1;
    	}
	#endif
	int a, b, c, d;
	a = InitServInfo();
	b = BindToOwnSock();
	c = StartListening();
	d = AcceptConnection();
	close(m_OwnSockfd);
	if((a == -1) || (b == -1) || (c == -1) || (d == -1))
		return -1;
	else
		return 0;
}

bool CServer::RecieveNumber(int *pValue)
{
	int Ret;
	uint32_t *pBuf = new uint32_t;
	Ret = recv(m_Sockfd, pBuf, sizeof *pBuf, 0);
	*pValue = ntohl(*pBuf);
	delete pBuf;
	if (Ret < 0)
	{
		CConsole::PrintError(RecvError);
		return false;
	}
	else if (Ret == 0)
	{
		CConsole::PrintError(OpponentQuit);
		return false;
	}
	return true;
}

bool CServer::SendNumber(int *pValue)
{
	int Ret;
	uint32_t *pBuf = new uint32_t;
	*pBuf = htonl(*pValue);
	#ifdef _WIN32
	Ret = send(m_Sockfd, pBuf, sizeof *pBuf, 0);
	#else
	Ret = send(m_Sockfd, pBuf, sizeof *pBuf, MSG_NOSIGNAL);
	#endif
	delete pBuf;
	if (Ret < 0)
	{
		CConsole::PrintError(SendError);
		return false;
	}
	return true;
}

void CServer::CloseConnection()
{
	close(m_Sockfd);
	return;
}

CServer *CreateServer()
{
	return new CServer;
}

