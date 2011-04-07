#include "server.h"
#include "network.h"
#include "console.h"

CServer::~CServer()
{
	Shutdown();
}

void *CServer::GetInAddr(struct sockaddr *pSa)
{
	if (pSa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)pSa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)pSa)->sin6_addr);
}

int CServer::Init()
{
	// make sure everythings is fine for windows
	#ifdef _WIN32  
	WSADATA wsaData;
	if (WSAStartup (MAKEWORD (1, 1), &wsaData) != 0)
	{
		CConsole::Print("Server: Failed to init (WSAStartup)!\n");
		return -1;
    }
	#endif
	
	struct addrinfo	*pHints = new struct addrinfo;

	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;
	pHints->ai_flags = AI_PASSIVE; // use my IP

	if (getaddrinfo(NULL, PORT, pHints, &m_pServInfo) != 0)
	{
		CConsole::Print("Server: Failed to init (getaddrinfo)!\n");
		delete pHints;
        return -1;
	}
	delete pHints;

	char yes[2] = "1";
	struct addrinfo *pP;// = new struct addrinfo;
	for(pP = m_pServInfo; pP != NULL; pP = pP->ai_next)
	{
		if ((m_OwnSockfd = socket(pP->ai_family, pP->ai_socktype, pP->ai_protocol)) == -1)
		{
			continue;
		}
		if (setsockopt(m_OwnSockfd, SOL_SOCKET, SO_REUSEADDR, yes, sizeof(int)) == -1)
		{
			CConsole::Print("Server: Failed to init (setsockopt)!\n");
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
		CConsole::Print("Server: Failed to init (bind)!\n");
		return -1;
	}
	freeaddrinfo(m_pServInfo);

	if (listen(m_OwnSockfd, BACKLOG) == -1)
	{
		CConsole::Print("Server: Failed to init (listen)!\n");
		return -1;
	}
	CConsole::Print("Server: waiting for connections...\n");

	char aIp[INET6_ADDRSTRLEN];
	m_SinSize = sizeof m_TheirAddr;
	m_Sockfd = accept(m_OwnSockfd, (struct sockaddr *)&m_TheirAddr, &m_SinSize);
	if (m_Sockfd == -1)
	{
		CConsole::Print("Server: Failed to init (accept)!\n");
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

int CServer::Recv(void *pData, unsigned Maxsize)
{
	int Ret;
	Ret = recv(m_Sockfd, (char*)pData, Maxsize, 0);
	return Ret;
}

int CServer::Send(const void *pData, unsigned Size)
{
	int Ret;
	#if defined (_WIN32) || defined (__APPLE__)
	Ret = send(m_Sockfd, (const char*)pData, Size, 0);
	#else
	Ret = send(m_Sockfd, (const char*)pData, Size, MSG_NOSIGNAL);
	#endif
	return Ret;
}

void CServer::Shutdown()
{
	close(m_Sockfd);
	return;
}

INetwork *CreateServer() { return new CServer; }
