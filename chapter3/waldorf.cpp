//
//  waldorf.cpp
//  
//
//  Created by Matheus Lehmann on 4/25/18.
//

#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    int m, n;
    int k;
    
    string word;
    bool found;
    
    while (t > 0) {
        cin >> m >> n;
        vector<string> grid(m);
        for (int row = 0; row < m; row++) {
            cin >> grid[row];
            for (int col = 0; col < n; col++) {
                if (grid[row][col] >= 'A' && grid[row][col] <= 'Z') {
                    grid[row][col] = grid[row][col] - 'A' + 'a';
                }
            }
        }
        
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> word;
            for (int j = 0; j < word.length(); j++) {
                if (word[j] >= 'A' && word[j] <= 'Z') {
                    word[j] = word[j] - 'A' + 'a';
                }
            }

            found = false;
            for (int row = 0; row < m && !found; row++) {
                for (int col = 0; col < n && !found; col++) {
                    if (grid[row][col] == word[0]) {
                        // horizontal
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col+j >= n) break;
                            if (word[j] != grid[row][col+j]) break;
                            if (j == word.length()-1) found = true;
                        }
                        
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col-j < 0) break;
                            if (word[j] != grid[row][col-j]) break;
                            if (j == word.length()-1) found = true;
                        }
                        
                        // vertical
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (row+j >= m) break;
                            if (word[j] != grid[row+j][col]) break;
                            if (j == word.length()-1) found = true;
                        }
                        
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (row-j < 0) break;
                            if (word[j] != grid[row-j][col]) break;
                            if (j == word.length()-1) found = true;
                        }
                        
                        // diagonal
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col+j >= n || row+j >= m) break;
                            if (word[j] != grid[row+j][col+j]) break;
                            if (j == word.length()-1) found = true;
                        }
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col+j >= n || row-j < 0) break;
                            if (word[j] != grid[row-j][col+j]) break;
                            if (j == word.length()-1) found = true;
                        }
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col-j < 0 || row+j >= m) break;
                            if (word[j] != grid[row+j][col-j]) break;
                            if (j == word.length()-1) found = true;
                        }
                        for (int j = 0; j < word.length() && !found; j++) {
                            if (col-j < 0 || row-j < 0) break;
                            if (word[j] != grid[row-j][col-j]) break;
                            if (j == word.length()-1) found = true;
                        }

                        if (found) {
                            cout << (row+1) << " " << (col+1) << endl;
                        }
                    }
                }
            }
        }

        if (t > 1) cout << endl;
        
        t--;
    }
    
    return 0;
}
