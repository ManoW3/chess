#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

bool moveValidation (char board[8][8], string piece, string target);
vector<vector<int>> convert (string p1Piece, string p1Target);

int main() {
    char board[8][8] = 
        {{'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}, 
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'_', '_', '_', '_', '_', '_', '_', '_'}, 
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'}, 
        {'R', 'N', 'B', 'K', 'Q', 'B', 'N', 'R'}};  

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cout << board[i][j];
        }
    }

    while (true) {
        do {
            string p1Piece;
            string p1Target;

            cout << "Player 1, piece would you like to move?" << endl << ">>> ";
            cin >> p1Piece;

            cout << "Player 1, where would you like to move that piece?" << endl << ">>> ";
            cin >> p1Target;
            vector<vector<int>> move = convert(p1Piece, p1Target);
            bool valid = moveValidation(board, move);

        } while(!valid);
    } 
}
bool rookValidation (char board[8][8], vector<int> pos, vector<int> target) {
    int greaterY = max(pos[1], target[1]);
    int smallerY = min(pos[1], target[1]);

    int greaterX = max(pos[0], target[0]);
    int smallerX = min(pos[0], target[0]);

    // left and right
    if (pos[0] == target[0]) {
        for (int i = smallerY + 1; i < greaterY; i++) {
            if (board[pos[0]][i] != ' ') {
                return false; 
            }
        }
    }
    // up and down
    else if (pos[1] == target[1]) {
        for (int i = smallerX + 1; i < greaterX; i++) {
            if (board[i][pos[1]] != ' ') {
                return false; 
            }
        }
    }
    else {
        return false; 
    }
}

bool bishopValidation (char board[8][8], vector<int> pos, vector<int> target) {
    int greaterY = max(pos[1], target[1]);
    int smallerY = min(pos[1], target[1]);

    int greaterX = max(pos[0], target[0]);
    int smallerX = min(pos[0], target[0]);

    if(abs(pos[0]-target[0]) == abs(pos[1]-target[1])) {
        // if 
        // for loop starts at top right, subtracts one from each
    }
}

bool moveValidation (char board[8][8], vector<vector<int>> move) {
    vector<int> pos = move[0];
    vector<int> target = move[1];
    char piece = board[move[0][0]][move[0][1]];
    switch (piece) {
        case 'R': 
            return rookValidation(board, pos, target);
            break;
        case 'B': 
            return bishopValidation(board, pos, target);
            break;

            
    }
}

vector<int> convert (string position) {
    vector<int> coords(2);
    coords[0] = position[0] - 'a';
    coords[1] = 8 - (position[1] - '0');
    return coords;
}