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
	protected:
	#ifdef _WIN32
	WSADATA m_Wsadata;
	#endif
	struct addrinfo *m_pServInfo;
	void *GetInAddr(struct sockaddr *pSa);
	int m_Sockfd;
	virtual int DoStartup() = 0;
	virtual int DoConnect(const char *pIp) = 0;

	public:
	virtual ~INetwork() {}
	int Init();
	int Recv(void *pData, unsigned Maxsize);
	int Send(const void *pData, unsigned Size);
	void Shutdown();
	int Startup() { return DoStartup(); }
	int Connect(const char *pIp) { return DoConnect(pIp); }
} ;

class CServer : public INetwork
{
	private:
	int m_OwnSockfd;
	struct sockaddr_storage m_TheirAddr;
	socklen_t m_SinSize;

	protected:
	int DoStartup();
	int DoConnect(const char *pIp) { return 0; }
} ;

class CClient : public INetwork
{
	protected:
	int DoStartup();
	int DoConnect(const char *pIp);
} ;

extern INetwork *CreateServer();
extern INetwork *CreateClient();

#endif


	
