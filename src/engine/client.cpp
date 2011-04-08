#include "client.h"
#include "network.h"
#include "console.h"

CClient::~CClient()
{
	Shutdown();
}

void *CClient::GetInAddr(struct sockaddr *pSa)
{
	if (pSa->sa_family == AF_INET)
	{
		return &(((struct sockaddr_in*)pSa)->sin_addr);
	}

	return &(((struct sockaddr_in6*)pSa)->sin6_addr);
}

int CClient::Init()
{
	// make sure everythings is fine for windows
	#ifdef _WIN32  
	WSADATA wsaData;
	if (WSAStartup (MAKEWORD (1, 1), &wsaData) != 0)
	{
		CConsole::Print("Client: Failed to init (WSAStartup)!\n");
		return -1;
    }
	#endif

	if(SetAddress() == -1)
		return -1;

	char aIP[INET6_ADDRSTRLEN];
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
		CConsole::Print("Client: Failed to init (connect)!\n");
		freeaddrinfo(m_pServInfo);
		return -1;
	}
	#ifdef _WIN32
	getnameinfo((struct sockaddr *)pP->ai_addr, sizeof (struct sockaddr), aIP, sizeof aIP, 0, NI_MAXSERV, NI_NUMERICSERV);
	#else
	inet_ntop(pP->ai_family, GetInAddr((struct sockaddr *)pP->ai_addr), aIP, sizeof aIP);
	#endif
	CConsole::Print("Client: connecting to %s\n\n", aIP);
	freeaddrinfo(m_pServInfo);
	return 0;
}

int CClient::SetAddress()
{
	struct addrinfo *pHints = new struct addrinfo;

	char aHost[64];
	CConsole::Print("Serveraddress: ");
	CConsole::GetString(aHost);
	
	memset(pHints, 0, sizeof *pHints);
	pHints->ai_family = AF_UNSPEC;
	pHints->ai_socktype = SOCK_STREAM;

	if (getaddrinfo(aHost, PORT, pHints, &m_pServInfo) != 0)
	{
		CConsole::Print("Client: Failed to set the address (getaddrinfo)!\n");
		delete pHints;
		return -1;
	}
	delete pHints;
	return 0;
}

int CClient::Recv(void *pData, unsigned Maxsize)
{
	int Ret;
	Ret = recv(m_Sockfd, (char*)pData, Maxsize, 0);
	return Ret;
}

int CClient::Send(const void *pData, unsigned Size)
{
	int Ret;
	#if defined (_WIN32) || defined (__APPLE__)
	Ret = send(m_Sockfd, (const char*)pData, Size, 0);
	#else
	Ret = send(m_Sockfd, (const char*)pData, Size, MSG_NOSIGNAL);
	#endif
	return Ret;
}

void CClient::Shutdown()
{
	close(m_Sockfd);
	return;
}

INetwork *CreateClient() { return new CClient; }
