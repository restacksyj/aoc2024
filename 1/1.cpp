#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<int> left;
  vector<int> right;
  unordered_map<int, int> u;
  while (getline(f, s)) {
    stringstream ss(s);
    int a, b;
    ss >> a >> b;
    left.push_back(a);
    right.push_back(b);
    u[b]++;
  }

  /*sort(left.begin(), left.end());*/
  /*sort(right.begin(), right.end());*/

  int sum = 0;
  for (int i = 0; i < (int)left.size(); i++) {
    sum += left[i]*u[left[i]];
  }

  cout << sum << endl;

  f.close();

  return 0;
}
