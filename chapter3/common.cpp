//
//  common.cpp
//  
//
//  Created by Matheus Lehmann on 4/25/18.
//

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
    vector<string> words(2);
    vector<int> common(26);
    string permutation;
    
    int INFINITE = 10000;
    
    vector<map<char, int> > letters(2);
    int index;
    
    while (!cin.eof()) {
        getline(cin, words[0]);

        if (cin.eof()) break;

        getline(cin, words[1]);
        for (int i = 0; i < 26; i++) {
            common[i] = INFINITE;
        }
        permutation = "";
        
        for (int i = 0; i < letters.size(); i++) {
            letters[i].clear();
        }
        
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].length(); j++) {
                if (letters[i].count(words[i][j]) == 0) {
                    letters[i][words[i][j]] = 0;
                }
                letters[i][words[i][j]]++;
            }
        }

        for (map<char, int>::iterator it = letters[0].begin(); it != letters[0].end(); ++it) {
            index = (it->first) - 'a';
            common[index] = min(common[index], it->second);
            for (int i = 1; i < letters.size(); i++) {
                if (letters[i].count(it->first) > 0) {
                    common[index] = min(common[index], letters[i][it->first]);
                } else {
                    common[index] = 0;
                }
            }
        }
        
        for (int i = 0; i < common.size(); i++) {
            if (common[i] > 0 && common[i] != INFINITE) {
                for (int j = 0; j < common[i]; j++) {
                    permutation += ('a' + i);
                }
            }
        }
        cout << permutation << endl;
    }
    
    
    
    return 0;
}

