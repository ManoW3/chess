#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool moveValidation(char board[8][8], vector<vector<int>> move);
vector<vector<int>> convert(string p1Piece, string p1Target);
void makeMove(char board[8][8], vector<vector<int>> move);
bool isValidPosition(string pos);

int main() {
    char board[8][8] = 
       {{'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}, 
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}};  

    cout << "Welcome to Chess! Use algebraic notation (e.g., 'e2' to 'e4') to move pieces." << endl;
    cout << "White pieces: R=Rook, N=Knight, B=Bishop, Q=Queen, K=King, P=Pawn (uppercase)" << endl;
    cout << "Black pieces: r=rook, n=knight, b=bishop, q=queen, k=king, p=pawn (lowercase)" << endl;
    cout << "Board layout: Columns (a-h, left to right), Rows (8-1, top to bottom)" << endl;
    cout << "Enter 'quit' to exit or type 'lost' to resign and lose the game. cuz we didn't have enough time to check for checkmate in this project" << endl;

    while (true) {
        string piece;
        string target;
        
        // White's turn
        while (true) {
            cout << "\033[2J\033[1;1H"; // Clear screen
            cout << "\033[90m  a b c d e f g h\033[0m" << endl;
            for (int i = 0; i < 8; i++) {
                cout << "\033[90m" << (8 - i) << "\033[0m ";
                for (int j = 0; j < 8; j++) {
                    cout << board[i][j] << " ";
                }
                cout << "\033[90m" << (8 - i) << "\033[0m" << endl;
            }
            cout << "\033[90m  a b c d e f g h\033[0m" << endl;

            cout << "White's turn - Enter the position of the piece (e.g., 'e2'):" << endl << ">>> ";
            cin >> piece;
            if (piece == "quit") {
                cout << "Game ended. Thanks for playing!" << endl;
                return 0;
            }
            if (piece == "lost") {
                cout << "White has resigned. Black wins!" << endl;
                return 0;
            }

            cout << "Enter the target position (e.g., 'e4'):" << endl << ">>> ";
            cin >> target;
            if (target == "lost") {
                cout << "\033[2J\033[1;1H";
                cout << "White has resigned. Black wins!" << endl;
                return 0;
            }
            
            if (!isValidPosition(piece) || !isValidPosition(target)) {
                cout << "Invalid position! Please enter positions in the format 'e2'." << endl;
                continue;
            }

            vector<vector<int>> move = convert(piece, target);
            bool valid = false;
            if (move[0][0] >= 0 && move[0][0] < 8 && move[0][1] >= 0 && move[0][1] < 8) {
                char currentPiece = board[move[0][1]][move[0][0]];
                if (currentPiece >= 'A' && currentPiece <= 'Z') {
                    valid = moveValidation(board, move);
                }
            }

            if (valid) {
                makeMove(board, move);
                break;
            } else {
                cout << "Invalid move! Check the rules for that piece or ensure the path is clear." << endl;
            }
        }

        // Black's turn
        while (true) {
            cout << "\033[2J\033[1;1H"; // Clear screen
            cout << "\033[90m  a b c d e f g h\033[0m" << endl;
            for (int i = 0; i < 8; i++) {
                cout << "\033[90m" << (8 - i) << "\033[0m ";
                for (int j = 0; j < 8; j++) {
                    cout << board[i][j] << " ";
                }
                cout << "\033[90m" << (8 - i) << "\033[0m" << endl;
            }
            cout << "\033[90m  a b c d e f g h\033[0m" << endl;

            cout << "Black's turn - Enter the position of the piece (e.g., 'e7'):" << endl << ">>> ";
            cin >> piece;
            if (piece == "quit") {
                cout << "Game ended. Thanks for playing!" << endl;
                return 0;
            }
            if (piece == "lost") {
                cout << "\033[2J\033[1;1H";
                cout << "Black has resigned. White wins!" << endl;
                return 0;
            }

            cout << "Enter the target position (e.g., 'e5'):" << endl << ">>> ";
            cin >> target;
            if (target == "lost") {
                cout << "Black has resigned. White wins!" << endl;
                return 0;
            }
            
            if (!isValidPosition(piece) || !isValidPosition(target)) {
                cout << "Invalid position! Please enter positions in the format 'e2'." << endl;
                continue;
            }

            vector<vector<int>> move = convert(piece, target);
            bool valid = false;
            if (move[0][0] >= 0 && move[0][0] < 8 && move[0][1] >= 0 && move[0][1] < 8) {
                char currentPiece = board[move[0][1]][move[0][0]];
                if (currentPiece >= 'a' && currentPiece <= 'z') {
                    valid = moveValidation(board, move);
                }
            }

            if (valid) {
                makeMove(board, move);
                break;
            } else {
                cout << "Invalid move! Check the rules for that piece or ensure the path is clear." << endl;
            }
        }
    }
}

bool isValidPosition(string pos) {
    if (pos.length() != 2) return false;
    char col = pos[0];
    char row = pos[1];
    return (col >= 'a' && col <= 'h') && (row >= '1' && row <= '8');
}

bool rookValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int row1 = pos[1], col1 = pos[0];
    int row2 = target[1], col2 = target[0];

    if (row1 != row2 && col1 != col2) return false; // Must move straight
    
    int rowStep = (row2 == row1) ? 0 : (row2 > row1 ? 1 : -1);
    int colStep = (col2 == col1) ? 0 : (col2 > col1 ? 1 : -1);
    
    int row = row1 + rowStep;
    int col = col1 + colStep;
    
    while (row != row2 || col != col2) {
        if (board[row][col] != '_') return false; // Path blocked
        row += rowStep;
        col += colStep;
    }
    return true;
}

bool bishopValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int diffX = target[0] - pos[0];
    int diffY = target[1] - pos[1];
    
    if (abs(diffX) != abs(diffY)) return false;
    
    int stepX = diffX > 0 ? 1 : -1;
    int stepY = diffY > 0 ? 1 : -1;
    
    int currentX = pos[0] + stepX;
    int currentY = pos[1] + stepY;
    
    while (currentX != target[0] && currentY != target[1]) {
        if (board[currentY][currentX] != '_') return false;
        currentX += stepX;
        currentY += stepY;
    }
    
    return true;
}

bool knightValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int x1 = pos[0];
    int y1 = pos[1];

    int x2 = target[0];
    int y2 = target[1];

    if ((abs(x2-x1)==1 && abs(y2-y1) == 2) || (abs(x2-x1) == 2 && abs(y2-y1) == 1)) {
        return true;
    }
    return false;
}

bool pawnValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int col1 = pos[0], row1 = pos[1];
    int col2 = target[0], row2 = target[1];

    // Ensure the move is in the same column and only moves up or down one space
    if (col1 == col2 && abs(row2 - row1) == 1 && board[row2][col2] == '_') 
        return true;

    return false;
}

bool kingValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int x1 = pos[0];
    int y1 = pos[1];

    int x2 = target[0];
    int y2 = target[1];

    if (abs(x2-x1) <= 1 && abs(y2-y1) <= 1) {
        return true;
    }
    return false;
}

bool queenValidation(char board[8][8], vector<int> pos, vector<int> target) {
    int rowDiff = abs(target[1] - pos[1]);
    int colDiff = abs(target[0] - pos[0]);
    
    if (rowDiff == 0 || colDiff == 0) { // Rook-like move
        return rookValidation(board, pos, target);
    }
    if (rowDiff == colDiff) { // Bishop-like move
        return bishopValidation(board, pos, target);
    }
    return false;
}

bool moveValidation(char board[8][8], vector<vector<int>> move) {
    vector<int> pos = move[0];
    vector<int> target = move[1];
    
    if (pos[0] == target[0] && pos[1] == target[1]) return false;
    if (pos[0] < 0 || pos[0] > 7 || pos[1] < 0 || pos[1] > 7) return false;
    if (target[0] < 0 || target[0] > 7 || target[1] < 0 || target[1] > 7) return false;
    
    char piece = board[pos[1]][pos[0]];
    char targetPiece = board[target[1]][target[0]];
    bool isWhite = (piece >= 'A' && piece <= 'Z');
    bool targetIsWhite = (targetPiece >= 'A' && targetPiece <= 'Z');
    if (targetPiece != '_' && isWhite == targetIsWhite) return false;

    switch (piece) {
        case 'R': case 'r': return rookValidation(board, pos, target);
        case 'B': case 'b': return bishopValidation(board, pos, target);
        case 'N': case 'n': return knightValidation(board, pos, target);
        case 'P': case 'p': return pawnValidation(board, pos, target);
        case 'K': case 'k': return kingValidation(board, pos, target);
        case 'Q': case 'q': return queenValidation(board, pos, target);
        default: return false;
    }
}

vector<int> convertidk(string position) {
    if (position.length() != 2 || position[0] < 'a' || position[0] > 'h' || position[1] < '1' || position[1] > '8') {
        return {-1, -1};  // Invalid move, prevent crashes
    }
    return {position[0] - 'a', 8 - (position[1] - '0')};
}

vector<vector<int>> convert(string piece, string target) {
    return {convertidk(piece), convertidk(target)};
}

void makeMove(char board[8][8], vector<vector<int>> move) {
    int startRow = move[0][1];
    int startCol = move[0][0];
    int targetRow = move[1][1];
    int targetCol = move[1][0]; 

    char piece = board[startRow][startCol];
    board[startRow][startCol] = '_';
    board[targetRow][targetCol] = piece; 
}