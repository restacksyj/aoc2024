#include <bits/stdc++.h>
using namespace std;

void printvec(vector<vector<string>> vec) {
  for (auto it : vec) {
    for (auto k : it) {
      cout << k;
    }
    cout << "\n";
  }
}

void printvec2(vector<vector<char>> &vec) {
  for (auto it : vec) {
    for (auto k : it) {
      cout << k;
    }
    cout << "\n";
  }
}

bool check(int row, int col, char ch, vector<vector<char>> &v, bool starting,
           int n, int m, set<pair<pair<int, int>, string>> &visited) {
  while (row != n - 1 && col != m - 1) {
    if (ch == '^') {
      if (starting) {
        v[row][col] = '.';
        visited.insert({{row, col}, "^"});
        starting = false;
      }

      int nR = row;
      while (nR >= 0 && v[nR][col] == '.') {
        if (visited.count({{nR, col}, "^"}) > 0) {
          return true;
        }
        visited.insert({{nR, col}, "^"});
        nR--;
      }

      if (nR < 0) {
        break;
      }

      if (nR >= 0 && nR < n && v[nR][col] == '#') {
        row = nR + 1;
        col += 1;
        ch = '>';
      }

    } else if (ch == '>') {
      int nC = col;
      while (nC < n && v[row][nC] == '.') {
        if (visited.count({{row, nC}, ">"}) > 0) {
          return true;
        }
        visited.insert({{row, nC}, ">"});
        nC++;
      }

      if (nC >= m) {
        break;
      }

      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row + 1;
        col = nC - 1;
        ch = 'v';
      }

    } else if (ch == 'v') {
      int nR = row;
      while (nR < m && v[nR][col] == '.') {
        if (visited.count({{nR, col}, "v"}) > 0) {
          return true;
        }
        visited.insert({{nR, col}, "v"});
        nR++;
      }

      if (nR >= n) {
        break;
      }

      if (nR >= 0 && nR < n && v[nR][col] == '#') {
        row = nR - 1;
        col -= 1;
        ch = '<';
      }
    } else if (ch == '<') {
      int nC = col;
      while (nC >= 0 && v[row][nC] == '.') {
        if (visited.count({{row, nC}, "<"}) > 0) {
          return true;
        }
        visited.insert({{row, nC}, "<"});
        nC--;
      }
      if (nC < 0) {
        break;
      }
      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row - 1;
        col = nC + 1;
        ch = '^';
      }
    }
  }
  return false;
}

int main() {

  //ifstream f("input.txt");
  ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<vector<char>> v;
  int startRow = 0;
  int startCol = 0;
  int i = 0;
  while (getline(f, s)) {
    stringstream ss(s);
    string val;
    vector<char> temp;
    int j = 0;
    while (getline(ss, val)) {
      for (auto it : val) {
        if (it == '^') {
          startRow = i;
          startCol = j;
        }
        temp.push_back(it);
        j++;
      }
    }
    v.push_back(temp);
    i++;
  }

  int n = (int)v.size();
  int m = (int)v[0].size();

  int row = startRow;
  int col = startCol;
  char ch = v[row][col];
  bool starting = true;
  vector<vector<string>> visvec(n, vector<string>(m, "."));

  while (row != n - 1 && col != m - 1) {
    if (ch == '^') {
      if (starting) {
        v[row][col] = '.';
        starting = false;
      }
      int nR = row;
      while (nR >= 0 && v[nR][col] == '.') {
        visvec[nR][col] = 'x';
        nR--;
      }
      if (nR < 0) {
        break;
      }
      if (nR >= 0 && nR < n && v[nR][col] == '#') {
        row = nR + 1;
        col += 1;
        ch = '>';
      }
    } else if (ch == '>') {
      int nC = col;
      while (nC < n && v[row][nC] == '.') {
        visvec[row][nC] = 'x';
        nC++;
      }
      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row + 1;
        col = nC - 1;
        ch = 'v';
      }
    } else if (ch == 'v') {
      int nR = row;
      while (nR < m && v[nR][col] == '.') {
        visvec[nR][col] = 'x';
        nR++;
      }
      if (nR >= n) {
        break;
      }
      if (nR >= 0 && nR < n && v[nR][col] == '#') {
        row = nR - 1;
        col -= 1;
        ch = '<';
      }
    } else if (ch == '<') {
      int nC = col;
      while (nC >= 0 && v[row][nC] == '.') {
        visvec[row][nC] = 'x';
        nC--;
      }
      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row - 1;
        col = nC + 1;
        ch = '^';
      }
    }
  }

  int ans = 0;
  vector<pair<int, int>> possibleObs;
  for (int x = 0; x < n; x++) {
    for (int y = 0; y < m; y++) {
      if (visvec[x][y] == "x") {
        possibleObs.push_back({x, y});
      }
    }
  }

  // v[startRow][startCol] = '^';
  for (auto it : possibleObs) {
    v[it.first][it.second] = '#';
    set<pair<pair<int, int>, string>> visited;
    bool newstarting = false;
    if (check(startRow, startCol, '^', v, newstarting, n, m, visited)) {
      ans++;
    }
    v[it.first][it.second] = '.';
    visited.clear();
  }

  cout << ans << endl;

  return 0;
}
