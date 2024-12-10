#include <bits/stdc++.h>
using namespace std;
/*for (auto it : v) {*/
/*  for (auto k : it) {*/
/*    cout << k;*/
/*  }*/
/*  cout << endl;*/
/*}*/
/**/

vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
void dfs(vector<vector<int>> &v, int row, int col, int n, int m, int val,
         int &ans, set<pair<int, int>> &vis) {
  if (val == 9) {
    ans++;
    return;
  }

  for (auto dir : dirs) {
    int dR = row + dir.first;
    int dC = col + dir.second;
    if (dR < n && dR >= 0 && dC < m && dC >= 0 && v[dR][dC] == val + 1) {
      dfs(v, dR, dC, n, m, val + 1, ans, vis);
    }
  }
}

int main() {

  ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<vector<int>> v;

  while (getline(f, s)) {
    vector<int> temp;
    for (auto it : s) {
      temp.push_back(it - '0');
    }
    v.push_back(temp);
  }

  int n = (int)v.size();
  int m = (int)v[0].size();

  auto inside = [&](int row, int col) {
    if (row < n && row >= 0 && col < m && col >= 0) {
      return true;
    }
    return false;
  };

  int finalans = 0;

  int k = 0;
  unordered_map<int, int> u;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v[i][j] == 0) {
        u[k] = 0;
        set<pair<int, int>> vis;
        for (auto dir : dirs) {
          int dR = i + dir.first;
          int dC = j + dir.second;
          if (inside(dR, dC) && v[dR][dC] == 1) {
            int ans = 0;
            dfs(v, dR, dC, n, m, 1, ans, vis);
            finalans += ans;
          }
        }
      }
    }
  }
  cout << finalans << endl;

  return 0;
}
