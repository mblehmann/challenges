#include <iostream>
#include <set>

using namespace std;

int main() {
    int t;
    cin >> t;
    
    int n, p, c;
    set<int> h;
    
    for (int i = 0; i < t; i++) {
        cin >> n;
        cin >> p;
        
        h.clear();
        for (int j = 0; j < p; j++) {
            cin >> c;
            for (int k = c; k <= n; k += c) {
                if (k % 7 > 0 && k % 7 < 6) {
                    h.insert(k);
                }
            }
        }
        cout << h.size() << endl;
    }
    
    return 0;
}