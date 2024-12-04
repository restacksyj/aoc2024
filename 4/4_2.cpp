#include <bits/stdc++.h>
using namespace std;

bool search(vector<vector<char>> &v, int row, int col, char c, string &temp,
            int &ans, string direction) {
  int aR = row;
  int aC = col;
  if (direction == "bld") {
    aC -= 1;
    aR += 1;
  } else if (direction == "brd") {
    aC += 1;
    aR += 1;
  } else if (direction == "uld") {
    aC -= 1;
    aR -= 1;
  } else if (direction == "urd") {
    aC += 1;
    aR -= 1;
  }

  if (aR < (int)v.size() && aR >= 0 && aC < (int)v[0].size() && aC >= 0 &&
      v[aR][aC] == c) {
    if (c == 'A') {
      temp += 'A';
      return search(v, aR, aC, 'S', temp, ans, direction) ||
             search(v, aR, aC, 'M', temp, ans, direction);
    } else if ((c == 'S' && temp.size() == 2 && temp == "MA") ||
               (c == 'M' && temp.size() == 2 && temp == "SA")) {
      return true;
    }
  }
  return false;
}

bool ogsearch(vector<vector<char>> &v, int row, int col, char c, string &temp,
              int &ans, string direction) {
  int aR = row;
  int aC = col;
  if (direction == "bld") {
    aC -= 1;
    aR += 1;
  } else if (direction == "brd") {
    aC += 1;
    aR += 1;
  } else if (direction == "uld") {
    aC -= 1;
    aR -= 1;
  } else if (direction == "urd") {
    aC += 1;
    aR -= 1;
  }

  if (aR < (int)v.size() && aR >= 0 && aC < (int)v[0].size() && aC >= 0 &&
      v[aR][aC] == c) {
    if (c == 'A') {
      temp += 'A';
      return ogsearch(v, aR, aC, 'S', temp, ans, direction);
    } else if (c == 'S' && temp.size() == 2 && temp == "MA") {
      return true;
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
  while (getline(f, s)) {
    vector<char> temp;
    for (auto it : s) {
      temp.push_back(it);
    }
    v.push_back(temp);
  }

  int ans = 0;
  // bottom left diagonal, col -2(sam or mas),
  // bottom right diagonal, col +2(sam or mas),
  // top right diagonal, col +2(sam or mas),
  // top left diagonal, col -2(sam or mas),
  int n = (int)v.size();
  int m = (int)v[0].size();

  for (int i = 0; i < (int)v.size(); i++) {
    for (int j = 0; j < (int)v[0].size(); j++) {
      char el = v[i][j];
      if (el == 'M') {
        vector<string> directions = {"bld", "brd", "urd", "uld"};
        // vector<string> directions = {"bld"};
        for (auto it : directions) {
          if (it == "bld") {
            string temp = "";
            temp += 'M';
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'S') {
                res1 = search(v, i, j - 2, 'A', newtemp, ans, "brd");
              }
              newtemp = "M";
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'M') {
                res2 = search(v, i, j - 2, 'A', newtemp, ans, "brd");
              }
              if (res1 || res2) {
                ans++;
              }
            }
          } else if (it == "brd") {
            string temp = "";
            temp += 'M';
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'S') {
                res1 = search(v, i, j + 2, 'A', newtemp, ans, "bld");
              }
              newtemp = "M";
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'M') {
                res2 = search(v, i, j + 2, 'A', newtemp, ans, "bld");
              }
              if (res1 || res2) {
                ans++;
              }
            }
          } else if (it == "uld") {
            string temp = "";
            temp += 'M';
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'S') {
                res1 = search(v, i, j - 2, 'A', newtemp, ans, "urd");
              }
              newtemp = "M";
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'M') {
                res2 = search(v, i, j - 2, 'A', newtemp, ans, "urd");
              }
              if (res1 || res2) {
                ans++;
              }
            }
          } else if (it == "urd") {
            string temp = "";
            temp += 'M';
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'S') {
                res1 = search(v, i, j + 2, 'A', newtemp, ans, "uld");
              }
              newtemp = "M";
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'M') {
                res2 = search(v, i, j + 2, 'A', newtemp, ans, "uld");
              }
              if (res1 || res2) {
                ans++;
              }
            }
          }
        }
      }
    }
  }

  cout << ans << endl;

  return 0;
}
