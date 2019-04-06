#ifndef TicTacToe_H
#define TicTacToe_H

#include <iostream>
using namespace std;

struct Cell {
	int row;
	int col;
};

class TicTacToe
{
private:
	int map[3][3];
	int turn = 1;

	void setTurn();
	bool validCell(Cell target);
	Cell getTargetsFromClient();
public:
	TicTacToe() :map{ 0 } {}
	int  winner();
	int  getTurn();
	bool noWinner();
	bool mapIsFull();
	void print();
	bool markTarget(Cell target);
	bool markTarget(int row, int col);
	void startGame();
};


#endif // TicTacToe_H
