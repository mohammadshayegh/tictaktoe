#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")

#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "SocketNetwork.h"
#include "tictactoe.h"

#define NUMOFCONNS 2

using namespace std;

vector<SOCKET> connections;
int newConnectionCounter = 0;

void sendToOtherClients(int index)
{
	while(true)
	{
		int size;
		recv(connections.at(index),(char*)&size,sizeof(int),NULL);
		char *sentMsg = new char[size+1];
		sentMsg[size] = '\0';
		recv(connections[index],sentMsg,size,NULL);
		cout << &sentMsg << endl;

		for(int i=0; i < newConnectionCounter; i++)
		{
			if(i == index)
				continue;

			send(connections[i],(char*)&size,sizeof(int),NULL);
			send(connections[i],sentMsg,size,NULL);
		}

		delete [size] sentMsg;
	}
}

void sendMsg(int socketID,string msg) {
	int size = msg.size();
	send(connections[socketID], (char*)&size, sizeof(int), NULL);
	send(connections[socketID], msg.c_str(), size, NULL);
}

string recvMsg(int socketID) 

{
	int size;
	recv(connections[socketID], (char*)&size, sizeof(int), NULL);

	char* buf = new char[size + 1];
	buf[size] = '\0';
	recv(connections[socketID], buf, size, NULL);

	string str = string(buf);
	return str;
}

int _tmain(int argc, _TCHAR* argv[])
{
	SocketNetwork sockSet;
	if( !sockSet.socketInitiation() )return 0;
	sockSet.addrAndSockBinder();

	for(int i=0; i<NUMOFCONNS; i++)
	{
		if(sockSet.server_newConnection())
		{
			connections = sockSet.getConnections();
			newConnectionCounter = sockSet.getNumOfCons();
			
			cout << "server : connected successfully " << endl;
		}
		else
		{
			cout << "server : Client connection to server Failed " << endl;
			return 0;
		}
	}


	cout << " two players connected succesfully ..." << endl;
	Sleep(250);
	cout << " Let's start it !" << endl;

	

	TicTacToe game;
	Cell target;
	
	do
	{
		do
		{
			int turn = game.getTurn()-1;
			sendMsg(turn, "Enter inputs ");
			target.row = atoi(recvMsg(turn).c_str());
			target.col = atoi(recvMsg(turn).c_str());

		} while (!game.markTarget(target.row, target.col));

		game.print();

	} while (game.noWinner() && !game.mapIsFull());

	system("pause");

	return 0;

}

