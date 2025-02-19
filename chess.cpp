#include <iostream>
#include <string>
#include <vector>
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
        do{
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

bool moveValidation (char board[8][8], vector<vector<char>> move) {
    char piece = board[move[0][0]][move[0][1]];
    switch (piece) {
        case 'R':
            
    }
}

vector<vector<int>> convert (string piece, string target) {
    // Converts it into a vector of vector of ints, example:
    // piece = a7 and Target = b3, it will return {{0, 6}, {1, 2}}
    // piece = c2 and Target = d1, it will return {{2, 1}, {3, 0}}

}
