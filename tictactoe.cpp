/*
 * ============================================================
 *  TIC TAC TOE  —  Console Mini Game
 *  Demonstrates: arrays, loops, conditionals, functions
 * ============================================================
 */

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ── Board ────────────────────────────────────────────────────
char board[3][3];

void initBoard() {
    char num = '1';
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = num++;
}

void displayBoard() {
    cout << "\n";
    cout << "  +---+---+---+\n";
    for (int r = 0; r < 3; r++) {
        cout << "  | ";
        for (int c = 0; c < 3; c++) {
            char ch = board[r][c];
            // Colour X red, O blue, numbers dim
            if      (ch == 'X') cout << "\033[1;31mX\033[0m";
            else if (ch == 'O') cout << "\033[1;34mO\033[0m";
            else                cout << "\033[2m" << ch << "\033[0m";
            cout << " | ";
        }
        cout << "\n  +---+---+---+\n";
    }
    cout << "\n";
}

// ── Logic ────────────────────────────────────────────────────
bool checkWin(char mark) {
    // Rows & columns
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == mark && board[i][1] == mark && board[i][2] == mark) return true;
        if (board[0][i] == mark && board[1][i] == mark && board[2][i] == mark) return true;
    }
    // Diagonals
    if (board[0][0] == mark && board[1][1] == mark && board[2][2] == mark) return true;
    if (board[0][2] == mark && board[1][1] == mark && board[2][0] == mark) return true;
    return false;
}

bool checkDraw() {
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] != 'X' && board[r][c] != 'O') return false;
    return true;
}

bool makeMove(int cell, char mark) {
    if (cell < 1 || cell > 9) return false;
    int r = (cell - 1) / 3;
    int c = (cell - 1) % 3;
    if (board[r][c] == 'X' || board[r][c] == 'O') return false;
    board[r][c] = mark;
    return true;
}

// ── Input helper ─────────────────────────────────────────────
int getInput(const string& prompt) {
    int val;
    while (true) {
        cout << prompt;
        if (cin >> val) { cin.ignore(); return val; }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Try again.\n";
    }
}

// ── Scoreboard ───────────────────────────────────────────────
struct Score { int wins = 0, losses = 0, draws = 0; };

// ── Main game loop ───────────────────────────────────────────
void playGame(Score& score, const string& p1, const string& p2) {
    initBoard();

    char marks[2]    = {'X', 'O'};
    string names[2]  = {p1, p2};
    int currentPlayer = 0;
    int moves = 0;

    cout << "\n\033[1;33m  Game start! " << p1 << " (X) vs " << p2 << " (O)\033[0m\n";

    while (true) {
        displayBoard();

        string& name = names[currentPlayer];
        char    mark = marks[currentPlayer];

        cout << "  \033[1m" << name << "'s turn (" << mark << ")\033[0m\n";
        int cell = getInput("  Enter cell [1-9]: ");

        if (!makeMove(cell, mark)) {
            cout << "  \033[1;31m  Cell taken or invalid — try again.\033[0m\n";
            continue;
        }
        moves++;

        if (checkWin(mark)) {
            displayBoard();
            cout << "  \033[1;32m*** " << name << " wins! Congratulations! ***\033[0m\n\n";
            if (currentPlayer == 0) { score.wins++;   }
            else                    { score.losses++; }
            return;
        }
        if (checkDraw()) {
            displayBoard();
            cout << "  \033[1;33m*** It's a draw! Well played both. ***\033[0m\n\n";
            score.draws++;
            return;
        }
        currentPlayer = 1 - currentPlayer;
    }
}

// ── Entry point ──────────────────────────────────────────────
int main() {
    cout << "\033[2J\033[H"; // clear screen
    cout << "\033[1;36m";
    cout << "  ╔═══════════════════════════╗\n";
    cout << "  ║      TIC  TAC  TOE        ║\n";
    cout << "  ╚═══════════════════════════╝\033[0m\n\n";

    cout << "  Enter Player 1 name (X): ";
    string p1; getline(cin, p1);
    cout << "  Enter Player 2 name (O): ";
    string p2; getline(cin, p2);
    if (p1.empty()) p1 = "Player 1";
    if (p2.empty()) p2 = "Player 2";

    Score score;
    char replay;

    do {
        playGame(score, p1, p2);

        cout << "  ─── Scoreboard ───────────────\n";
        cout << "  " << p1 << " Wins : " << score.wins   << "\n";
        cout << "  " << p2 << " Wins : " << score.losses << "\n";
        cout << "  Draws        : " << score.draws << "\n";
        cout << "  ──────────────────────────────\n\n";

        cout << "  Play again? (y/n): ";
        cin >> replay;
        cin.ignore();
        cout << "\n";
    } while (replay == 'y' || replay == 'Y');

    cout << "  Thanks for playing! Final scores:\n";
    cout << "  " << p1 << " — " << score.wins   << " wins\n";
    cout << "  " << p2 << " — " << score.losses << " wins\n";
    cout << "  Draws — " << score.draws << "\n\n";

    return 0;
}
