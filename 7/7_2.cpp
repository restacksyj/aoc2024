#include <bits/stdc++.h>
#include <cctype>
using namespace std;

bool dfs(vector<int> &nums, int index, long long sum, long long currAns) {
  if (index == (int)nums.size() && currAns == sum)
    return true;
  if (currAns > sum || index >= (int)nums.size())
    return false;

  long long newMul = currAns * nums[index];
  long long newAdd = currAns + nums[index];
  long long newOrOp = stoll(to_string(currAns) + to_string(nums[index]));

  return dfs(nums, index + 1, sum, newMul) ||
         dfs(nums, index + 1, sum, newAdd) ||
         dfs(nums, index + 1, sum, newOrOp);
}

bool vtry(vector<int> &nums, long long sum, int j) {
  return dfs(nums, 1, sum, nums[0]);
}

int main() {
  // ifstream f("input.txt");
  ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  int j = 0;
  long long ans = 0;
  while (getline(f, s)) {
    /*if (find(unsafeLines.begin(),unsafeLines.end(),j) == unsafeLines.end())
     * {*/
    /*  j++;*/
    /*  continue;*/
    /*}*/
    stringstream ss(s);
    string val;
    long long sum = 0;
    int i = 0;
    vector<int> v;
    while (getline(ss, val, ':')) {
      if (i == 0) {
        sum = stoll(val);
      } else {
        stringstream ss2(val);
        string val2;
        while (getline(ss2, val2, ' ')) {
          v.push_back(stoi(val2));
        }
      }
      i++;
    }

    if (vtry(v, sum, j)) {
      ans += sum;
    }

    j++;
  }

  cout << ans << endl;

  return 0;
}
