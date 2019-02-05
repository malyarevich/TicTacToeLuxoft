#include "pch.h"
#include <iostream>
#include <algorithm>
#include "TicTacToeGame.h"
//#include <CTime>

// '0' same the 'O' and '1' same the 'X'
// '1' same the 'C' and '2' same the 'H'
TicTacToeGame::TicTacToeGame(char player1, char mode, bool isPlayer1First) {
    player1_ = convertPlayer(player1);
    player2_ = invertPlayer(player1);
    bool isVersusAi = mode == '1' || mode == 'c';

    if (isVersusAi) {
        mode_ = '1';
        playerTitle1_ = "Human";
        playerTitle2_ = "AI";
    } 
    else {
        mode_ = '2';
        playerTitle1_ = "Player 1";
        playerTitle2_ = "Player 2";
    }

    turn_ = 0;
    isP1First_ = isPlayer1First;
    last_ = { 0, 0 };

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board_[i][j] = 0;
        }
    }
}

TicTacToeGame::~TicTacToeGame() {

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

//static

const std::vector<int> TicTacToeGame::RAYS_OF_CELLS[3][3] = {
    { { 0, 1, 2 }, { 0, 3 }, { 0, 4, 7 }, }, // _|_|_
    { { 1, 5 }, { 2, 3, 5, 7 }, { 4, 5 }, }, // _|_|_
    { { 1, 6, 7 }, { 3, 6 }, { 2, 4, 6 }, }, // _|_|_
};

//static
const int TicTacToeGame::RAYS[8][3][2] = {
    { {0, 0}, { 0,1 }, { 0,2 }, }, //0 -
    { {0, 0}, { 1,0 }, { 2,0 }, }, //1 |
    { {0, 0}, { 1,1 }, { 2,2 }, }, //2 /
    { {0, 1}, { 1,1 }, { 2,1 }, }, //3 |
    { {0, 2}, { 1,2 }, { 2,2 }, }, //4 |
    { {1, 0}, { 1,1 }, { 1,2 }, }, //5 -
    { {2, 0}, { 2,1 }, { 2,2 }, }, //6 -
    { {2, 0}, { 1,1 }, { 0,2 }, }, //7 /
};

//static
const char TicTacToeGame::X_O_SYMBOLS[5] = { '_', 'X', ' ', '_', 'O' };

int TicTacToeGame::checkWin() {
    for (int i : RAYS_OF_CELLS[last_.x][last_.y]) {
        int sum = board_[RAYS[i][0][0]][RAYS[i][0][1]]
                + board_[RAYS[i][1][0]][RAYS[i][1][1]]
                + board_[RAYS[i][2][0]][RAYS[i][2][1]];
        bool isWinSum = sum == 3 || sum == 12;

        if (isWinSum) {
            return sum;
        }
    }

    return 0;
}

void TicTacToeGame::printBoard() {
    for (int i = 0; i < 3; i++) {
        if (i != 2) {
            std::cout << "\n\t\t _";
        } 
        else {
            std::cout << "\n\t\t  ";
        }
        for (int j = 0; j < 3; j++) {
            std::string subline = "_|_";

            if (j == 2) {
                if (i == 2) {
                    subline = " ";
                } 
                else {
                    subline = "_";
                }
            } 
            else if (i == 2) {
                subline = " | ";
            }
            bool isEmptyBottomCell = board_[i][j] == 0 && i == 2;

            if (isEmptyBottomCell) {
                std::cout << " " << subline;
            } 
            else {
                std::cout << X_O_SYMBOLS[board_[i][j]] << subline;
            }
        }
    }
}
bool TicTacToeGame::gameOver() {
    if (turn_ > 4) {
        if (checkWin()) {
            return true;
        }
    }

    if (turn_ < 9) {
        return false;
    }

    return true;
}

int TicTacToeGame::evaluateScore() {
    int lineSum = checkWin();
    bool isPlayer1Win = lineSum == 3 * player1_;
    bool isPlayer2Win = lineSum == 3 * player2_;

    if (isPlayer1Win) {
        return 10; //Human win
    } 
    else if (isPlayer2Win) {
        bool isNextMoveWinning = turn_ - lastTurn_ == 1;
        return (isNextMoveWinning ? - 1000 : -1) * 10; //AI win
    }

    return 0; //Tie
}

Move TicTacToeGame::minimax() {
    lastTurn_ = turn_;
    int bestMoveScore = 1000;
    Move bestMove;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {

            if (board_[i][j] == 0) {
                board_[i][j] = player2_;
                last_.x = i;
                last_.y = j;
                turn_++;
                int tempMoveScore = maxSearch();

                if (tempMoveScore <= bestMoveScore) {
                    bestMoveScore = tempMoveScore;
                    bestMove.x = i;
                    bestMove.y = j;
                }
                board_[i][j] = 0;
                turn_--;
            }
        }
    }

    return bestMove;
}

int TicTacToeGame::maxSearch() {
    bool isGameOver = turn_ > 4 && gameOver();

    if (isGameOver) {
        return evaluateScore();
    }

    int bestMoveScore = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_[i][j] == 0) {
                board_[i][j] = player1_;
                last_.x = i;
                last_.y = j;
                turn_++;
                int tempMoveScore = minSearch();

                if (tempMoveScore >= bestMoveScore) {
                    bestMoveScore = tempMoveScore;
                }
                board_[i][j] = 0;
                turn_--;
            }
        }
    }

    return bestMoveScore;
}
int TicTacToeGame::minSearch() {
    bool isGameOver = turn_ > 4 && gameOver();

    if (isGameOver) {
        return evaluateScore();
    }

    int bestMoveScore = 1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board_[i][j] == 0) {
                board_[i][j] = player2_;
                last_.x = i;
                last_.y = j;
                turn_++;
                int tempMove = maxSearch();

                if (tempMove <= bestMoveScore) {
                    bestMoveScore = tempMove;
                }

                board_[i][j] = 0;
                turn_--;
            }
        }
    }

    return bestMoveScore;
}

void TicTacToeGame::askHumanMove(int player) {
    int x = -INT8_MAX,
        y = -INT8_MAX;
    bool isMoveMakeSense;
    bool isSkipAfterFirst = false;

    do {
        if (isSkipAfterFirst) {
                std::cout << "\t   _____________________________\n";
                std::cout << "\t   |        Incorrect:         |\n";
                std::cout << "\t   |---------------------------|\n";

            bool isRowMiss = x < 0 || x > 2;

            if (isRowMiss) {
                std::cout << "\t   | * Row is not existing!    |\n";
            }

            bool isColumnMiss = y < 0 || y > 2;

            if (isColumnMiss) {
                std::cout << "\t   | * Column is not existing! |\n";
            }

            bool isCellOccupied = !isRowMiss && !isColumnMiss &&
                                  (board_[x][y] != 0);

            if (isCellOccupied) {
                std::cout << "\t   | * This cell is not empty! |\n";
            }
                std::cout << "\t   |---------------------------|\n";
                std::cout << "\t   |     Please try again.     |\n";
                std::cout << "\t   |___________________________|" << std::endl;
        } 
        else {
            isSkipAfterFirst = true;
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
        isMoveMakeSense = x < 0 || x > 2 || y < 0 || y > 2 ||
                          board_[x][y] != 0;
    } while (isMoveMakeSense);

    board_[x][y] = player;
    last_.x = x;
    last_.y = y;
}

void TicTacToeGame::play() {
    std::string curMove;
    std::cout << "\n\t\tGood luck, have fun!" << std::endl;
    printBoard();
    std::cout << "\n  ( Enter your move, e.g. Row: 1, Column: 3. )" << 
                 std::endl;
    //time_t seconds1;
    int lineSum;
    bool isGameContinue = turn_ < 5 || !gameOver();

    while (isGameContinue) {
        //seconds1 = time(0);
        std::cout << "\n-------------------------------------------------" <<
                     std::endl;
            
        bool isTurnPlayer1 = turn_ % 2 == (isP1First_ ? 0 : 1);

        if (isTurnPlayer1) {
            curMove = playerTitle1_;
            std::cout << "\t\t @ " << curMove << " Move " << std::endl;
            askHumanMove(player1_);
        }
        else {
            curMove = playerTitle2_;
            std::cout << "\t\t @ " << curMove << " Move " << std::endl;

            if (mode_ == '1') {
                Move AImove = minimax();
                board_[AImove.x][AImove.y] = player2_;
                last_ = AImove;

                std::cout << "\tRow: " << (last_.x + 1) << "\n\tColumn: " <<
                             (last_.y + 1) << std::endl;
            } 
            else {
                askHumanMove(player2_);
            }
        }

        printBoard();
        //std::cout << "\t" << curMove << " time: " << (time(0) - seconds1) << 
        //             "s." << std::endl;
        lineSum = checkWin();
        turn_++;
        isGameContinue = turn_ < 5 || !gameOver();
    }
    std::cout << "\n-------------------------------------------------" <<
                 std::endl;
    bool isGameWin = lineSum == 3 || lineSum == 12;

    if (isGameWin) {
        std::cout << "\n\t    `*~=. " << curMove << " Wins .=~*`" << std::endl;
        isP1Won_ = curMove == playerTitle1_;
    } 
    else if (turn_ == 9) {
        std::cout << "\n\t\t   `~. Tie .~`" << std::endl;
    }

    std::cout << "\n=================================================" <<
                 std::endl;

}
void TicTacToeGame::reset() {
    turn_ = 0;
    isP1First_ = isP1Won_;
    last_ = { 0, 0 };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board_[i][j] = 0;
        }
    }
}