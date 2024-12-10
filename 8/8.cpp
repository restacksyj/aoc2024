#include <bits/stdc++.h>
using namespace std;

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

  int n = (int)v.size();
  int m = (int)v[0].size();

  unordered_map<char, vector<pair<int, int>>> u;
  set<vector<int>> vis;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (v[i][j] != '.' && v[i][j] != '#') {
        u[v[i][j]].push_back({i, j});
      }
    }
  }

  auto inside = [&](int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m) {
      return true;
    }
    return false;
  };

  for (auto it : u) {
    char node = it.first;
    auto allNodes = it.second;
    // try out all the possible ways to establish a antinode
    for (int i = 0; i < (int)allNodes.size(); i++) {
      auto eachnode = allNodes[i];
      for (int j = 0; j < (int)allNodes.size(); j++) {
        if (i == j) {
          continue;
        }
        auto othernode = allNodes[j];
        int dR = eachnode.first - othernode.first;
        int dC = eachnode.second - othernode.second;

        int possibleR = eachnode.first + dR;
        int possibleC = eachnode.second + dC;
        if (inside(possibleR, possibleC)) {
          vis.insert({possibleR, possibleC, 1});
        }
        dR = -dR;
        dC = -dC;
        possibleR = othernode.first + dR;
        possibleC = othernode.second + dC;
        if (inside(possibleR, possibleC)) {
          vis.insert({possibleR, possibleC, 1});
        }
      }
    }
  }

  cout << vis.size() << endl;

  return 0;
}
