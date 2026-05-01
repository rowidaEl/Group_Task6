#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std;

enum Difficulty { EASY, HARD };

class Board {
private:
    vector<vector<char>> grid;
    const int size;

public:
    Board(int size = 3) : size(size) {
        grid.resize(size, vector<char>(size, ' '));
    }


    void display() const;

    bool isValidMove(int row, int col) const;

    bool makeMove(int row, int col, char symbol);

    bool checkWin(char symbol) const;

    bool isFull() const;

    char getCell(int row, int col) const;

    void reset();

    int getSize() const;
};


class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol)
        : name(name), symbol(symbol) {}

    virtual void getMove(int& row, int& col) = 0;

    string getName() const;

    char getSymbol() const;

    void setName(const string& newName);

    virtual ~Player();
};


class HumanPlayer : public Player {
public:
     HumanPlayer(const string& name, char symbol)
        : Player(name, symbol) {}

    void getMove(int& row, int& col) override;
};


class AIPlayer : public Player {

private:
    Difficulty difficulty;

public:

     AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol), difficulty(difficulty) {}

    void setDifficulty(Difficulty newDifficulty);

    void getMove(int& row, int& col) override;

    void getRandomMove(const Board& board, int& row, int& col) const;

    int evaluateBoard(const Board& board) const{
        // Determine the opponent's symbol
    char oppSymbol = (symbol == 'X') ? 'O' : 'X';

    // If AI wins, return +10
    if (board.checkWin(symbol)) {
        return 10;
    }
    // If Opponent wins, return -10
    else if (board.checkWin(oppSymbol)) {
        return -10;
    }
    
    // Draw or ongoing game
    return 0;
    }

    int minimax(Board board, bool isMax) const{
        int score = evaluateBoard(board);

    // Terminal states (Win/Loss/Draw)
    if (score == 10) return score;
    if (score == -10) return score;
    if (board.isFull()) return 0;

    char oppSymbol = (symbol == 'X') ? 'O' : 'X';

    if (isMax) {
        int best = -1000;
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i, j) == ' ') {
                    Board nextBoard = board; 
                    nextBoard.makeMove(i, j, symbol);
                    best = std::max(best, minimax(nextBoard, !isMax));
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.getCell(i, j) == ' ') {
                    Board nextBoard = board;
                    nextBoard.makeMove(i, j, oppSymbol);
                    best = std::min(best, minimax(nextBoard, !isMax));
                }
            }
        }
        return best;
    }
    }

    void getBestMove(Board& board, int& row, int& col) const{
        int bestVal = -1000;
    row = -1;
    col = -1;

    for (int i = 0; i < board.getSize(); i++) {
        for (int j = 0; j < board.getSize(); j++) {
            if (board.getCell(i, j) == ' ') {
                Board nextBoard = board;
                nextBoard.makeMove(i, j, symbol);
                
                // AI just made a move, so next turn is the minimizer's turn (false)
                int moveVal = minimax(nextBoard, false);

                if (moveVal > bestVal) {
                    row = i;
                    col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    }

    void calculateMove(Board& board, int& row, int& col);
};


class Game {

private:

    Board board;

    Player* player1;
    Player* player2;

    Player* currentPlayer;

    bool vsAI;

    AIPlayer* ai;

public:

    Game();

    void showMenu();

    void setupPvP();

    void setupPvC(Difficulty diff);

    void switchPlayer();

    void handleHumanMove(Player* player);

    void handleAIMove(AIPlayer* aiPlayer);

    bool checkGameEnd(){
        if (board.checkWin(player1->getSymbol())) {
        board.display();
        std::cout << player1->getName() << " wins!" << std::endl;
        return true;
    } else if (board.checkWin(player2->getSymbol())) {
        board.display();
        std::cout << player2->getName() << " wins!" << std::endl;
        return true;
    } else if (board.isFull()) {
        board.display();
        std::cout << "It's a draw!" << std::endl;
        return true;
    }
    return false;
    }

    void reset(){
        board.reset();
        currentPlayer = player1;
    }

    void start(){
        showMenu(); // Setup the game mode (PvP or PvC)

    bool playing = true;
    while (playing) {
        reset(); 
        bool gameEnded = false;

        while (!gameEnded) {
            board.display();
            
            if (vsAI && currentPlayer == ai) {
                handleAIMove(ai);
            } else {
                handleHumanMove(currentPlayer);
            }

            gameEnded = checkGameEnd();
            
            if (!gameEnded) {
                switchPlayer();
            }
        }

        std::cout << "Would you like to play again? (y/n): ";
        char choice;
        std::cin >> choice;
        if (choice != 'y' && choice != 'Y') {
            playing = false;
        }
    }
    
    std::cout << "Thanks for playing!" << std::endl;
    }
};


int main() {

    Game game;

    game.start();

    return 0;
}
