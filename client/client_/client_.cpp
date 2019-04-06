// server_.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "tictactoe.h"


using namespace std;
SOCKET connection1;
bool socketInitiaion(WSAData &wsaData,WORD &DllVersion )
{
	DllVersion = MAKEWORD(2, 1);

	//If WSAStartup returns anything other than 0, then that means an error has occured in the WinSock Startup.
	if (WSAStartup(DllVersion, &wsaData) != 0) 
	{
		cout << " Socket initiation Faild! "  << endl;
		return 0;
	}
	
	return 1;
	
}
void addrAndSockBinder(SOCKADDR_IN& addr, SOCKET &sListen){
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	sListen = socket( AF_INET, SOCK_STREAM, NULL );
	bind( sListen, (SOCKADDR*)&addr, sizeof(addr) );
	listen( sListen, SOMAXCONN );
}


void sendMsg(string msg) {
	int size = msg.size();
	send(connection1, (char*)&size, sizeof(int), NULL);
	send(connection1, msg.c_str(), size, NULL);
}


void getServerMsg(){

	int size;

	while(1)
	{
		recv(connection1,(char*)&size,sizeof(int),NULL);

		char* buf = new char[size+1];
		buf[size] = '\0';
		recv(connection1,buf,size,NULL);

		cout << buf << endl;
		string row = std::to_string(rand() % 3),
		col = std::to_string(rand() % 3);
		cout << " row : " << row << endl << " col : " << col << endl;

		sendMsg(row);
		sendMsg(col);

		delete[size] buf;
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	// socket options
	WSAData wsaData;
	WORD DllVersion;
	if(!socketInitiaion(wsaData,DllVersion) )
		return 0;
	

	// adress to be binded to socket
	SOCKADDR_IN addr;
	SOCKET sListen;
	int sizeOfAddr = sizeof(addr);
	addrAndSockBinder(addr,sListen);
	
	connection1 = socket(AF_INET,SOCK_STREAM,NULL);

	if(connect(connection1,(SOCKADDR*)&addr,sizeOfAddr))
	{
		cout << "client : connection Failed " << endl;
		return 0;
	}

	HANDLE threadHDL = CreateThread(NULL,NULL,(LPTHREAD_START_ROUTINE)getServerMsg,NULL,NULL,NULL);

	string buf;

	/*while(1)
	{
		getline(cin,buf);
		sendMsg(buf);
	}*/

	


	WaitForSingleObject(threadHDL,INFINITE);
	closesocket(connection1);
	system("pause");
	return 0;

}

