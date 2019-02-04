
#include "pch.h"
#include <iostream>
#include <string>

#include "TicTacToeGame.h"

// For transforming to lowercase
char easyToLower(char in) {
    if (in <= 'Z' && in >= 'A') {
        return in - ('Z' - 'z');
    }

    return in;
}

void chooseMode(char &mode) {
    std::string in;
    bool isInputMakeSense;

    do {
        system("CLS");
        std::cout << "\n\n\t\t\tHello there :)" <<
                     "\n\t\tLet us start playing Tic-Tac-Toe!" <<
                     "\n\tDo you want to play versus (C)omputer or (H)uman?" <<
                     "\n\t\t(C)omputer - 1 or (H)uman - 2\n\n\t\t\t\t";
        std::getline(std::cin, in);
        in = easyToLower(in[0]);
        isInputMakeSense = in[0] != 'c' && in[0] != 'h' && in[0] != '1' &&
                           in[0] != '2';
    } while (isInputMakeSense);

    bool isVersusComputer = in[0] == '1' || in[0] == 'C';

    if (isVersusComputer) {
        mode = '1';
    } 
    else {
        mode = '0';
    }
}

void chooseXo(char &player1) {
    std::string in;
    bool isInputMakeSense;
    
    do {
        system("CLS");
        std::cout << "\n\n\t\tChoose your symbol:" <<
                     "\n\t\t(O) - 0 or (X) - 1 \n\n\t\t\t";
        std::getline(std::cin, in);
        in = easyToLower(in[0]);
        isInputMakeSense = in[0] != 'x' && in[0] != 'o' && in[0] != '0' &&
                           in[0] != '1';
    } while (isInputMakeSense);

    bool isChoseX = in[0] == 'x' || in[0] == '1';
    
    if (isChoseX) {
        player1 = '1';
    } 
    else {
        player1 = '0';
    }
}

bool chooseStep() {
    std::string in;
    bool isInputMakeSense;
    
    do {
        system("CLS");
        std::cout << "\n\n\t\tWill Player 1 go first?" <<
                     "\n\t\t\t(Y)es - 1 \n\t\t\t(N)o - 0 \n\n\t\t\t";
        std::getline(std::cin, in);
        in = easyToLower(in[0]);
        isInputMakeSense = in[0] != 'y' && in[0] != 'n' && in[0] != '1' &&
                           in[0] != '0';
    } while (isInputMakeSense);

    bool isPlayer1First = in[0] == 'x' || in[0] == '1';
    
    if (isPlayer1First) {
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
    std::cout << "\n\n\tNice, Player 1 chose - " << showToXO(player1) << 
                 "\n\tAnd Player 1 will go " <<
                 (isP1First ? "first.\n" : "second.\n");
}

bool choosePlayAgain() {
    std::string in;
    bool isInputMakeSense;

    do {
        std::cout << "\n\t\t  Play Again? \n\t\t   (Y)es - 1" <<
                     "\n\t\t    (N)o - 0\n\n\t\t\t";
        std::cin >> in;
        in = easyToLower(in[0]);
        isInputMakeSense = in[0] != 'y' && in[0] != 'n' && in[0] != '1' &&
                           in[0] != '0';
    } while (isInputMakeSense);

    bool isPlayAgain = in[0] == 'y' || in[0] == '1';

    if (isPlayAgain) {
        system("CLS");
        return true;
    }

    return false;
}
int main() {
    char mode = 0;
    chooseMode(*&mode);
    char player1 = 0;
    chooseXo(*&player1);
    bool isPlayer1First = 0;
    isPlayer1First = chooseStep();
    showChoose(*&player1, *&isPlayer1First);
    TicTacToeGame Game(player1, mode, isPlayer1First);
    bool isPlay;
    do {
        Game.play();
        isPlay = choosePlayAgain();

        if (isPlay) {
            Game.reset();
        }
    } while (isPlay);
}
