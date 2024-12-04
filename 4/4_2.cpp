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
  // ifstream f("input.txt");
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
  vector<vector<int>> vis(n, vector<int>(m, -1));

  for (int i = 0; i < (int)v.size(); i++) {
    for (int j = 0; j < (int)v[0].size(); j++) {
      char el = v[i][j];
      if (el == 'M') {
        vis[i][j] = 1;
        vector<string> directions = {"bld", "brd", "urd", "uld"};
        for (auto it : directions) {
          if (it == "bld" || it == "uld") {
            string temp = "";
            temp += 'M';
            string newDir = it == "bld" ? "brd" : "urd";
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'S'
                  /*&& vis[i][j - 2] == -1*/
              ) {
                res1 = search(v, i, j - 2, 'A', newtemp, ans, newDir);
              }
              newtemp = "M";
              if (j - 2 >= 0 && j - 2 < m && v[i][j - 2] == 'M' 
                                /*&& vis[i][j - 2] == -1*/
                            ) {
                res2 = search(v, i, j - 2, 'A', newtemp, ans, newDir);
              }
              if (res1 || res2) {
                vis[i][j - 2] = 1;
                ans++;
              }
            }
          } else if (it == "brd" || it == "urd") {
            string temp = "";
            temp += 'M';
            string newDir = it == "brd" ? "bld" : "uld";
            if (ogsearch(v, i, j, 'A', temp, ans, it)) {
              string newtemp = "S";
              bool res1 = false;
              bool res2 = false;
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'S'
                  /*&& vis[i][j + 2] == -1*/
              ) {
                res1 = search(v, i, j + 2, 'A', newtemp, ans, newDir);
              }
              newtemp = "M";
              if (j + 2 >= 0 && j + 2 < m && v[i][j + 2] == 'M'
                  /*&& vis[i][j + 2] == -1*/
              ) {
                res2 = search(v, i, j + 2, 'A', newtemp, ans, newDir);
              }
              if (res1 || res2) {
                vis[i][j + 2] = 1;
                ans++;
              }
            }
          }
        }
      }
    }
  }

//ans comes double because we are repeately counting the elements that is why divide by 2
  cout << ans/2<< endl;

  return 0;
}
