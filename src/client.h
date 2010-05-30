#ifndef CLIENT_DEFINED
#define CLIENT_DEFINED

#ifdef _WIN32
	#define _WIN32_WINNT 0x501
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define close(s) closesocket(s)
#else
	#include <netdb.h>
	#include <arpa/inet.h>
	#define closesocket(s) close(s)
#endif
#include <string.h>
#define PORT "7005"

class CClient
{
	private:
	int m_Sockfd;
	struct addrinfo *m_pServInfo;
	void *GetInAddr(struct sockaddr *pSa);
	int InitServinfo(char*);
	int ConnectToServer();

	public:
	int StartConnecting(char *pIpString);
	bool Recv(void *pData, unsigned Maxsize);
	bool Send(const void *pData, unsigned Size);
	void CloseConnection();
} ;

extern CClient *CreateClient();

#endif


