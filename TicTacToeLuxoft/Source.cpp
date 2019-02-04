// TicTacToeLuxoft.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <string>

//custom h file
#include "TicTacToeGame.h"

// For transforming to lowercase
char easyToLower(char in) {
	if (in <= 'Z' && in >= 'A')
		return in - ('Z' - 'z');
	return in;
}

void chooseMode(char &mode) {
	std::string inp = " ";
	while (inp[0] != 'c' && inp[0] != 'h' && inp[0] != '1' && inp[0] != '2')
	{
		system("CLS");
		std::cout << "\n\n\t\t\tHello there :)\n\t\tLet us start playing Tic-Tac-Toe!" << std::endl;
		std::cout << "\tDo you want to play versus (C)omputer or (H)uman?" 
			<< "\n\t\t(C)omputer - 1 or (H)uman - 2" << std::endl;
		std::cout << "\n\t\t\t\t";
		std::getline(std::cin, inp);
		inp = easyToLower(inp[0]);
	}
	if (inp[0] == '1' || inp[0] == 'C') {
		mode = '1';
	} else {
		mode = '0';
	}
}

void chooseXO(char &player1) {
	std::string inp = " ";
	while (inp[0] != 'x' && inp[0] != 'o' && inp[0] != '0' && inp[0] != '1')
	{
		system("CLS");
		std::cout << "\n\n\t\tChoose your symbol:"
			<<"\n\t\t(O) - 0 or (X) - 1" << std::endl;
		std::cout << "\n\t\t\t";
		std::getline(std::cin, inp);
		inp = easyToLower(inp[0]);
	}
	if (inp[0] == 'x' || inp[0] == '1') {
		player1 = '1';
	} else {
		player1 = '0';
	}
}

bool chooseStep() {
	std::string inp = " ";
	while (inp[0] != 'y' && inp[0] != 'n' && inp[0] != '1' && inp[0] != '0') {
		system("CLS");
		std::cout << "\n\n\t\tWill Player 1 go first?"
			<< "\n\t\t\t(Y)es - 1"
			<< "\n\t\t\t(N)o - 0" << std::endl;
		std::cout << "\n\t\t\t";

		std::getline(std::cin, inp);
		inp = easyToLower(inp[0]);
	}
	if (inp[0] == 'x' || inp[0] == '1') {
		return true;
	}
	return false;
}

//Convert player to X('1') or O('0')
char showToXO(char in) {
	if (in == '1') {
		return 'X';
	}
	return 'O';
}

void showChoose(char &player1, bool &isP1First) {
	system("CLS");
	std::cout << "\n\n\tNice, Player 1 chose - " << showToXO(player1) << std::endl;
	std::cout << "\tAnd Player 1 will go " << (isP1First ? "first." : "second.") << std::endl;
}

bool choosePlay(TicTacToeGame &Game) {
	std::string inp = " ";
	while (inp[0] != 'y' && inp[0] != 'n' && inp[0] != '1' && inp[0] != '0') {
		std::cout << "\n\t\t  Play Again?" << "\n\t\t   (Y)es - 1" << "\n\t\t    (N)o - 0\n";
		std::cout << "\n\t\t\t";
		std::cin >> inp;
		inp = easyToLower(inp[0]);
	}

	if (inp[0] == 'y' || inp[0] == '1') {
		system("CLS");
		return true;
	}
	return false;
}
int main()
{
	char mode = 0;
	char player1 = 0;
	bool isP1First = 0, isNotExit = true;

	chooseMode(*&mode);
	chooseXO(*&player1);
	isP1First = chooseStep();
	showChoose(*&player1, *&isP1First);
	TicTacToeGame Game(player1, mode, isP1First);
	while (isNotExit) {
		Game.play();
		if (isNotExit = choosePlay(Game)) {
			Game.reset();
		}
	 }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
