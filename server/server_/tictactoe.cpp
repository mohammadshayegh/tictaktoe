#include "stdafx.h"
#include "TicTacToe.h"

void TicTacToe::setTurn()
{
	if (turn == 1)
		turn++;
	else
		turn--;
}
bool TicTacToe::validCell(Cell target)
{
	if (target.col > 2 || target.row > 2 || map[target.row][target.col])
	{
		cout << " INVALID INPUT ! - it's " << getTurn() << "d gamer fault! " << endl;
		return 0;
	}
	return 1;
}
int  TicTacToe::winner()
{
	for (int j = 0; j < 3; j++)
	{
		if (map[0][j] == map[1][j] && map[0][j] == map[2][j] && map[0][j])
			return map[0][j];

		if (map[j][0] == map[j][1] && map[j][0] == map[j][2] && map[0][j])
			return map[j][0];
	}

	if (map[0][0] == map[1][1] && map[0][0] == map[2][2] && map[0][0])
		return map[0][0];

	if (map[2][0] == map[1][1] && map[2][0] == map[0][2] && map[2][0])
		return map[0][0];

	return 0;

}
bool TicTacToe::noWinner()
{
	int w = winner();
	if (w == 0)
		return 1;

	cout << " player " << w << " has won! " << endl;
	return 0;
}
bool TicTacToe::mapIsFull()
{
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (!map[i][j])
				return 0;

	return 1;
}
void TicTacToe::print()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << map[i][j] << "  ";
		cout << endl;
	}
}
bool TicTacToe::markTarget(Cell target)
{
	if (!validCell(target))
		return 0;

	map[target.row][target.col] = turn;
	addChoice(target);
	setTurn();

	return 1;
}
bool TicTacToe::markTarget(int row, int col)
{
	Cell tg;
	tg.col = col;
	tg.row = row;
	return markTarget(tg);
}
void TicTacToe::startGame()
{
	Cell target;

	do
	{
		do
		{
			target = getTargetsFromClient();
		} while (!markTarget(target.row, target.col));

		print();

	} while (noWinner() && !mapIsFull());
}
vector<Cell> TicTacToe::getChoices()
{
	return choices[turn-1];
}
void TicTacToe::addChoice(Cell target)
{
	choices[turn - 1].push_back(target);
}

vector<Cell> TicTacToe::getOppChoices()
{
	return choices[getOppTurn()];
}

vector<Cell> TicTacToe::getMap()
{
	vector<Cell> cells;
	Cell cell;
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) 
		{
			cell.row = i;
			cell.col = j;
			cell.val = map[i][j];
			cells.push_back(cell);
		}
	}
	return cells;
}
int  TicTacToe::getTurn()
{
	return turn;
}

int TicTacToe::getOppTurn()
{
	/*
		turn | index | opp index
		------------------------
		  1		 0		  1
		  2		 1		  0
	*/

	if (turn == 1)
		return 1;
	else
		return 0;
}

// user can change this function based on his requierments
Cell TicTacToe::getTargetsFromClient()
{
	Cell target;

	cout << "Enter row : ";
	cin >> target.row;
	cout << "Enter column : ";
	cin >> target.col;

	return target;
}
