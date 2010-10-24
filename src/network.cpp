#include "network.h"
#include "console.h"

void *INetwork::GetInAddr(struct sockaddr *pSa)
{
	if (pSa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)pSa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)pSa)->sin6_addr);
}

int INetwork::Init()
{
	#ifdef _WIN32  
	WSADATA wsaData;
	if (WSAStartup (MAKEWORD (1, 1), &wsaData) != 0)
	{
		return -1;
    	}
	#endif
	return 0;
}

int INetwork::Recv(void *pData, unsigned Maxsize)
{
	int Ret;
	Ret = recv(m_Sockfd, (char*)pData, Maxsize, 0);
	return Ret;
}

int INetwork::Send(const void *pData, unsigned Size)
{
	int Ret;
	#if defined (_WIN32) || defined (__APPLE__)
	Ret = send(m_Sockfd, (const char*)pData, Size, 0);
	#else
	Ret = send(m_Sockfd, (const char*)pData, Size, MSG_NOSIGNAL);
	#endif
	return Ret;
}

void INetwork::Shutdown()
{
	close(m_Sockfd);
	return;
}

int CServer::DoStartup()
{
	struct addrinfo	*pHints = new struct addrinfo;

	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;
	pHints->ai_flags = AI_PASSIVE; // use my IP

	if (getaddrinfo(NULL, PORT, pHints, &m_pServInfo) != 0)
	{
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

	if (listen(m_OwnSockfd, BACKLOG) == -1)
	{
		return -1;
	}
	CConsole::Print("Server: waiting for connections...\n");

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


int CClient::DoConnect(const char *pIp)
{
	struct addrinfo *pHints = new struct addrinfo;

	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;

	if (getaddrinfo(pIp, PORT, pHints, &m_pServInfo) != 0)
	{
		delete pHints;
		return -1;
	}
	delete pHints;
	return 0;
}
	
int CClient::DoStartup()
{
	char aIp[INET6_ADDRSTRLEN];
	struct addrinfo *pP;
	for(pP = m_pServInfo; pP != NULL; pP = pP->ai_next)
	{
		if ((m_Sockfd = socket(pP->ai_family, pP->ai_socktype, pP->ai_protocol)) == -1)
		{
			continue;
		}
		if (connect(m_Sockfd, pP->ai_addr, pP->ai_addrlen) == -1)
		{
			close(m_Sockfd);
			continue;
		}
      		break;
	}
	if (pP == NULL)
	{
		freeaddrinfo(m_pServInfo);
		return -1;
	}
	#ifdef _WIN32
	getnameinfo((struct sockaddr *)pP->ai_addr, sizeof (struct sockaddr), aIp, sizeof aIp, 0, NI_MAXSERV, NI_NUMERICSERV);
	#else
	inet_ntop(pP->ai_family, GetInAddr((struct sockaddr *)pP->ai_addr), aIp, sizeof aIp);
	#endif
	CConsole::Print("Client: connecting to %s\n\n", aIp);
	freeaddrinfo(m_pServInfo);
	return 0;
}

INetwork *CreateServer() { return new CServer; }
INetwork *CreateClient() { return new CClient; }

