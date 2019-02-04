#include "pch.h"
#include <iostream>
#include <algorithm>
#include "TicTacToeGame.h"
#include <CTime>

// '0' same the 'O' and '1' same the 'X'
// '1' same the 'C' and '2' same the 'H'
TicTacToeGame::TicTacToeGame(char inPlayer1, char inMode, bool inIsP1First)
{
	player1 = convertPlayer(inPlayer1);
	player2 = invertPlayer(inPlayer1);
	if (inMode == '1' || inMode == 'c') {
		mode = '1';
		playerTitle1 = "Human";
		playerTitle2 = "AI";
	} else {
		mode = '2';
		playerTitle1 = "Player 1";
		playerTitle2 = "Player 2";
	}
	std::string playerTitle1, playerTitle2;
	turn = 0;
	isP1First = inIsP1First;
	last = { 0, 0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}


TicTacToeGame::~TicTacToeGame()
{
}

//static '0' -> 4 or '1'(any) -> 1;
int TicTacToeGame::convertPlayer(char player) {
	if (player == '0') {
		return 4;
	}
	return 1;
}

//static '0' -> 1 or '1'(any) -> 4;
int TicTacToeGame::invertPlayer(char player) {
	if (player == '0') {
		return 1;
	}
	return 4;
}

int TicTacToeGame::checkToWin() {
	for (int i : raysOfCells[last.x][last.y]) {
		int sum = board[rays[i][0][0]][rays[i][0][1]]
				+ board[rays[i][1][0]][rays[i][1][1]]
				+ board[rays[i][2][0]][rays[i][2][1]];
		if (sum == 3 || sum == 12) {
			return sum;
		}
	}
	return 0;
}

void TicTacToeGame::printBoard() {
	for (int i = 0; i < 3; i++) {

		if (i != 2) {
			std::cout << "\n\t\t _";
		} else {
			std::cout << "\n\t\t  ";
		}
		for (int j = 0; j < 3; j++) {
			std::string subline = "_|_";
			if (j == 2) {
				if (i == 2) {
					subline = " ";
				} else {
					subline = "_";
				}
			} else if (i == 2) {
				subline = " | ";
			}
			if (board[i][j] == 0 && i == 2) {
				std::cout << " " << subline;
			} else {
				std::cout << XOSymbols.at(board[i][j]) << subline;
			}
		}
	}
}
bool TicTacToeGame::gameOver() {
	if (turn > 4) {
		if (checkToWin()) {
			return true;
		}
	}	
	if (turn < 9) {
		return false;
	}
	return true;
}

int TicTacToeGame::score() {
	int lineSum = checkToWin();	
	if (lineSum == 3 * player1) {
		return 10; /*Human win*/
	} else if (lineSum == 3 * player2 ) {
		return (turn - lastTurn == 1 ? - 1000 : -1) * 10; /*AI win*/	
	}
	return 0; /*Tie*/
}

Move TicTacToeGame::minimax() {
	lastTurn = turn;
	int bestMoveScore = 1000;
	Move bestMove;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				board[i][j] = player2;
				last.x = i;
				last.y = j;
				turn++;
				int tempMoveScore = maxSearch();
				if (tempMoveScore <= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				board[i][j] = 0;
				turn--;
			}
		}
	}

	return bestMove;
}

int TicTacToeGame::maxSearch() {
	if (gameOver()) {
		return score();
	}
	Move bestMove;
	int bestMoveScore = -1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				board[i][j] = player1;
				last.x = i;
				last.y = j;
				turn++;
				int tempMoveScore = minSearch();
				if (tempMoveScore >= bestMoveScore) {
					bestMoveScore = tempMoveScore;
					bestMove.x = i;
					bestMove.y = j;
				}
				board[i][j] = 0;
				turn--;
			}
		}
	}

	return bestMoveScore;
}
int TicTacToeGame::minSearch() {
	if (gameOver()) {
		return score();
	}
	Move bestMove;
	int bestMoveScore = 1000;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == 0) {
				board[i][j] = player2;
				last.x = i;
				last.y = j;
				turn++;
				int tempMove = maxSearch();
				if (tempMove <= bestMoveScore) {
					bestMoveScore = tempMove;
					bestMove.x = i;
					bestMove.y = j;
				}
				board[i][j] = 0;
				turn--;
			}
		}
	}

	return bestMoveScore;
}

void TicTacToeGame::getHumanMove(int player) {
	int x = -INT_MAX, y = -INT_MAX;
	while (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != 0) {
		if (x != -INT_MAX && y != -INT_MAX) {
				std::cout << "\t   _____________________________" << std::endl;
				std::cout << "\t   |        Incorrect:         |" << std::endl;
				std::cout << "\t   |---------------------------|" << std::endl;
			if (x < 0 || x > 2) {
				std::cout << "\t   | * Row is not existing!    |" << std::endl;
			}
			if (y < 0 || y > 2) {
				std::cout << "\t   | * Column is not existing! |" << std::endl;
			}
			if (!(x < 0 || x > 2) && !(y < 0 || y > 2) && board[x][y] != 0) {
				std::cout << "\t   | * This cell is not empty! |" << std::endl;
			}
				std::cout << "\t   |---------------------------|" << std::endl;
				std::cout << "\t   |     Please try again.     |" << std::endl;
				std::cout << "\t   |___________________________|" << std::endl;
		}
		std::cout << "\tRow: "; //x
		std::cin >> x;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
		}
		std::cout << "\tColumn: "; //y
		std::cin >> y;
		if (!std::cin) {
			std::cin.clear();
			std::cin.ignore(200, '\n');
		}
		x--;
		y--;
	}
	board[x][y] = player;
	last.x = x;
	last.y = y;
}

void TicTacToeGame::play() {
	time_t seconds1, seconds2;
	std::string curMove;
	std::cout << "\n\t\tGood luck, have fun!" << std::endl;
	printBoard();
	std::cout << "\n  ( Enter your move, e.g. Row: 1, Column: 3. )" << std::endl;
	int lineSum = 0;
	while (turn < 5 || !gameOver()) {
		seconds1 = time(0);
		std::cout << "\n-------------------------------------------------" << std::endl;
		if (turn % 2 == (0 + !isP1First)) {
			curMove = playerTitle1;
			std::cout << "\t\t @ " << curMove << " Move " << std::endl;
			getHumanMove(player1);
		}
		else {
			curMove = playerTitle2; 
			std::cout << "\t\t @ " << curMove << " Move " << std::endl;
			if (mode == '1') {
				//Move AImove = (turn == 0) ? Move({ 1, 1 }) : minimax();
				Move AImove = minimax(); //Save 1 second
				board[AImove.x][AImove.y] = player2;
				last = AImove;

				std::cout << "\tRow: " << (last.x + 1) << "\n\tColumn: " << (last.y + 1) << std::endl;
			} else {
				getHumanMove(player2);
			}
		}
		seconds2 = time(0);
		printBoard();
		std::cout << "\t" << curMove << " time: " << (seconds2 - seconds1) << "s." << std::endl;
		lineSum = checkToWin();
		turn++;
	}
	std::cout << "\n-------------------------------------------------" << std::endl;
	if (lineSum == 3 || lineSum == 12) {
		std::cout << "\n\t    `*~=. " << curMove << " Wins .=~*`" << std::endl;
		isP1Won = curMove == playerTitle1;
	} else if (turn == 9) {
		std::cout << "\n\t\t   `~. Tie .~`" << std::endl;
	}
	std::cout << "\n=================================================" << std::endl;

}
void TicTacToeGame::reset() { 
	turn = 0;
	isP1First = isP1Won;
	last = { 0, 0 };

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = 0;
		}
	}
}