#pragma once
#include <vector>
#include <array>
#include <string>

const std::vector<int> raysOfCells[3][3] = {
	{ {0, 1, 2}, { 0,3 }, { 0,4,7 }, }, // _|_|_
	{ {1, 5}, { 2,3,5,7 }, { 4,5 }, },	// _|_|_
	{ {1, 6, 7}, { 3,6 }, { 2,4,6 }, }, // _|_|_
};

const int rays[][3][2] = {
	{ {0, 0}, { 0,1 }, { 0,2 }, }, //0 -
	{ {0, 0}, { 1,0 }, { 2,0 }, }, //1 |
	{ {0, 0}, { 1,1 }, { 2,2 }, }, //2 /
	{ {0, 1}, { 1,1 }, { 2,1 }, }, //3 |
	{ {0, 2}, { 1,2 }, { 2,2 }, }, //4 |
	{ {1, 0}, { 1,1 }, { 1,2 }, }, //5 -
	{ {2, 0}, { 2,1 }, { 2,2 }, }, //6 -
	{ {2, 0}, { 1,1 }, { 0,2 }, }, //7 /
};

const std::array<char, 5> XOSymbols{ 
	{'_', 'X', ' ', ' ', 'O'} 
};

struct Move {
	int x;
	int y;
};

class TicTacToeGame
{
public:
	TicTacToeGame(char inplayer1, char inmode, bool isP1First);
	~TicTacToeGame();
	static int convertPlayer(char player);
	static int invertPlayer(char player);
	void play();
	void reset();
private:
	int turn, lastTurn;
	bool isP1First, isP1Won;
	char mode;
	int player1, player2;
	std::string playerTitle1, playerTitle2;
	int board[3][3];
	Move last;

	int checkToWin();
	void printBoard();
	bool gameOver();
	int score();
	Move minimax();
	int maxSearch();
	int minSearch();
	void getHumanMove(int player);
};

