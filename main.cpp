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

    bool checkWin(char symbol) const
    {
        for(int i = 0 ; i < size ; i++)
        {

            bool rowWin = true;
            bool colWin = true;

            for(int j = 0 ; j < size ; j++)
            {

                if(grid[i][j] != symbol)
                    rowWin = false;
                if(grid[j][i] != symbol)
                    colWin = false ;
            }
            if(rowWin || colWin)
                return true;
        }
        bool diag1 = true;
        bool diag2 = true;

        for(int i = 0 ; i < size;i++)
        {

            if(grid[i][i] != symbol)
                diag1 = false;
            if(grid[i][size-i-1] != symbol)
                diag2 = false;
        }
        return diag1 || diag2;

    }

    bool isFull() const
    {
        for(auto &row : grid)
        {
            for(auto &cell: row)
                if(cell == ' ')
                return false;
        }
        return true;
    }

    char getCell(int row, int col) const
    {
        return grid[row][col];
    }

    void reset();

    int getSize() const
    {
        return size;
    }
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

    char getSymbol() const
    {
        return symbol;
    }

    void setName(const string& newName);

    virtual ~Player() {}
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

    int evaluateBoard(const Board& board) const;

    int minimax(Board board, bool isMax) const;

    void getBestMove(Board& board, int& row, int& col) const;

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

    Game()
    {
        player1 = nullptr;
        player2 = nullptr;
        currentPlayer = nullptr;
        ai = nullptr;
        vsAI = false;
    }

    void showMenu()
    {
        cout << "\nTIC-TAC-TOE GAME\n";
        cout << "================\n";
        cout << "1. Player vs Player \n";
        cout << "2. Player vs Computer (Easy)\n";
        cout << "3. Player vs Computer (Hard)\n";
        cout << "4. Exit\n";


    }

    void setupPvP();

    void setupPvC(Difficulty diff);

    void switchPlayer();

    void handleHumanMove(Player* player);

    void handleAIMove(AIPlayer* aiPlayer)
    {
        int row;
        int col;
        aiPlayer->calculateMove(board,row,col);
        board.makeMove(row,col,aiPlayer->getSymbol());
        cout << "Computer Played: " << row+1 << " " << col+1 << endl;
    }

    bool checkGameEnd();

    void reset();

    void start();
};


int main() {

    Game game;

    game.start();

    return 0;
}
