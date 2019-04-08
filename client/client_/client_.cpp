// server_.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <time.h>

#include "tictactoe.h"
#include "AI.h"

using namespace std;
SOCKET connection;

bool socketInitiaion(WSAData &wsaData, WORD &DllVersion)
{
	DllVersion = MAKEWORD(2, 1);

	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		cout << " Socket initiation Faild! " << endl;
		return 0;
	}

	return 1;

}
void addrAndSockBinder(SOCKADDR_IN& addr, SOCKET &sListen) {
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	addr.sin_port = htons(1111);
	addr.sin_family = AF_INET;

	sListen = socket(AF_INET, SOCK_STREAM, NULL);
	bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
	listen(sListen, SOMAXCONN);
}
void sendMsg(string msg) {
	int size = msg.size();
	send(connection, (char*)&size, sizeof(int), NULL);
	send(connection, msg.c_str(), size, NULL);
}
void getMap(Cell* data, int size) {
	Cell cc;

	for (int i = 0; i < size; i++)
	{
		recv(connection, (char*)&cc.row, sizeof(int), NULL);
		recv(connection, (char*)&cc.col, sizeof(int), NULL);
		recv(connection, (char*)&cc.val, sizeof(int), NULL);

		data[i].col = cc.col;
		data[i].row = cc.row;
		data[i].val = cc.val;

	}
}
void getChoices(Cell* data, int size) {
	Cell cc;

	for (int i = 0; i < size; i++)
	{
		recv(connection, (char*)&cc.row, sizeof(int), NULL);
		recv(connection, (char*)&cc.col, sizeof(int), NULL);

		data[i].col = cc.col;
		data[i].row = cc.row;
	}
}

void getServerMsg() {

	int size;
	dataType dt;
	Cell* map = nullptr, *oppChoices = nullptr, *myChoices = nullptr;
	

	while (1)
	{
		recv(connection, (char*)&dt, sizeof(int), NULL);
		recv(connection, (char*)&size, sizeof(int), NULL);

		switch (dt)
		{
		case ARRAY:
		{
			// Map
			map = new Cell[size];
			getMap(map, size);

			// opponent choices
			int opp_size;
			recv(connection, (char*)&opp_size, sizeof(int), NULL);
			oppChoices = new Cell[opp_size];
			getChoices(oppChoices, opp_size);

			// My choices
			int my_size;
			recv(connection, (char*)&my_size, sizeof(int), NULL);
			myChoices = new Cell[my_size];
			getChoices(myChoices, my_size);

			break;
		}
		case VAR:
		{
			gameInfo gi;
			char* buf = new char[size + 1];
			buf[size] = '\0';
			recv(connection, buf, size, NULL);

			gi.map = map;
			gi.my_targets = myChoices;
			gi.opp_targets = oppChoices;
			gi.my_last_target = myChoices[0];
			gi.opp_last_target = oppChoices[0];


			AI ttt_game;
			Cell answer = ttt_game.gameLogic(gi); // tic tac toe game

			string row = std::to_string(answer.row),
				col = std::to_string(answer.col);

			cout << " row : " << row << " - " << " col : " << col << endl;

			sendMsg(row);
			sendMsg(col);

			delete[] map;
			delete[] oppChoices;
			delete[] myChoices;
			delete[] buf;

			break;
		}

		default: 
			cout << " server and client didn't synchronize " << endl;
			return;
		}

	}

}


int _tmain(int argc, _TCHAR* argv[])
{
	// socket options
	WSAData wsaData;
	WORD DllVersion;
	if (!socketInitiaion(wsaData, DllVersion))
		return 0;


	// adress to be binded to socket
	SOCKADDR_IN addr;
	SOCKET sListen;
	int sizeOfAddr = sizeof(addr);
	addrAndSockBinder(addr, sListen);

	connection = socket(AF_INET, SOCK_STREAM, NULL);

	if (connect(connection, (SOCKADDR*)&addr, sizeOfAddr))
	{
		cout << "client : connection Failed " << endl;
		return 0;
	}

	HANDLE threadHDL = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)getServerMsg, NULL, NULL, NULL);

	WaitForSingleObject(threadHDL, INFINITE);
	closesocket(connection);

	system("pause");
	return 0;

}

