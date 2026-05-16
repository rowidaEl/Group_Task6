# ❌⭕ Tic-Tac-Toe with AI

A **console-based Tic-Tac-Toe game** written in C++ featuring Player vs Player mode and two AI difficulty levels — including an unbeatable AI powered by the **Minimax algorithm**.

---

## 📋 Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Game Modes](#game-modes)
- [How the AI Works](#how-the-ai-works)
- [Project Structure](#project-structure)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Compilation](#compilation)
  - [Running](#running)
- [Gameplay](#gameplay)
- [Class Design](#class-design)

---

## Overview

This project is a fully playable Tic-Tac-Toe game built in C++ using **Object-Oriented Programming** principles. It supports human vs human matches and human vs computer matches at two difficulty levels. The hard-mode AI is implemented using the classic **Minimax algorithm**, making it play optimally and never lose.

---

## ✨ Features

- 🎮 Three game modes: PvP, Easy AI, Hard AI
- 🤖 Unbeatable AI using the **Minimax algorithm**
- 🎲 Easy AI uses **randomized moves**
- ♻️ **Play again** option without restarting the program
- 🧱 Clean **OOP architecture** with abstract base classes and polymorphism
- 🖥️ Simple, readable **console board display**
- ✅ Input validation with error recovery

---

## 🎮 Game Modes

| Mode | Description |
|------|-------------|
| **Player vs Player** | Two human players take turns on the same machine |
| **Player vs Computer (Easy)** | AI plays random valid moves |
| **Player vs Computer (Hard)** | AI uses Minimax — plays perfectly and never loses |

---

## 🧠 How the AI Works

### Easy Mode
The AI selects a **random empty cell** on the board each turn. It is easy to beat.

### Hard Mode — Minimax Algorithm
The AI uses the **Minimax algorithm**, a decision-making algorithm that:

1. Simulates **all possible future moves** recursively
2. Assigns a score to each terminal state:
   - `+10` → AI wins
   - `-10` → Human wins
   - `0` → Draw
3. The AI **maximizes** its own score and **minimizes** the opponent's score
4. Picks the move with the **highest evaluated value**

This guarantees the AI always plays optimally — the best outcome a human can achieve against it is a **draw**.

```
         AI's Turn (Maximize)
              [root]
            /    |    \
          move1 move2 move3
          /         \
    Human (Minimize) ...
       /    \
    move4  move5
     -10    +10
```

---

## 📁 Project Structure

```
XO_withAI/
│
├── main.cpp              # All source code
├── XO_withAI.exe         # Pre-compiled Windows executable
├── XO_withAI.depend      # Code::Blocks dependency file
└── .gitignore
```

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler supporting **C++11 or later** (e.g. `g++`, MSVC)
- No external libraries — uses only the C++ Standard Library

### Compilation

**Linux / macOS:**
```bash
g++ -std=c++11 -o XO_withAI main.cpp
```

**Windows (MinGW):**
```bash
g++ -std=c++11 -o XO_withAI.exe main.cpp
```

**Windows (MSVC):**
```bash
cl /EHsc /std:c++11 main.cpp /Fe:XO_withAI.exe
```

> A pre-compiled `XO_withAI.exe` for Windows is included in the repository.

### Running

```bash
./XO_withAI        # Linux / macOS
XO_withAI.exe      # Windows
```

---

## 🕹️ Gameplay

### Main Menu

```
TIC-TAC-TOE GAME
================
1. Player vs Player
2. Player vs Computer (Easy)
3. Player vs Computer (Hard)
4. Exit
```

### Board Display

```
    X  |  O  |    
   ----+-----+----
       |  X  |    
   ----+-----+----
    O  |     |  X 
```

### Making a Move

Players enter the **row and column** numbers (1–3):

```
Alice (X) enter row and column: 2 3
```

### After the Game

```
Alice wins!
Play again? (y/n):
```

---

## 🏗️ Class Design

```
Player  (abstract)
├── HumanPlayer       → gets input from the user via console
└── AIPlayer          → calculates moves via random or Minimax
        ├── getRandomMove()    → Easy mode
        ├── minimax()          → Minimax recursion
        ├── evaluateBoard()    → scores terminal states
        └── getBestMove()      → selects optimal move

Board
├── display()         → renders grid to console
├── makeMove()        → places a symbol on the board
├── checkWin()        → checks rows, columns, and diagonals
├── isFull()          → detects draw condition
└── reset()           → clears board for a new round

Game
├── setupPvP()        → configures two human players
├── setupPvC()        → configures human vs AI
├── handleHumanMove() → handles user input with validation
├── handleAIMove()    → triggers AI move calculation
├── checkGameEnd()    → detects win/draw and announces result
└── start()           → main game loop with menu
```

---

## 👩‍💻 Author

**rowidaEl** — [@rowidaEl](https://github.com/rowidaEl)
