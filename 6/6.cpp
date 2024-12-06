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
      // cout << "up" << endl;
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
        cout << "row" << row << "col" << col << "up" << endl;
        ch = '>';
      }
    } else if (ch == '>') {
      cout << "right" << endl;
      int nC = col;
      while (nC < n && v[row][nC] == '.') {
        visvec[row][nC] = 'x';
        nC++;
      }
      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row + 1;
        col = nC - 1;
        cout << "row" << row << "col" << col << "right" << endl;
        ch = 'v';
      }
    } else if (ch == 'v') {
      cout << "down" << endl;
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
        cout << "row" << row << "col" << col << "down" << endl;
        ch = '<';
      }
    } else if (ch == '<') {
      cout << "left" << endl;
      int nC = col;
      while (nC >= 0 && v[row][nC] == '.') {
        visvec[row][nC] = 'x';
        nC--;
      }
      if (nC >= 0 && nC < m && v[row][nC] == '#') {
        row = row - 1;
        col = nC + 1;
        cout << "row" << row << "col" << col << "left" << endl;
        ch = '^';
      }
    }
  }

  int ans = 0;
  for (auto it : visvec) {
    for (auto k : it) {
      if (k == "x") {
        ans++;
      }
      cout << k << "";
    }
    cout << "\n";
  }
  cout << ans << endl;

  return 0;
}
