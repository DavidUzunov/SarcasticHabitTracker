#include <iostream>
#include <vector>
#include <limits>
#include <string>
#include <climits>

void erase(int lines);

class TicTacToe {
public:
    TicTacToe();
    void playGame();
    
private:
    char board[3][3];
    const char PLAYER = 'O';
    const char COMPUTER = 'X';
    const char EMPTY = ' ';
    
    void printBoard();
    bool isBoardFull();
    bool isWinner(char player);
    int minimax(bool isMaximizing);
    int bestMove();
    void playerMove();
    void computerMove();
};

TicTacToe::TicTacToe() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = EMPTY;
        }
    }
}

void TicTacToe::printBoard() {
    std::cout << "Current board state:\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j];
            if (j < 2) std::cout << "|";
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "-----\n";
    }
}

bool TicTacToe::isBoardFull() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                return false;
            }
        }
    }
    return true;
}

bool TicTacToe::isWinner(char player) {
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < 3; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || 
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}

int TicTacToe::minimax(bool isMaximizing) {
    if (isWinner(COMPUTER)) {
        return 1;
    }
    if (isWinner(PLAYER)) {
        return -1;
    }
    if (isBoardFull()) {
        return 0;
    }

    if (isMaximizing) {
        int best = std::numeric_limits<int>::min();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = COMPUTER;
                    best = std::max(best, minimax(false));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    } else {
        int best = std::numeric_limits<int>::max();
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == EMPTY) {
                    board[i][j] = PLAYER;
                    best = std::min(best, minimax(true));
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

int TicTacToe::bestMove() {
    int bestVal = std::numeric_limits<int>::min();
    int moveRow = -1;
    int moveCol = -1;

    // Try every cell to find the best move
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == EMPTY) {
                board[i][j] = COMPUTER;
                int moveVal = minimax(false);
                board[i][j] = EMPTY;

                if (moveVal > bestVal) {
                    moveRow = i;
                    moveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    return moveRow * 3 + moveCol; // Return move in index form (row * 3 + col)
}

void TicTacToe::playerMove() {
    int row = INT_MIN, col = INT_MIN;
    std::cout << "Your turn! Enter row and column from top left (1-3): ";
    std::string input;
    std::getline(std::cin, input);
    for(char x : input){
	    if(isdigit(x) && row == INT_MIN){
		    row = x - '0';
	    }
	    else if(isdigit(x) && col == INT_MIN){
		    col = x - '0';
	    }
    }

    while (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != EMPTY) {
	std::cout << "Invalid move! Try again.\n";
	std::getline(std::cin, input);
	row = INT_MIN, col = INT_MIN;
	for(char x : input){
        if(isdigit(x) && row == INT_MIN){
                row = x - '0';
        }
        else if(isdigit(x) && col == INT_MIN){
                col = x - '0';
        }
    }
	erase(2);
    }
    board[--row][--col] = PLAYER;
}

void TicTacToe::computerMove() {
    std::cout << "Opponent's turn...\n";
    int move = bestMove();
    board[move / 3][move % 3] = COMPUTER;
    int j = 1+move/8;
    for(int i = 0; i < 2000000000*j; i++){
	    i/3%92;
    }
}

void TicTacToe::playGame() {
    std::cout << "Welcome to Tic Tac Toe drinking edition!\nRules:\nYou will be matched against random players.\nThe loser has to take a shot\nIn the case of a draw, both players have to take a shot.\nOnly winners start their next game.\n\n";
    printBoard();
    while (true) {
        computerMove();
	erase(7);
	printBoard();

        if (isWinner(COMPUTER)) {
            std::cout << "Opponent wins! Take a shot.\n";
            break;
        }

        if (isBoardFull()) {
            std::cout << "It's a draw! Both players take a shot.\n";
            break;
        }

        playerMove();
        erase(7);
	printBoard();

        if (isWinner(PLAYER)) {
            std::cout << "You win! Unfortunately for your liver, this shouldn't ever happen.\n";
            break;
        }

        if (isBoardFull()) {
            std::cout << "It's a draw! Both players take a shot.\n";
            break;
        }
    }
}

int main(){
    TicTacToe game;
    game.playGame();
    return 0;
}

void erase(int lines){
	for(int i = 0; i < lines; i++){
		std::cout << "                                                                                                 \033[F";
	}
}
