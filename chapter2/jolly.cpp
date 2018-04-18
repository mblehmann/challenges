#include <iostream>
#include <set>

using namespace std;

int main() {
    int n;
    set<int> s;
    int c, l;
    int d;
    bool j;
    
    while (cin >> n) {
        s.clear();
        j = true;
        cin >> c;
        for (int i = 0; i < n-1; i++) {
            l = c;
            cin >> c;
            if (j) {
                d = abs(l-c);
                if (d >= n || s.count(d)) {
                    j = false;
                }
                s.insert(d);
            }
        }
        
        if (j) {
            cout << "Jolly" << endl;
        } else {
            cout << "Not jolly" << endl;
        }
        
    }
    
    return 0;
}
