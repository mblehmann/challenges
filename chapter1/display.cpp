#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
 string n;
 int s;

 while (true) {
  cin >> s;
  if (s == 0) break;

  cin >> n;
  int r, c;
  r = 2*s+3;
  c = s+2;
  vector<vector<char> > d(r, vector<char>(n.length()*c, ' '));

  for (int i = 0; i < r; i += (s+1)) {
   for (int j = 0; j < n.length(); j++) {
    bool marks = true;
    if (i == 0) {
     if (n[j] == '1' || n[j] == '4') marks = false;
    } else if (i == s+1) {
     if (n[j] == '1' || n[j] == '7' || n[j] == '0') marks = false;
    } else {
     if (n[j] == '1' || n[j] == '4' || n[j] == '7') marks = false;
    }
    if (marks) {
     for (int k = j*c+1; k < (j+1)*c-1; k++) {
      d[i][k] = '-';
     }
    }
   }
  }

  for (int i = 1; i < r; i += (s+1)) {
   for (int j = 0; j < n.length(); j++) {
    for (int k = 0; k < c; k += (s+1)) {
     bool marks = true;
     if (i < s+1 && k == 0) {
      if (n[j] == '1' || n[j] == '2' || n[j] == '3' || n[j] == '7') marks = false;
     } 
     else if (i > s+1 && k == 0) {
      if (n[j] == '1' || n[j] == '3' || n[j] == '4' || n[j] == '5' || n[j] == '7' || n[j] == '9') marks = false;
     } 
     else if (i < s+1 && k == s+1) {
      if (n[j] == '5' || n[j] == '6') marks = false;
     }
     else {
      if (n[j] == '2') marks = false;
     } 
     if (marks) {
      for (int l = i; l < i+s; l++) {
       d[l][j*c+k] = '|';
      }
     }
    }
   }
  }

  for (int i = 0; i < r; i++) {
   for (int j = 0; j < n.length()*c; j++) {
    if (j > 0 && (j % (s+2) == 0)) cout << " ";
    cout << d[i][j];
   }
   cout << endl;
  }
  cout << endl;

 }

 return 0;
}


