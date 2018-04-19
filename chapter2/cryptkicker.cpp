#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>

using namespace std;

bool FOUND;

// Returns the format of the word based on letter repetition
string format(string word) {
    char l = 'a';
    map<char, char> m;
    string a = "";
    
    for (int i = 0; i < word.size(); i++) {
        ;
        if (m.count(word[i]) == 0) {
            m[word[i]] = l;
            l++;
        }
        a += m[word[i]];
    }
    
    return a;
}

void backtrack(vector<string> solution, int k, vector<string> line, vector<vector<string> > words, map<char, char> mapping, map<char, char> reverse, map<string, string> known) {
    if (k == words.size()) {
        FOUND = true;
        for (int i = 0; i < solution.size()-1; i++) {
            cout << solution[i] << " ";
        }
        cout << solution[solution.size()-1] << endl;
    } else {
        string input = line[k];
        if (known.count(input) > 0) {
            solution[k] = known[input];
            backtrack(solution, k+1, line, words, mapping, reverse, known);
        } else {
            vector<string> candidates = words[k];
            bool correct;
            for (int i = 0; i < candidates.size(); i++) {
                string word = candidates[i];
                solution[k] = word;
                
                correct = true;
                map<char, char> new_mapping = mapping;
                map<char, char> new_reverse = reverse;
                
                for (int i = 0; i < input.size(); i++) {
                    if ((new_mapping[input[i]] == '*' && new_reverse[word[i]] == '*')
                        || (new_mapping[input[i]] == word[i] && new_reverse[word[i]] == input[i])) {
                        new_mapping[input[i]] = word[i];
                        new_reverse[word[i]] = input[i];
                    } else {
                        correct = false;
                        break;
                    }
                }
                if (correct) {
                    known[input] = word;
                    backtrack(solution, k+1, line, words, new_mapping, new_reverse, known);
                }
                if (FOUND) return;
            }
        }
    }
}

int main() {
    int n;
    string sentence;
    string input;

    string s_format;
    string word;
    map<string, vector<string> > dict;
    
    map<char, char> mapping;
    map<char, char> reverse;
    map<char, char> result;
    
    vector<string> line;
    vector<vector<string> > words;
    
    // Build the dictionary
    // The dictionary is format: [words]
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> word;
        s_format = format(word);
        if (dict.count(s_format) == 0) {
            dict[s_format] = vector<string>();
        }
        dict[s_format].push_back(word);
    }
    
    // each line in the file
    getline(cin, sentence);
    while (getline(cin, sentence)) {
        
        // Clear the data structures
        // Two mapping char: char to guarantee one-for-one
        // A mapping of string: [candidates]
        // The correct flag indicates if it is still possible to solve
        mapping.clear();
        reverse.clear();
        mapping[' ' ] = ' ';
        reverse[' '] = ' ';
        for (char c = 'a'; c <= 'z'; c++) {
            mapping[c] = '*';
            reverse[c] = '*';
        }
        line.clear();
        words.clear();
        
        // Build the initial mapping of words to translation
        // Each word matches those of the same format
        // This is the smallest set of candidates
        stringstream crypt(sentence);
        while (crypt >> input) {
            s_format = format(input);
            line.push_back(input);
            if (dict.count(s_format) == 0) {
                dict[s_format] = vector<string>();
            }
            words.push_back(dict[s_format]);
        }
        
        FOUND = false;
        vector<string> solution(words.size());
        map<string, string> known;
        backtrack(solution, 0, line, words, mapping, reverse, known);
        
        if (!FOUND) {
            for (int i = 0; i < sentence.size(); i++) {
                if (sentence[i] >= 'a' && sentence[i] <= 'z') cout << '*';
                else cout << sentence[i];
            }
            cout << endl;
        }
    }

    return 0;
}
