#include "stdafx.h"
#include "AI.h"

Cell AI::gameLogic(gameInfo &game)
{
	Cell answer;

	cout << "row " << game.map[5].col << endl;

	answer.col = rand() % 3;
	answer.row = rand() % 3;

	return answer;
}
