#ifndef SERVER_DEFINED
#define SERVER_DEFINED

#include "network.h"

class CServer : public INetwork
{
	private:
	struct addrinfo *m_pServInfo;
	int m_Sockfd;
	int m_OwnSockfd;
	struct sockaddr_storage m_TheirAddr;
	socklen_t m_SinSize;
	
	void *GetInAddr(struct sockaddr *pSa);

	public:
	virtual int Init();
	virtual int Recv(void *pData, unsigned Maxsize);
	virtual int Send(const void *pData, unsigned Size);
	virtual void Shutdown();
} ;

#endif