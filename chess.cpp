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
            // asks user 1 for move, then user 2, converts it and checks. 
            // if it is a valid move, it will replace the piece at the end location with the one at the start.
            // Keeps going, we will not do checking for checkmates cuz thats too hard
            // Rememebr, if a move is invalid, it asks again. you will prob have to use a nested while loop.
            string piece;
            string target;
            
            while (true) {
                cout << "Player 1, piece would you like to move?" << endl << ">>> ";
                cin >> piece;

                cout << "Player 1, where would you like to move that piece?" << endl << ">>> ";
                cin >> target;
                
                vector<vector<int>> move = convert(piece, target);
                bool valid = moveValidation(board, move);

                if (boo)
            }    

            cout << "Player 2, piece would you like to move?" << endl << ">>> ";
            cin >> piece;

            cout << "Player 2, where would you like to move that piece?" << endl << ">>> ";
            cin >> target;
            
            vector<vector<int>> move = convert(piece, targehft);
            bool valid = moveValidation(board, move);

        }
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
    int diffX = target[0] - pos[0];
    int diffY = target[1] - pos[1];
    
    // Check if the move is diagonal using something I foudn online
    if (abs(diffX) != abs(diffY)) {
        return false;
    }
    // Determines whether the top one has to go forwards or backwards.
    int stepX = diffX > 0 ? 1 : -1;            
    int stepY = diffY > 0 ? 1 : -1;
    
    int currentX = pos[0] + stepX;
    int currentY = pos[1] + stepY;
    
    // Check each square on the path, other than the start and target. if there is  
    while (currentX != target[0]) {
        if (board[currentX][currentY] != '_') {
            return false;
        }
        currentX += stepX;
        currentY += stepY;
    }
    
    return true;
}

bool knightValidation (char board[8][8], vector<int> pos, vector<int> target) {
    int x1 = pos[0];
    int y1 = pos[1];

    int x2 = target[0];
    int y2 = target[1];

    // found thisc online cuz idk how a knight is supposed to move
    if ((abs(x2-x1)==1 && abs(y2-y1) == 2) || (abs(x2-x1) == 2 && abs(y2-y1) == 1)) {
        return true;
    }
    return false;
}


bool pawnValidation (char board[8][8], vector<int> pos, vector<int> target) {
    int x1 = pos[0];
    int y1 = pos[1];

    int x2 = target[0];
    int y2 = target[1];

    if (x2 == x1 && abs(y2 -y1) == 1) {
        if (board[target[0]][target[1]] == '_') return true;
    }
    return false;
}

bool kingValidation (char board[8][8], vector<int> pos, vector<int> target) {
    // |X2-X1|<=1 and |Y2-Y1|<=1
    int x1 = pos[0];
    int y1 = pos[1];

    int x2 = target[0];
    int y2 = target[1];

    if (abs(x2-x1) <= 1 && abs(y2-y1) <= 1) {
        return true;
    }
    return false;
}


bool queenValidation (char board[8][8], vector<int> pos, vector<int> target) {

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
        case 'N':
            return knightValidation(board, pos, target);
            break;
        case 'P':
            return pawnValidation(board, pos, target);
            break;
        case 'K':
            return kingValidation(board, pos, target);
            break;
        case 'Q':
            return queenValidation(board, pos, target);

            
    }
}

vector<vector<int>> convert(string piece, string target) {
    return {convert(piece), convert(target)};
}

vector<int> convert(string position) {
    vector<int> coords(2);
    coords[0] = position[0] - 'a';
    coords[1] = 8 - (position[1] - '0');
    return coords;
}


// This is the stack overflow page I got the basic move validation from, but had to add my own to see if there was  a piece in the way
// https://stackoverflow.com/questions/54972474/how-to-determine-valid-chess-moves