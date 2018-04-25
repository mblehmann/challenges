//
//  wertyu.cpp
//  
//
//  Created by Matheus Lehmann on 4/25/18.
//

#include <stdio.h>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main() {
    string line;
    map<char, char> shift;
    
    vector<string> keyboard;
    keyboard.push_back("`1234567890-=");
    keyboard.push_back("QWERTYUIOP[]\\");
    keyboard.push_back("ASDFGHJKL;'");
    keyboard.push_back("ZXCVBNM,./");
    

    shift[' '] = ' ';
    for (int i = 0; i < keyboard.size(); i++) {
        for (int j = 1; j < keyboard[i].length(); j++) {
            shift[keyboard[i][j]] = keyboard[i][j-1];
        }
    }
    
    while (true) {
        getline(cin, line);
        if (line == "") break;
        
        for (int i = 0; i < line.length(); i++) {
            cout << shift[line[i]];
        }
        cout << endl;
    }
    
    return 0;
}
