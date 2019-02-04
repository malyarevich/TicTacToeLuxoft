#pragma once
#ifndef COM_LUXOFT_GAME_TICTACTOEGAME_H
#define COM_LUXOFT_GAME_TICTACTOEGAME_H
#include <vector>
#include <string>

struct Move {
    int x;
    int y;
};

class TicTacToeGame
{
public:
    TicTacToeGame(char player1, char mode, bool isPlayer1First);
    ~TicTacToeGame();
    void play();
    void reset();

protected:
    const static std::vector<int> RAYS_OF_CELLS[3][3];
    const static int RAYS[8][3][2];
    const static char X_O_SYMBOLS[5];

private:
    int turn_, lastTurn_;
    bool isP1First_, isP1Won_;
    char mode_;
    int player1_, player2_;
    std::string playerTitle1_, playerTitle2_;
    int board_[3][3];
    Move last_;

    int convertPlayer(char player);
    int invertPlayer(char player);

    void askHumanMove(int player);
    void printBoard();
    int checkWin();
    bool gameOver();

    int evaluateScore();
    Move minimax();
    int maxSearch();
    int minSearch();

};

#endif // COM_LUXOFT_GAME_TICTACTOEGAME_H