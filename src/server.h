#ifndef SERVER_DEFINED
#define SERVER_DEFINED

#ifdef _WIN32
	#define _WIN32_WINNT 0x501
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define socklen_t int
	#define close(s) closesocket(s)
#else
	#include <netdb.h>
	#include <arpa/inet.h>
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
	bool Recv(void *pData, unsigned Maxsize);
	bool Send(const void *pData, unsigned Size);
	void CloseConnection();
} ;

extern CServer *CreateServer();

#endif


