#ifndef CLIENT_DEFINED
#define CLIENT_DEFINED

#include <netdb.h>
#include <arpa/inet.h>
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
	bool RecieveNumber(int *pValue);
	bool SendNumber(int *pValue);
	void CloseConnection();
} ;

extern CClient *CreateClient();

#endif

