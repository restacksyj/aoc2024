#include <bits/stdc++.h>
using namespace std;

void print(int i) { cout << i << endl; }

int main() {

  ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<vector<char>> v;
  while (getline(f, s)) {
    vector<char> temp;
    for (auto it : s) {
      temp.push_back(it);
    }
    v.push_back(temp);
  }

  int n = (int)v.size();
  int m = (int)v[0].size();

  unordered_map<char, int> vis;
  unordered_map<char, vector<pair<int, int>>> viscoord;
  vector<vector<int>> visited(n, vector<int>(m, -1));
  vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};

  auto inside = [&](int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m) {
      return true;
    }
    return false;
  };

  auto dfs = [&](int row, int col, char ch, auto &dfs_ref) -> void {
    vis[ch]++;
    viscoord[ch].push_back({row, col});
    visited[row][col] = 1;
    for (auto dir : dirs) {
      int dR = dir.first + row;
      int dC = dir.second + col;
      if (inside(dR, dC) && v[dR][dC] == ch && visited[dR][dC] == -1) {
        dfs_ref(dR, dC, v[dR][dC], dfs_ref);
      }
    }
  };

  auto neighbors = [&](int row, int col, char ch) {
    int count = 0;
    if (row > 0 && v[row - 1][col] == ch) {
      count++;
    }
    if (row < n - 1 && v[row + 1][col] == ch) {
      count++;
    }
    if (col < m - 1 && v[row][col + 1] == ch) {
      count++;
    }
    if (col > 0 && v[row][col - 1] == ch) {
      count++;
    }
    return count;
  };

  int finalAns = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (vis.count(v[i][j]) == 0 && visited[i][j] == -1) {
        dfs(i, j, v[i][j], dfs);
        char ch = v[i][j];
        auto q = viscoord[ch];
        int totalC = 0;
        for (auto k : q) {
          int kR = k.first;
          int kC = k.second;
          totalC += 4 - neighbors(kR, kC, ch);
        }
        cout << ch << " " << vis[ch] << " " << totalC << endl;
        finalAns += vis[ch] * totalC;
        vis.erase(ch);
        viscoord.erase(ch);
      }
    }
  }

  print(finalAns);

  return 0;
}
