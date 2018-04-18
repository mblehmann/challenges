#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

int main() {

 char c;
 char o;
 int m, n;
 vector<vector<char> > p;
 queue<pair<int, int> > q;
 set<pair<int, int> > v;

 int x1, x2;
 int y1, y2;
 int b1, b2, e1, e2;
 char a;
 string f;
 
 while (true) {
  cin >> c;
  if (c == 'X') break;
 
  switch (c) {
    case 'I':
     cin >> m >> n;

      case 'C':
       p.assign(m, vector<char>(n, 'O'));
       //p = vector<vector<int> >(m, vector<int>(n, 'O'));
       break;

      case 'L':
       cin >> x1 >> y1 >> a;
       x1--;
       y1--;
       p[x1][y1] = a;
       break;

      case 'V':
       cin >> x1 >> y1 >> y2 >> a;
       x1--;
       y1--;
       y2--;
       b1 = min(y1,y2);
       e1 = max(y1,y2);
       for (int i = b1; i <= e1; i++) {
        p[x1][i] = a;
       }
       break;

      case 'H':
       cin >> x1 >> x2 >> y1 >> a;
       x1--;
       x2--;
       y1--;
       b1 = min(x1,x2);
       e1 = max(x1,x2);
       for (int i = b1; i <= e1; i++) {
        p[i][y1] = a;
       }
       break;

      case 'K':
       cin >> x1 >> y1 >> x2 >> y2 >> a;
       x1--;
       x2--;
       y1--;
       y2--;
       b1 = min(x1,x2);
       e1 = max(x1,x2);
       b2 = min(y1,y2);
       e2 = max(y1,y2);
       for (int i = b1; i <= e1; i++) {
        for (int j = b2; j <= e2; j++) {
         p[i][j] = a;
        }
       }
       break;

      case 'F':
       cin >> x1 >> y1 >> a;
       x1--;
       y1--;
       o = p[x1][y1];
       if (a != o) {
        q = queue<pair<int, int> >();
        v = set<pair<int, int> >();
        q.push(make_pair(x1, y1));
        while (!q.empty()) {
         pair<int, int> d = q.front();
         if (v.count(d) == 0) {
          v.insert(d);
          p[d.first][d.second] = a;
          if (d.first+1 < m && p[d.first+1][d.second] == o) {
           q.push(make_pair(d.first+1, d.second));
          }
          if (d.first-1 >= 0 && p[d.first-1][d.second] == o) {
           q.push(make_pair(d.first-1, d.second));
          }
          if (d.second+1 < n && p[d.first][d.second+1] == o) {
           q.push(make_pair(d.first, d.second+1));
          }
          if (d.second-1 >= 0 && p[d.first][d.second-1] == o) {
           q.push(make_pair(d.first, d.second-1));
          }
         }
         q.pop();
        }
       }
       break;
 
      case 'S':
       cin >> f;
       cout << f << endl;
       for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
         cout << p[j][i];
        }
        cout << endl;
       }
       break;

      default: break;
     }
    }

 return 0;
}
