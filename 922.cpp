#include <bits/stdc++.h>
using namespace std;

int main() {
  ifstream f("newinput.txt");
  // 2,40,006

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
  auto cmp = [](const std::pair<int, int> &a, const std::pair<int, int> &b) {
    return a.first < b.first;
  };

  map<int, set<pair<int, int>, decltype(cmp)>> availableSpacesMap;

  int i = 0;
  while (i < (int)lists.size()) {
    int start = i;
    if (lists[i] == -1) {
      while (lists[i] == -1) {
        i++;
      }
      availableSpacesMap[i - start].insert({start, i});
    }
    i++;
  }

  /*for (auto it : availableSpacesMap) {*/
  /*  cout << "they key" << it.first << endl;*/
  /*  for (auto k : it.second) {*/
  /*    cout << k.first << k.second << endl;*/
  /*  }*/
  /*}*/

  int m = (int)lists.size() - 1;
  while (id >= 0) {
    int no_of_files = um[id];
    while (lists[m] != id) {
      m--;
    }
    int key = no_of_files;
    int map_it = 0;
    bool found = false;
    cout << key << endl;
    auto it = availableSpacesMap.lower_bound(no_of_files);
    if (it != availableSpacesMap.end()) {
      auto range = *it->second.begin();
      it->second.erase(it->second.begin());

      int start = range.first, end = range.second;
      cout << start << end << endl;
      if (m < start) {
        id--;
        continue;
      }
      bool updateKey = false;
      /*if (end - start - 1 > no_of_files) {*/
      /*  updateKey = true;*/
      /*}*/
      /*cout << updateKey << endl;*/
      /*for (int u = m; u > m - no_of_files; u--) {*/
      /*  lists[start] = lists[u];*/
      /*  lists[u] = -1;*/
      /*  printvec(lists);*/
      /*  start++;*/
      /*}*/
      for (int u = m; u > m - no_of_files; u--) {
        lists[start++] = lists[u];
        lists[u] = -1;
      }

      if (end > start && end - start > 0) {
        availableSpacesMap[end - start].insert({start, end});
      }

      /*if (updateKey) {*/
      /*  availableSpacesMap[end - start].insert({start, end});*/
      /*}*/
      if (it->second.empty()) {
        availableSpacesMap.erase(it);
      }

      /*if (availableSpacesMap[key].size() > 0) {*/
      /*  availableSpacesMap[key].erase(availableSpacesMap[key].begin());*/
      /*}*/
      /*if (availableSpacesMap[key].size() == 0) {*/
      /*  availableSpacesMap.erase(key);*/
      /*}*/
    }
    /*while (map_it < (int)availableSpacesMap.size()) {*/
    /*  if (availableSpacesMap.count(key) > 0) {*/
    /*    found = true;*/
    /*    break;*/
    /*  } else {*/
    /*    key++;*/
    /*  }*/
    /*  map_it++;*/
    /*}*/
    id--;
  }

  printvec(lists);
  int z = 0;
  long long ans = 0;
  for (int it : lists) {
    if (it != -1) {
      /*cout << it << " ";*/
      ans += it * z;
    }
    z++;
  }
  cout << ans << endl;
  return 0;
}
/*for (int u = 0; u < (int)availableSpaces.size(); u++) {*/
/*  if (availableSpaces[u] >= no_of_files) {*/
/*    int val = availableSpaces[u] - no_of_files;*/
/*    availableSpaces.erase(availableSpaces.begin() + u);*/
/*    if (val != 0) {*/
/*      availableSpaces.push_back(val);*/
/*      sort(availableSpaces.begin(), availableSpaces.end());*/
/*    }*/
/*  }*/
/*}*/
/**/
