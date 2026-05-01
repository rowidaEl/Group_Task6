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


    void display() const{
    cout << "\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " " << grid[i][j] << " ";
            if (j < size - 1) cout << "|";
        }
        cout << "\n";
        if (i < size - 1) {
            for (int j = 0; j < size; j++) {
                cout << "---";
                if (j < size - 1) cout << "+";
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

    bool isValidMove(int row, int col) const {
    return (row >= 0 && row < size &&
            col >= 0 && col < size &&
            grid[row][col] == ' ');
}

    bool makeMove(int row, int col, char symbol){
    if (isValidMove(row, col)) {
        grid[row][col] = symbol;
        return true;
    }
    return false;
}

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

    string getName() const{
    return name;
}

    char getSymbol() const
    {
        return symbol;
    }

    void setName(const string& newName){
    name=newName;
    }

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

    void switchPlayer(){

    if (currentPlayer == player1)
        currentPlayer = player2;
    else
        currentPlayer = player1;
}

    void handleHumanMove(Player* player){
    int row, col;

    while (true) {
        cout << player->getName() << " (" << player->getSymbol() << ") enter row and column: ";
        cin >> row >> col;

        // convert to 0-based index
        row--;
        col--;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Try again.\n";
            continue;
        }

        if (board.makeMove(row, col, player->getSymbol())) {
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}

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
