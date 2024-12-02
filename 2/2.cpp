#include <bits/stdc++.h>
using namespace std;

bool check(vector<int> nums) {
  int start = nums[0];
  string order = "ascending";
  if (start > nums[1] && nums[nums.size() - 2] > nums[nums.size() - 1]) {
    order = "descending";
  }

  bool safe = true;
  if (order == "ascending") {
    for (int i = 1; i < (int)nums.size(); i++) {
      if (nums[i] - start < 1 || nums[i] - start > 3) {
        safe = false;
        break;
      }
      start = nums[i];
    }
  } else {
    for (int i = 1; i < (int)nums.size(); i++) {
      if (start - nums[i] < 1 || start - nums[i] > 3) {
        safe = false;
        break;
      }
      start = nums[i];
    }
  }

  return safe;
}

int main() {
  //ifstream f("input.txt");
   ifstream f("input2.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  int ans = 0;
  while (getline(f, s)) {
    stringstream ss(s);
    int num;
    vector<int> nums;
    while (ss >> num) {
      nums.push_back(num);
    }
    // trying with original nums
    int start = nums[0];
    string order = "ascending";
    if (start > nums[1] && nums[nums.size() - 2] > nums[nums.size() - 1]) {
      order = "descending";
    }

    // check original nums
    bool og = check(nums);

    if (og) {
      ans++;
      continue;
    }

    // try all possible ways to remove an element
    for (int i = 0; i < (int)nums.size(); i++) {
      vector<int> newNum;
      for (int j = 0; j < (int)nums.size(); j++) {
        if (i == j)
          continue;
        newNum.push_back(nums[j]);
      }
      bool checkIf = check(newNum);
      if (checkIf) {
        /*for (auto it : newNum) {*/
        /*  cout << it << " ";*/
        /*}*/
        /*cout << "\n";*/
        ans++;
        break;
      }
    }
  }

  cout << ans << endl;
  return 0;
}
