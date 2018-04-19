#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <sstream>

using namespace std;

// Print the sentence based on the given mapping
void print(string sentence, map<char, char> letters) {
    for (int i = 0; i < sentence.size(); i++) {
        cout << letters[sentence[i]];
    }
    cout << endl;
}

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

vector<map<char, char> > guess(map<string, vector<string> > words, map<char, char> mapping, map<char, char> reverse) {
    vector<map<char, char> > response;
    bool correct = true;
    bool unchanged = false;
    
    string input, word;
    
    // Iterate until there are words left to translate trivially
    while (!words.empty() && correct && !unchanged) {
        unchanged = true;
        
        for (map<string, vector<string> >::iterator w = words.begin(); w != words.end() && correct; ) {
            if ((w->second).size() == 0) {
                correct = false;
                break;
            }
            if ((w->second).size() == 1) {
                unchanged = false;
                input = w->first;
                word = (w->second)[0];
                for (int i = 0; i < input.size(); i++) {
                    if ((mapping[input[i]] == '*' && reverse[word[i]] == '*')
                        || (mapping[input[i]] == word[i] && reverse[word[i]] == input[i])) {
                        mapping[input[i]] = word[i];
                        reverse[word[i]] = input[i];
                    } else {
                        correct = false;
                        break;
                    }
                }
                w = words.erase(w);
            } else {
                ++w;
            }
        }
        
        for (map<string, vector<string> >::iterator w = words.begin(); w != words.end() && correct; ++w) {
            input = w->first;
            vector<string> potentials = w->second;
            for (int i = 0; i < potentials.size(); i++) {
                word = potentials[i];
                for (int j = 0; j < input.size(); j++) {
                    if (!((mapping[input[j]] == '*' && reverse[word[j]] == '*')
                          || (mapping[input[j]] == word[j] && reverse[word[j]] == input[j]))) {
                        unchanged = false;
                        potentials.erase(potentials.begin()+i);
                        i--;
                        break;
                    }
                }
            }
            words[input] = potentials;
        }
    }
    
    response.push_back(mapping);
    response.push_back(reverse);
    if (unchanged) {
        correct = false;
        int total = 1;
        input = "";
        vector<int> max_n(words.size(), 0);
        int index = 0;
        for (map<string, vector<string> >::iterator w = words.begin(); w != words.end(); ++w) {
            input += w->first;
            total *= (w->second).size();
            max_n[index] = (w->second).size();
            index++;
        }
        vector<int> cartesian(words.size(), 0);
        
        while (total > 0) {
            word = "";
            index = 0;
            
            for (map<string, vector<string> >::iterator w = words.begin(); w != words.end(); ++w) {
                word += (w->second)[cartesian[index]];
                index++;
            }
            mapping = response[0];
            reverse = response[1];
            correct = true;
            for (int i = 0; i < input.size(); i++) {
                if ((mapping[input[i]] == '*' && reverse[word[i]] == '*')
                    || (mapping[input[i]] == word[i] && reverse[word[i]] == input[i])) {
                    mapping[input[i]] = word[i];
                    reverse[word[i]] = input[i];
                } else {
                    correct = false;
                    break;
                }
            }
            if (correct) {
                response[0] = mapping;
                response[1] = reverse;
                break;
            }
            
            index = cartesian.size()-1;
            cartesian[index]++;
            while (cartesian[index] >= max_n[index]) {
                cartesian[index] = 0;
                index--;
                cartesian[index]++;
            }
            total--;
        }
    }
    
    map<char, char> result;
    if (correct) {
        result['r'] = 'y';
    } else {
        result['r'] = 'n';
    }
    
    response.push_back(result);
    
    return response;
}

int main() {
    int n;
    
    string s_format;
    string word;
    map<string, vector<string> > dict;
    
    map<char, char> mapping;
    map<char, char> reverse;
    map<char, char> result;
    map<string, vector<string> > words;
    
    bool correct;
    bool unchanged;
    
    int s;
    bool p;
    
    vector<string> candidates;
    
    string sentence;
    string input;
    
    string r1, r2;
    bool ok;
    bool done;
    bool prog;
    
    
    int a;
    
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
        words.clear();
        correct = true;
        unchanged = false;
        
        // Build the initial mapping of words to translation
        // Each word matches those of the same format
        // This is the smallest set of candidates
        stringstream crypt(sentence);
        while (crypt >> input) {
            s_format = format(input);
            if (dict.count(s_format) == 0) {
                correct = false;
                break;
            }
            words[input] = dict[s_format];
        }
        
        vector<map<char, char> > response = guess(words, mapping, reverse);
        mapping = response[0];
        reverse = response[1];
        result = response[2];
        
        if (result['r'] == 'n') {
            for (char c = 'a'; c <= 'z'; c++) {
                mapping[c] = '*';
            }
        }
        print(sentence, mapping);
    }
    
    
    
    return 0;
}
