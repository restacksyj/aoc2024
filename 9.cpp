#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream f("input.txt");
  // 2,40,006

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  vector<int> lists;
  int id = 0;
  while (getline(f, s)) {
    int j = 0;
    for (auto it : s) {
      for (int i = 0; i < it - '0'; i++) {
        if (j % 2 == 0) {
          lists.push_back(id);
        } else {
          lists.push_back(-1);
        }
      }
      j++;
      if (j % 2 == 0) {
        id++;
      }
    }
  }


  int actualL = 0;
  set<int> availableSpaces;
  for (int i = 0; i < (int)lists.size(); i++) {
    int it = lists[i];
    if (it == -1) {
      availableSpaces.insert(i);
    } else {
      actualL++;
    }
  }

  auto checker = [&](vector<int> ss) {
    int count = 0;
    for (int i = 0; i < (int)ss.size(); i++) {
      if (ss[i] == -1 && count < actualL) {
        return false;
      } else {
        count++;
      }
    }
    return true;
  };

  for (int m = (int)lists.size() - 1; m >= 0; m--) {
    if (lists[m] != -1) {
      lists[*availableSpaces.begin()] = lists[m];
      availableSpaces.erase(*availableSpaces.begin());
      lists[m] = -1;
      availableSpaces.insert(m);
      if (checker(lists)) {
        break;
      }
    }
  }

  int z = 0;
  long long ans = 0;
  for (int it : lists) {
    if (it != -1) {
      cout << it << " ";
      ans += it * z;
      z++;
    }
  }
  cout << ans << endl;

  return 0;
}
