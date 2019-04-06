#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <vector>

using namespace std;

class SocketNetwork
{
public:

private :
	WSAData wsaData;
	WORD DllVersion;
	SOCKADDR_IN addr;
	SOCKET sListen;
	int sizeOfAddr;
	vector<SOCKET> connections;

	void addConnectionToConList(SOCKET con);
public:
	SocketNetwork(){this->sizeOfAddr = sizeof(this->addr);}

	bool socketInitiation();
	void addrAndSockBinder();
	SOCKET server_newConnection();

	int getNumOfCons();
	vector<SOCKET> getConnections();


	~SocketNetwork(void);
};

