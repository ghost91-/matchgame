#ifndef NETWORK_DEFINED
#define NETWORK_DEFINED

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

class INetwork
{
	public:
	virtual ~INetwork() {}
	virtual int Init() = 0;
	virtual int Recv(void *pData, unsigned Maxsize) = 0;
	virtual int Send(const void *pData, unsigned Size) = 0;
	virtual void Shutdown() = 0;
} ;

extern INetwork *CreateServer();
extern INetwork *CreateClient();

#endif


	
