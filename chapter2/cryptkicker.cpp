#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

int main() {
    int n;
    int s;
    map<int, vector<string> > words;
    map<char, char> dict;
    string word;
    string sentence;
    set<string> news;
    
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> word;
        s = word.size();
        if (words.count(s) == 0) {
            words[s] = vector<string>();
        }
        words[s].push_back(word);
    }
    
    getline(cin, sentence);
    while (getline(cin, sentence)) {
        dict.clear();
        news.clear();
        stringstream crypt(sentence);
        while (crypt >> word) {
            news.insert(word);
        }
        
        for (map<int, vector<string> >::reverse_iterator m = words.rbegin(); m != words.rend(); ++m) {
            cout << m->first << " " << (m->second).size() << endl;
        }

        while (!news.empty()) {
            for (set<string>::iterator z = news.begin(); z != news.end(); ++z) {
                s = z->size();
                if (
            
            }

        }
        
        
        
    }
    
    
    
    return 0;
}
