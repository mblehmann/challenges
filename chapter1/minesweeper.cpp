#include <iostream>
#include <vector>

using namespace std;

int main() {
 int n, m;
 int c;

 c = 0;
 while (true) {
  cin >> n >> m;
  if (n == 0 && m == 0) break;

  if (c > 0)
   cout << endl;

  vector<vector<char> > f(n, vector<char>(m));
  int b;
  c++; 

  for (int i = 0; i < n; i++) {
   for (int j = 0; j < m; j++) {
    cin >> f[i][j];
   }
  }

  for (int i = 0; i < n; i++) {
   for (int j = 0; j < m; j++) {
    if (f[i][j] == '.') {
     b = 0;
     for (int x = i-1; x <= i+1; x++) {
      for (int y = j-1; y <= j+1; y++) {
       if (x >= 0 && x < n && y >= 0 && y < m) {
        if (f[x][y] == '*') b++;
       }
      }
     }
     f[i][j] = b + '0';
    }
   }
  }
  
  printf("Field #%d:\n", c);
  for (int i = 0; i < n; i++) {
   for (int j = 0; j < m; j++) {
    cout << f[i][j];
   }
   cout << endl;
  }
 }

 return 0;
}

