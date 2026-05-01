#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>

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

// ==========================================
    // IMPLEMENTED: setDifficulty
    // ==========================================
    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    // ==========================================
    // IMPLEMENTED: getMove
    // ==========================================
    void getMove(int& row, int& col) override {
        // Dummy override since base Player::getMove lacks a Board reference.
        // The Game class should call calculateMove() to pass the board state.
        row = -1;
        col = -1;
    }

    // ==========================================
    // IMPLEMENTED: getRandomMove
    // ==========================================
    void getRandomMove(const Board& board, int& row, int& col) const {
        int size = board.getSize();
        do {
            row = rand() % size;
            col = rand() % size;
        } while (!board.isValidMove(row, col));
    }

    int evaluateBoard(const Board& board) const;

    int minimax(Board board, bool isMax) const;

    void getBestMove(Board& board, int& row, int& col) const;

    // ==========================================
    // IMPLEMENTED: calculateMove
    // ==========================================
    void calculateMove(Board& board, int& row, int& col) {
        if (difficulty == EASY) {
            getRandomMove(board, row, col);
        } else {
            getBestMove(board, row, col); 
        }
    }
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

    // ==========================================
    // IMPLEMENTED: setupPvP
    // ==========================================
    void setupPvP() {
        string name1, name2;
        cout << "Enter Player 1 (X) Name: ";
        cin >> name1;
        cout << "Enter Player 2 (O) Name: ";
        cin >> name2;
        
        player1 = new HumanPlayer(name1, 'X');
        player2 = new HumanPlayer(name2, 'O');
        
        currentPlayer = player1;
        vsAI = false;
    }

    // ==========================================
    // IMPLEMENTED: setupPvC
    // ==========================================
    void setupPvC(Difficulty diff) {
        string name;
        cout << "Enter Player (X) Name: ";
        cin >> name;
        
        player1 = new HumanPlayer(name, 'X');
        ai = new AIPlayer("Computer", 'O', diff);
        
        player2 = ai; 
        currentPlayer = player1; 
        vsAI = true;
    }

    void switchPlayer();

    void handleHumanMove(Player* player);

    void handleAIMove(AIPlayer* aiPlayer);

    bool checkGameEnd();

    void reset();

    void start();
};


int main() {

    Game game;

    game.start();

    return 0;
}
