#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double round2d(double n) {
 return (int) ((n*100)+0.5) / 100.0;
}

bool morethantwo(double n) {
 string l = to_string(n);
 for (int i = 0; i < l.length(); i++) {
  if (l[i] == '.') {
   for (int j = i+3; j < l.length()-1; j++) {
    if (l[j] != '0') return true;
   }
  }
 }
 return false;
}

int main() {
 int n;

 while (true) {
  cin >> n;
  if (n == 0) break;

  vector<double> m(n);
  double s;
  double d1, d2;
  vector<double> e(4,0);

  s = 0;
  for (int i = 0; i < n; i++) {
   cin >> m[i];
   s += m[i];
  }
  
  sort(m.begin(), m.end());
  d1 = s/n;
  if (morethantwo(d1)) {
   d2 = d1 + 0.01;
  } else {
   d2 = 0;
  }
  d1 = round2d(d1);
  d2 = round2d(d2);
 
  for (int i = 0; i < n; i++) {
   if (m[i] > d1) {
    e[0] += (m[i]-d1);
   } else {
    e[1] += (d1-m[i]);
   }

   if (d2 > 0) {
    if (m[i] > d2) {
     e[2] += (m[i]-d2);
    } else {
     e[3] += (d2-m[i]);
    }
   }
  }
  
  if (e[0] > 0 && e[1] > 0) 
    printf("$%.2f\n", min(e[0], e[1]));
  else 
    printf("$%.2f\n", min(e[2], e[3]));
 }

 return 0;
}
