#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream f("newinput.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  auto printvec = [&](vector<int> vec) {
    for (auto it : vec) {
      cout << it << " ";
    }
    cout << "\n";
  };

  string s;
  vector<int> lists;
  int id = 0;
  map<int, int> um;

  while (getline(f, s)) {
    int j = 0;
    for (auto it : s) {
      for (int i = 0; i < it - '0'; i++) {
        if (j % 2 == 0) {
          lists.push_back(id);
          um[id]++;
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

  printvec(lists);

  vector<int> availableSpaces;
  map<int, set<pair<int, int>>> availableSpacesMap;

  int i = 0;
  while (i < (int)lists.size()) {
    int start = i;
    if (lists[i] == -1) {
      while (lists[i] == -1) {
        i++;
      }
      availableSpacesMap[i - 1 - start].insert({start, i - 1});
    }
    i++;
  }

  cout << "Available Spaces Map after initial scan:" << endl;
  for (auto it : availableSpacesMap) {
    for (auto k : it.second) {
      cout << "Size: " << it.first << " [" << k.first << ", " << k.second << "]"
           << endl;
    }
  }

  int m = (int)lists.size() - 1;
  while (id >= 0) {
    int no_of_files = um[id];
    while (lists[m] != id) {
      m--;
    }

    int key = no_of_files;
    int map_it = 0;
    bool found = false;
    while (map_it < (int)availableSpacesMap.size()) {
      if (availableSpacesMap.count(key) > 0) {
        found = true;
        break;
      } else {
        key++;
      }
      map_it++;
    }

    if (found) {
      auto foundKeyVal = *availableSpacesMap[key].begin();
      int start = foundKeyVal.first;
      int end = foundKeyVal.second;
      bool updateKey = false;
      if (end - start + 1 > no_of_files) {
        updateKey = true;
      }

      for (int u = m; u > m - no_of_files; u--) {
        lists[start] = lists[u];
        lists[u] = -1;
        start++;
      }

      if (updateKey) {
        availableSpacesMap[end - start + 1].insert({start, end});
      }

      if (availableSpacesMap[key].size() > 0) {
        availableSpacesMap[key].erase(availableSpacesMap[key].begin());
      }
      if (availableSpacesMap[key].size() == 0) {
        availableSpacesMap.erase(key);
      }
    }
    id--;
  }

  printvec(lists);

  int z = 0;
  long long ans = 0;
  for (int it : lists) {
    if (it != -1) {
      ans += it * z;
    }
    z++;
  }

  cout << "Final answer: " << ans << endl;

  return 0;
}
