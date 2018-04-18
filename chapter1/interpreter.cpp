#include <iostream>
#include <vector>

using namespace std;

int main() {
 int t;
 vector<int> m;
 vector<string> r;
 int e;
 int c;
 int s;
 string l;
 int a, b;

 cin >> t;
 getline(cin, l);
 getline(cin, l);

 for (int i = 0; i < t; i++) {
  m = vector<int>(10,0);
  r = vector<string>(1000,"000");
  c = 0;
  while (true) {
   getline(cin, l);
   if (l.length() == 0) break;
   r[c] = l;
   c++;
  }
  
  e = 0;
  s = 0;
  while (true) {
   l = r[e];

   if (l == "100") {
    s++;
    break;
   }

   a = l[1]-'0';
   b = l[2]-'0';

   s++;

   switch (l[0]) {
    case '2':
     m[a] = b;
     e++;
     break;

    case '3':
     m[a] = (m[a]+b)%1000;
     e++;
     break;

    case '4':
     m[a] = (m[a]*b)%1000;
     e++;
     break;

    case '5':
     m[a] = m[b];
     e++;
     break;

    case '6':
     m[a] = (m[a]+m[b])%1000;
     e++;
     break;

    case '7':
     m[a] = (m[a]*m[b])%1000;
     e++;
     break;

    case '8':
     m[a] = stoi(r[m[b]]);
     e++;
     break;

    case '9':
     r[m[b]] = to_string(m[a]);
     e++;
     break;

    case '0':
     if (m[b] != 0) e = m[a];
     else e++;
     break;

    default:
     break;
   }
  }

  if (i > 0) cout << endl;
  cout << s << endl;

 } 

 return 0;
}



