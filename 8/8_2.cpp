#include <bits/stdc++.h>
using namespace std;

int main() {
  // ifstream f("temp.txt");
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

  auto slope = [&](int x1, int y1, int x2, int y2) {
    if (x2 - x1 != 0) {
      float val = float(y2 - y1) / float(x2 - x1);
      return val;
    }
  };

  auto intercept = [&](int x, int y, float slopeval) {
    // y = mx+c;
    return float(y) - slopeval * float(x);
  };

  auto satisfy = [&](int x1, int y1, int x, int y, float slopeval,
                     float interceptval) {
    return (slope(x1, y1, x, y) == slopeval);
  };

  auto inrange = [&](int start, int end, int target) {
    return start < target && target < end;
  };

  for (auto it : u) {
    auto allNodes = it.second;
    // try out all the possible ways to establish a antinode
    for (int i = 0; i < (int)allNodes.size(); i++) {
      auto eachnode = allNodes[i];
      int x1 = eachnode.first;
      int y1 = eachnode.second;
      for (int j = 0; j < (int)allNodes.size(); j++) {
        if (i == j) {
          continue;
        }
        auto othernode = allNodes[j];
        int x2 = othernode.first;
        int y2 = othernode.second;

        float calslope = slope(x1, y1, x2, y2);
        float calintercept = intercept(x1, y1, calslope);

        // calculate for all points
        for (int k = 0; k < n; k++) {
          for (int b = 0; b < m; b++) {
            if (!inrange(x1, x2, k) &&
                !inrange(y1, y2, b) && inside(k, b) &&
                satisfy(k, b, x2, y2, calslope, calintercept)) {
              vis.insert({k, b, 1});
            }
          }
        }
        /*nxm*/
        for (int b = 0; b < m; b++) {
          if (x2 - x1 == 0 && !inrange(y1, y2, b) && inside(x1, b)) {
            cout << x1 << b << endl;
            vis.insert({x1, b, 1});
          }
        }

        for (int k = 0; k < n; k++) {
          if (y2 - y1 == 0 &&
              !inrange(x1, x2, k) && inside(k, y1)) {
            vis.insert({k, y1, 1});
          }
        }
      }
    }
  }

  /*for (auto it : vis) {*/
  /*  cout << it[0] << it[1] << endl;*/
  /*}*/
  cout << vis.size() << endl;

  return 0;
}
