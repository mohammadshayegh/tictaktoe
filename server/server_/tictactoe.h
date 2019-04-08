#ifndef TicTacToe_H
#define TicTacToe_H

#include <iostream>
#include <vector>
using namespace std;

struct Cell {
	int row;
	int col;
	int val;
};

class TicTacToe
{
private:
	int map[3][3];
	int turn = 1;
	vector<Cell> choices[2];

	void setTurn();
	void addChoice(Cell target);
	bool validCell(Cell target);
	Cell getTargetsFromClient();
public:
	TicTacToe() :map{ 0 } {}

	int  winner();
	int  getTurn();
	int getOppTurn();
	bool noWinner();
	bool mapIsFull();
	void print();
	void startGame();

	bool markTarget(Cell target);
	bool markTarget(int row, int col);
	vector<Cell> getChoices();
	vector<Cell> getOppChoices();
	vector<Cell> getMap();
};


#endif // TicTacToe_H
