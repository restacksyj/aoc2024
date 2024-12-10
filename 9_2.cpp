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
  map<int, int> um;
  map<int, pair<int, int>> newum;
  set<vector<int>> vec;

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

  vector<pair<int, int>> availableSpaces;

  int i = 0;
  while (i < (int)lists.size()) {
    int start = i;
    if (lists[i] == -1) {
      while (lists[i] == -1) {
        i++;
      }
      availableSpaces.push_back({start, i});
    }
    i++;
  }

  int t = 0;
  while (t < (int)lists.size()) {
    int start = t;
    if (lists[t] != -1) {
      int el = lists[t];
      while (lists[t] == el) {
        t++;
      }
      newum[el] = {start, t - 1};
    } else {
      t++;
    }
  }

  /*for (auto it : availableSpaces) {*/
  /*  cout << it.first << it.second << endl;*/
  /*}*/

  /*for (auto it : newum) {*/
  /*  cout << it.first << it.second.first << it.second.second << endl;*/
  /*}*/

  while (id >= 0) {
    int nooffiles = um[id];
    int so = 0;
    int spacesSize = (int)availableSpaces.size();
    while (so < spacesSize) {
      int start = availableSpaces[so].first;
      int end = availableSpaces[so].second;
      int spaceAvailable = end - start;
      if (nooffiles <= spaceAvailable) {
        availableSpaces.erase(availableSpaces.begin() + so);
        int newStart = newum[id].first;
        int newEnd = newum[id].second;
        //availableSpaces.push_back({newStart, newEnd});
        for (int g = newStart; g <= newEnd; g++) {
          lists[start] = lists[g];
          lists[g] = -1;
          start++;
        }
        for (int it : lists) {
          cout << it << " ";
        }
        cout << "\n";
        break;
      }
      so++;
    }
    id--;
  }

  for (int it : lists) {
    cout << it << " ";
  }

  return 0;
}
