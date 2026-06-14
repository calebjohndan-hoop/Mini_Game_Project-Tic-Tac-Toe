# ❌ Tic Tac Toe

A two-player Tic Tac Toe game for the terminal, written in C++.

## Features

- Two-player local multiplayer with custom player names
- Coloured board — X in red, O in blue
- Win, loss, and draw detection
- Persistent scoreboard across multiple rounds
- Robust input validation (handles bad input gracefully)

## Requirements

- A C++11-compatible compiler (`g++`)
- Any terminal (works on Linux, macOS, Windows with a compatible shell)

## Build & Run

```bash
g++ -o tictactoe tictactoe.cpp
./tictactoe
```

## How to Play

1. Enter names for Player 1 (X) and Player 2 (O)
2. The board cells are numbered 1–9, left to right, top to bottom:

```
+---+---+---+
| 1 | 2 | 3 |
+---+---+---+
| 4 | 5 | 6 |
+---+---+---+
| 7 | 8 | 9 |
+---+---+---+
```

3. On your turn, type the cell number and press Enter
4. First to get three in a row (horizontally, vertically, or diagonally) wins
5. After each game, choose to play again — the scoreboard carries over

## Code Concepts Demonstrated

- 2D arrays for board state
- Functions for win/draw detection and move validation
- Structs (`Score`) for tracking session statistics
- Input sanitisation with `cin` error recovery
- ANSI escape codes for coloured terminal output
