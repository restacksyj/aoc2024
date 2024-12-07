#include <bits/stdc++.h>
using namespace std;

int main() {

  ifstream f("input.txt");
  // ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<vector<char>> v;

  pair<int, int> me;
  int i = 0;

  while (getline(f, s)) {
    stringstream ss(s);
    string val;
    vector<char> temp;
    int j = 0;
    while (getline(ss, val)) {
      for (auto it : val) {
        if (it == '^') {
          me = {i, j};
        }
        temp.push_back(it);
        j++;
      }
    }
    v.push_back(temp);
    i++;
  }

  v[me.first][me.second] = '.';
  vector<pair<int, int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
  int dir = 0;
  set<pair<int,int>> vis;
  while (true) {
    vis.insert(me);
    int r2 = me.first + dirs[dir].first;
    int c2 = me.second + dirs[dir].second;
    if (!(r2 >= 0 && r2 < (int)v.size() && c2 >= 0 && c2 < (int)v[0].size())) {
      break;
    }
    if (v[r2][c2] == '.') {
      me = {r2, c2};
    } else {
      dir = (dir + 1) % 4;
    }
  }

  cout << vis.size() << endl;

  return 0;
}
