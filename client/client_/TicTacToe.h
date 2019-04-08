#ifndef TicTacToe_H
#define TicTacToe_H

#include <iostream>
using namespace std;

struct Cell {
	int row;
	int col;
	int val;
	int n_val;
};

struct gameInfo {
	Cell *map;
	Cell *my_targets;
	Cell *opp_targets;
	Cell my_last_target;
	Cell opp_last_target;
};

enum dataType {
	ARRAY,
	VAR
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
