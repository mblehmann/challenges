#include <iostream>

using namespace std;

int main() {
 // first and last numbers of the sequence
 int i, j;
 int b, e;
 // current number
 int n;
 // sequence count
 int c;
 int m;

 while (cin >> i >> j) {
  m = 0;
  b = min(i, j);
  e = max(i, j);
  for (int a = b; a <= e; a++) {
   n = a;
   c = 1;
   while (n != 1) {
    if (n % 2 == 0) n = n/2;
    else n = 3*n + 1;
    c++;
   }
   m = max(m, c);
  }
  cout << i << " " << j << " " << m << endl;
 }

 return 0;
}

