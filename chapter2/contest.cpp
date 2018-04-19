#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <sstream>

using namespace std;

struct score {
    int contestant;
    int correct;
    int time;
};

bool compare_score(score a, score b) {
    if (a.correct != b.correct) {
        return a.correct > b.correct;
    }
    if (a.time != b.time) {
        return a.time < b.time;
    }
    return a.contestant < b.contestant;
}

int main() {
    int n;
    string s;
    
    int c, p, t;
    char l;
    
    cin >> n;
    getline(cin, s);
    getline(cin, s);
    
    while (n > 0) {
        map<int, map<int, int> > penalty;
        map<int, set<int> > done;
        map<int, score> result;
        
        while (true) {
            getline(cin, s);
            if (s == "") break;

            stringstream event(s);
            event >> c >> p >> t >> l;
            
            if (result.count(c) == 0) {
                score r;
                r.contestant = c;
                r.correct = 0;
                r.time = 0;
                result[c] = r;
            }

            if (l == 'C') {
                if (done.count(c) == 0) {
                    done[c] = set<int>();
                }
                
                if (done[c].count(p) == 0) {
                    int a = t;
                    if (penalty[c][p] > 0) {
                        a += penalty[c][p] * 20;
                    }
                    result[c].correct++;
                    result[c].time += a;
                    done[c].insert(p);
                }
            } else if (l == 'I') {
                if (penalty.count(c) == 0) {
                    penalty[c] = map<int, int>();
                }
                if (penalty[c].count(p) == 0) {
                    penalty[c][p] = 0;
                }
                penalty[c][p]++;
            }
        }
        
        vector<score> ordered;
        for (map<int, score>::iterator it = result.begin(); it != result.end(); ++it) {
            ordered.push_back(it->second);
        }

        sort(ordered.begin(), ordered.end(), compare_score);
        
        for (int i = 0; i < ordered.size(); i++) {
            cout << ordered[i].contestant << " " << ordered[i].correct << " " << ordered[i].time << endl;
        }
        
        if (n > 1) {
            cout << endl;
        }
        n--;
    }
    
    return 0;
}
