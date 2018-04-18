#include <iostream>
#include <vector>
#include <map>
#include <sstream>

using namespace std;

// check if we have a winner
bool winner(vector<int> r, int p) {
    for (int i = 0; i < r.size(); i++) {
        if (r[i] >= (p+1)/2) {
            return true;
        }
    }
    return false;
}

int main() {
    // number of cases
    int t;
    
    // number of candidates
    int n;
    
    // candidates names
    vector<string> c;
    
    // vote
    string v;
    int q;

    // ballot
    map<string, int> b;
    
    // valid candidates
    vector<int> l;
    
    // result
    vector<int> r;

    // population
    int p;
    
    // worst candidate
    int min_v;
    vector<int> min_c;
    
    // tie flag
    bool tie;
    
    cin >> t;
    for (int i = 0; i < t; i++) {
        // get list of candidates
        cin >> n;
        c = vector<string>(n, "");
        getline(cin, v);

        for (int i = 0; i < n; i++) {
            getline(cin, c[i]);
        }

        // get list of votes
        b.clear();
        p = 0;
        while (true) {
            getline(cin, v);
            if (v.length() == 0) break;
            if (b.count(v) == 0) {
                b[v] = 0;
            }
            b[v]++;
            p++;
        }
        
        l = vector<int>(n, 1);
        do {
            // count
            r = vector<int>(n, 0);
            for (map<string, int>::iterator it = b.begin(); it != b.end(); ++it) {
                stringstream iv(it->first);
                while (true) {
                    iv >> q;
                    if (l[q-1] == 1) {
                        r[q-1] += it->second;
                        break;
                    }
                }
            }

            // check
            if (winner(r, p)) break;
            
            // remove
            min_v = p;
            min_c = vector<int>();
            for (int i = 0; i < r.size(); i++) {
                if (l[i] == 1) {
                    if (r[i] < min_v) {
                        min_v = r[i];
                        min_c.clear();
                        min_c.push_back(i);
                    } else if (r[i] == min_v) {
                        min_c.push_back(i);
                    }
                }
            }

            for (int i = 0; i < min_c.size(); i++) {
                l[min_c[i]] = 0;
            }

            // check for a tie
            tie = true;
            for (int i = 0; i < l.size(); i++) {
                if (l[i] == 1) {
                    tie = false;
                    break;
                }
            }
            if (tie) break;
            
        } while (true);
        
        // output result
        if (tie) {
            for (int i = 0; i < n; i++) {
                if (r[i] > 0) cout << c[i] << endl;
            }
        } else {
            for (int i = 0; i < n; i++) {
                if (r[i] >= (p+1)/2) cout << c[i] << endl;
            }
        }
        if (i < t-1) cout << endl;
    }
    
    return 0;
}
