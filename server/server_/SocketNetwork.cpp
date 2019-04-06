#include "stdafx.h"
#include "SocketNetwork.h"

bool SocketNetwork::socketInitiation(){
	DllVersion = MAKEWORD(2, 1);

	//If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		cout << " Socket initiation Faild! "  << endl;
		return 0;
	}

	return 1;

}

void SocketNetwork::addrAndSockBinder(){
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	sListen = socket( AF_INET, SOCK_STREAM, NULL );
	bind( sListen, (SOCKADDR*)&addr, sizeof(addr) );
	listen( sListen, SOMAXCONN );
}

SOCKET SocketNetwork::server_newConnection(){
	SOCKET con = accept(this->sListen,(SOCKADDR*)&(this->addr), &(this->sizeOfAddr));
	addConnectionToConList(con);
	return con;
}

void SocketNetwork::addConnectionToConList(SOCKET con){
	this->connections.push_back(con);
}

int SocketNetwork::getNumOfCons(){
	return this->connections.size();
}

vector<SOCKET> SocketNetwork::getConnections(){
	return this->connections;
}

SocketNetwork::~SocketNetwork(void)
{
}
