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

    void reset() {
        for (auto &row : grid)
            for (auto &cell : row)
                cell = ' ';
    }

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

    void getMove(int& row, int& col) override {
        cout << name << " enter row and column (1-3): ";
        cin >> row >> col;

        row--;
        col--;
    }
};


class AIPlayer : public Player {

private:
    Difficulty difficulty;

public:

     AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol), difficulty(difficulty) {}

    void setDifficulty(Difficulty newDifficulty) {
        difficulty = newDifficulty;
    }

    void getMove(int& row, int& col) override {
        row = -1;
        col = -1;
    }

    void getRandomMove(const Board& board, int& row, int& col) const {
        int size = board.getSize();
        do {
            row = rand() % size;
            col = rand() % size;
        } while (!board.isValidMove(row, col));
    }

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

    void setupPvP()
       {

       board.reset();
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

    void setupPvC(Difficulty diff) {
          board.reset();
        string name;
        cout << "Enter Player (X) Name: ";
        cin >> name;

        player1 = new HumanPlayer(name, 'X');
        ai = new AIPlayer("Computer", 'O', diff);

        player2 = ai;
        currentPlayer = player1;
        vsAI = true;
    }

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

  void start() {

        srand(time(0));

        while (true) {

            showMenu();

            int choice;

            cout << "Select game mode: ";
            cin >> choice;

            if (choice == 4)
                break;

            if (choice == 1)
                setupPvP();

            else if (choice == 2)
                setupPvC(EASY);

            else if (choice == 3)
                setupPvC(HARD);

            else
                continue;

            bool playing = true;

            while (playing) {

                board.display();

                cout << currentPlayer->getName()
                     << "'s turn ("
                     << currentPlayer->getSymbol()
                     << ")\n";

                if (vsAI && currentPlayer == player2)
                    handleAIMove(ai);
                else
                    handleHumanMove(currentPlayer);

                if (checkGameEnd()) {

                    char again;

                    cout << "Play again? (y/n): ";
                    cin >> again;

                    if (again == 'y' || again == 'Y') {
                        reset();
                        continue;
                    }

                    playing = false;
                    break;
                }

                switchPlayer();
            }

            delete player1;
            delete player2;

            player1 = player2 = currentPlayer = nullptr;
        }
    }
};


int main() {

    Game game;

    game.start();

    return 0;
}
