#include <bits/stdc++.h>
using namespace std;

void search(vector<vector<char>> &v, int row, int col, char c,
                  string &temp, int &ans, string direction) {
  int aR = row;
  int aC = col;
  if (direction == "top") {
    aR -= 1;
  } else if (direction == "bottom") {
    aR += 1;
  } else if (direction == "left") {
    aC -= 1;
  } else if (direction == "right") {
    aC += 1;
  } else if (direction == "bld") {
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
    if (c == 'M') {
      temp += 'M';
      search(v, aR, aC, 'A', temp, ans, direction);
    } else if (c == 'A') {
      temp += 'A';
      search(v, aR, aC, 'S', temp, ans, direction);
    } else if (c == 'S' && temp.size() == 3 && temp == "XMA") {
      ans++;
      return;
    }
  }
  return;
}

int main() {
  ifstream f("input.txt");
   //ifstream f("input1.txt");

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

  for (int i = 0; i < (int)v.size(); i++) {
    for (int j = 0; j < (int)v[0].size(); j++) {
      char el = v[i][j];
      if (el == 'X') {
        string temp = "";
        temp += 'X';
        search(v, i, j, 'M', temp, ans, "top");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "left");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "right");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "bottom");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "bld");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "brd");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "uld");
        temp = "X";
        search(v, i, j, 'M', temp, ans, "urd");
        // search in all eight directions
      }
    }
  }
  cout << ans << endl;

  return 0;
}
