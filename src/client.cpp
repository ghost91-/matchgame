#include "client.h"
#include "console.h"

void* CClient::GetInAddr(struct sockaddr *pSa)
{
	if (pSa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)pSa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)pSa)->sin6_addr);
}

int CClient::InitServinfo(char *pIpString)
{
	struct addrinfo *pHints = new struct addrinfo;
	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;

	if (getaddrinfo(pIpString, PORT, pHints, &m_pServInfo) != 0)
	{
		delete pHints;
		return -1;
	}
	delete pHints;
	return 0;
}

int CClient::ConnectToServer()
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

int CClient::StartConnecting(char *pIpString)
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

	int Error;
	Error = InitServinfo(pIpString);
	if (Error == -1)
	{
		CConsole::PrintError(StartupError);
		return -1;
	}
	Error = ConnectToServer();
	if (Error == -1)
	{
		CConsole::PrintError(StartupError);
		return -1;
	}
	return 0;
}

bool CClient::RecieveNumber(int *pValue)
{
	int Ret;
	char *pBuf = new char;
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

bool CClient::SendNumber(int *pValue)
{
	int Ret;
	char *pBuf = new char;
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

void CClient::CloseConnection()
{
	close(m_Sockfd);
	return;
}

CClient *CreateClient()
{
	return new CClient;
}


