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

  auto neighbors = [&](int row, int col, char ch, set<pair<int, int>> &temp) {
    int count = 0;
    // up
    if (row > 0 && v[row - 1][col] == ch) {
      temp.insert({row - 1, col});
      count++;
    }
    // down
    if (row < n - 1 && v[row + 1][col] == ch) {
      temp.insert({row + 1, col});
      count++;
    }
    // right
    if (col < m - 1 && v[row][col + 1] == ch) {
      temp.insert({row, col + 1});
      count++;
    }
    //  left
    if (col > 0 && v[row][col - 1] == ch) {
      temp.insert({row, col - 1});
      count++;
    }
    return count;
  };

  auto printset = [&](set<pair<int, int>> s) {
    for (auto it : s) {
      cout << it.first << " " << it.second << " ";
    }
    cout << "\n";
  };

  auto checkCross = [&](int row, int col, char ch) {
    if (inside(row + 1, col) && v[row + 1][col] == ch) {
    }
  };

  auto corners = [&](int row, int col, char ch, set<pair<int, int>> &temp) {
    vector<pair<int, int>> diagonalsDirs = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};

    int finalCorners = 0;
    // check bR diagonal
    int count = 0;
    if (inside(row + 1, col) && v[row + 1][col] == ch) {
      count++;
    }

    if (inside(row, col + 1) && v[row][col + 1] == ch) {
      count++;
    }

    bool counted = false;
    if (count % 2 == 0) {
      int dR = row + diagonalsDirs[0].first;
      int dC = col + diagonalsDirs[0].second;
      if (!inside(dR, dC)) {
        finalCorners++;
      } else {
        if (v[dR][dC] != ch) {
          counted = true;
          finalCorners++;
        }
      }
    }

    if (count == 0 && !counted) {
      if (inside(row + 1, col) && inside(row, col + 1) &&
          v[row + 1][col] != ch && v[row][col + 1] != ch) {
        if (ch == 'B') {
          cout << count << endl;
          cout << row << col << endl;
          cout << "Incereasing bR" << endl;
          cout << row + 1 << col << row << col + 1 << endl;
        }
        finalCorners++;
      }
    }

    // check bL diagonal
    count = 0;
    if (inside(row, col - 1) && v[row][col - 1] == ch) {
      count++;
      temp.insert({row, col - 1});
    }
    if (inside(row + 1, col) && v[row + 1][col] == ch) {
      count++;
      temp.insert({row + 1, col});
    }

    counted = false;
    if (count % 2 == 0) {
      int dR = row + diagonalsDirs[1].first;
      int dC = col + diagonalsDirs[1].second;
      if (!inside(dR, dC)) {
        finalCorners++;
      } else {
        if (v[dR][dC] != ch) {
          finalCorners++;
          counted = true;
        }
      }
    }

    if (count == 0 && !counted) {
      if (inside(row, col - 1) && inside(row + 1, col) &&
          v[row][col - 1] != ch && v[row + 1][col] != ch) {
        finalCorners++;
      }
    }

    // check tL diagonal
    count = 0;
    counted = false;
    if (inside(row, col - 1) && v[row][col - 1] == ch) {
      count++;
    }
    if (inside(row - 1, col) && v[row - 1][col] == ch) {
      count++;
    }
    if (count % 2 == 0) {
      int dR = row + diagonalsDirs[2].first;
      int dC = col + diagonalsDirs[2].second;
      if (!inside(dR, dC)) {
        finalCorners++;
      } else {
        if (v[dR][dC] != ch) {
          finalCorners++;
          counted = true;
        }
      }
    }

    if (count == 0 && !counted) {
      if (inside(row, col - 1) && inside(row - 1, col) &&
          v[row][col - 1] != ch && v[row - 1][col] != ch) {
        finalCorners++;
      }
    }

    // check tR diagonal
    count = 0;
    counted = false;
    if (inside(row, col + 1) && v[row][col + 1] == ch) {
      count++;
    }

    if (inside(row - 1, col) && v[row - 1][col] == ch) {
      count++;
    }

    if (count % 2 == 0) {
      int dR = row + diagonalsDirs[3].first;
      int dC = col + diagonalsDirs[3].second;
      if (!inside(dR, dC)) {
        finalCorners++;
      } else {
        if (v[dR][dC] != ch) {
          finalCorners++;
          counted = true;
        }
      }
    }
    if (count == 0 && !counted) {
      if (inside(row, col + 1) && v[row][col + 1] != ch &&
          inside(row - 1, col) && v[row - 1][col] != ch) {
        finalCorners++;
      }
    }

    return finalCorners;
  };

  int finalAns = 0;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (vis.count(v[i][j]) == 0 && visited[i][j] == -1) {
        dfs(i, j, v[i][j], dfs);
        char ch = v[i][j];
        auto q = viscoord[ch];
        int totalC = 0;
        set<pair<int, int>> temp;
        for (auto k : q) {
          int kR = k.first;
          int kC = k.second;
          int canContributeSides = 0;
          canContributeSides = corners(kR, kC, ch, temp);
          totalC += canContributeSides;
        }
        finalAns += vis[ch] * totalC;
        /*cout << ch << endl;*/
        /*for (auto it : viscoord[ch]) {*/
        /*  cout << it.first << it.second;*/
        /*}*/
        /*cout << "\n";*/
        vis.erase(ch);
        viscoord.erase(ch);
      }
    }
  }

  print(finalAns);

  return 0;
}
