#ifndef SERVER_DEFINED
#define SERVER_DEFINED

#ifdef _WIN32
	#include <winsock.h>
#else
	#include <netdb.h>
	#include <arpa/inet.h>
	#define closesocket(s) close(s)
#endif
#include <string.h>
#define PORT "7005"
#define BACKLOG 10

class CServer
{
	private:
	int m_OwnSockfd, m_Sockfd;
	struct addrinfo *m_pServInfo;
	struct sockaddr_storage m_TheirAddr;
	socklen_t m_SinSize;
	void *GetInAddr(struct sockaddr *pSa);
	int InitServInfo();
	int BindToOwnSock();
	int StartListening();
	int AcceptConnection();

	public:
	int StartupServer();
	bool RecieveNumber(int *pValue);
	bool SendNumber(int *pValue);
	void CloseConnection();
} ;

extern CServer *CreateServer();

#endif

