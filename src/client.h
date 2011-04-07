#ifndef CLIENT_DEFINED
#define CLIENT_DEFINED

#include "network.h"

class CClient : public INetwork
{
	private:
	struct addrinfo *m_pServInfo;
	int m_Sockfd;
	
	void *GetInAddr(struct sockaddr *pSa);
	int SetAddress();

	public:

	virtual int Init();
	virtual int Recv(void *pData, unsigned Maxsize);
	virtual int Send(const void *pData, unsigned Size);
	virtual void Shutdown();

} ;

#endif