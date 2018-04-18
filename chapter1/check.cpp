#include <iostream>
#include <vector>
#include <list>

using namespace std;

// check if pawn is checking
bool checkPawn(vector<string> b, int x, int y, char p) {
    int t = -1;
    // check if pawn can take any piece (until 7th rank)
    if (p == 'K' && x < b.size()-1) {
        t = x+1;
    } else if (p == 'k' && x > 0) {
        t = x-1;
    }
    // if yes, check the two diagonals
    if (t >= 0) {
        // if pawn is in column B or higher
        if (y > 0) {
            if (b[t][y-1] == p) return true;
        }
        // if pawn is in column G or lower
        if (y < b.size()-1) {
            if (b[t][y+1] == p) return true;
        }
    }
    return false;
}

bool checkHorse(vector<string> b, int x, int y, char p) {
    list<pair<int, int> > moves;
    moves.push_back(make_pair(-2, +1));
    moves.push_back(make_pair(-2, -1));
    moves.push_back(make_pair(-1, +2));
    moves.push_back(make_pair(-1, -2));
    moves.push_back(make_pair(+1, +2));
    moves.push_back(make_pair(+1, -2));
    moves.push_back(make_pair(+2, +1));
    moves.push_back(make_pair(+2, -1));
    int i, j;
    
    for (list<pair<int, int> >::iterator it = moves.begin(); it != moves.end(); ++it) {
        i = it->first;
        j = it->second;
        
        if (x+i >= 0 && x+i < b.size() && y+j >= 0 && y+j < b.size()) {
            if (b[x+i][y+j] == p) return true;
        }
    }

    return false;
}

bool checkLines(vector<string> b, int x, int y, char p) {
    for (int i = x+1; i < b.size(); i++) {
        if (b[i][y] == p) return true;
        if (b[i][y] != '.') break;
    }
    for (int i = x-1; i >= 0; i--) {
        if (b[i][y] == p) return true;
        if (b[i][y] != '.') break;
    }
    for (int i = y+1; i < b.size(); i++) {
        if (b[x][i] == p) return true;
        if (b[x][i] != '.') break;
    }
    for (int i = y-1; i >= 0; i--) {
        if (b[x][i] == p) return true;
        if (b[x][i] != '.') break;
    }
    return false;
}

bool checkDiagonals(vector<string> b, int x, int y, char p) {
    for (int i = 1; max(x+i, y+i) < b.size(); i++) {
        if (b[x+i][y+i] == p) return true;
        if (b[x+i][y+i] != '.') break;
    }
    for (int i = 1; min(x-i, y-i) >= 0; i++) {
        if (b[x-i][y-i] == p) return true;
        if (b[x-i][y-i] != '.') break;
    }
    for (int i = 1; x+i < b.size() && y-i >= 0; i++) {
        if (b[x+i][y-i] == p) return true;
        if (b[x+i][y-i] != '.') break;
    }
    for (int i = 1; x-i >= 0 && y+i < b.size(); i++) {
        if (b[x-i][y+i] == p) return true;
        if (b[x-i][y+i] != '.') break;
    }
    return false;
}

// print the board (for debug purpose)
void printBoard(vector<string> b) {
    for (int i = 0; i < b.size(); i++) {
        cout << b[i] << endl;
    }
}

int main() {
    
    // chess board;
    vector<string> b;
    // check variable
    // -1: white is in check
    //  0: nobody is in check
    // +1: black is in check
    int c;
    // detect an empty board
    bool end;
    // number of games
    int g;
    string emptyline = "........";
    
    g = 1;
    while (true) {
        b = vector<string>(8, emptyline);
        end = true;
        
        // read the new board and test if there is any piece in it
        for (int i = 0; i < 8; i++) {
            cin >> b[i];
            if (b[i] != emptyline) end = false;
        }
        
        // empty board
        if (end) break;
        
        c = 0;
        // check every square and every piece on the board
        for (int i = 0; i < b.size() && c == 0; i++) {
            for (int j = 0; j < b[i].size() && c == 0; j++) {
                switch(b[i][j]) {
                    // Pawn
                    case 'p':
                        if (checkPawn(b, i, j, 'K')) c = -1;
                        break;
                    case 'P':
                        if (checkPawn(b, i, j, 'k')) c = 1;
                        break;

                    // Knight
                    case 'n':
                        if (checkHorse(b, i, j, 'K')) c = -1;
                        break;
                    case 'N':
                        if (checkHorse(b, i, j, 'k')) c = 1;
                        break;

                    // Bishop
                    case 'b':
                        if (checkDiagonals(b, i, j, 'K')) c = -1;
                        break;
                    case 'B':
                        if (checkDiagonals(b, i, j, 'k')) c = 1;
                        break;

                    // Rook
                    case 'r':
                        if (checkLines(b, i, j, 'K')) c = -1;
                        break;
                    case 'R':
                        if (checkLines(b, i, j, 'k')) c = 1;
                        break;

                    // Queen
                    case 'q':
                        if (checkLines(b, i, j, 'K') || checkDiagonals(b, i, j, 'K')) c = -1;
                        break;
                    case 'Q':
                        if (checkLines(b, i, j, 'k') || checkDiagonals(b, i, j, 'k')) c = 1;
                        break;

                    // King or empty
                    default: break;
                }
            }
        }
        
        // print the result
        cout << "Game #" << g << ": ";
        if (c > 0) {
            cout << "black";
        } else if (c < 0) {
            cout << "white";
        } else {
            cout << "no";
        }
        cout << " king is in check." << endl;
        g++;
    }
    
    return 0;
}

