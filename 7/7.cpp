#include <bits/stdc++.h>
#include <cctype>
using namespace std;

bool dfs(vector<int> &nums, int index, char operation, long long sum,
         long long &currAns) {
  if (currAns == sum) {
    return true;
  }

  if (currAns > sum || index >= (int)nums.size()) {
    return false;
  }

  long long newMul = currAns * nums[index];
  long long newAdd = currAns + nums[index];

  return dfs(nums, index + 1, '*', sum, newMul) ||
         dfs(nums, index + 1, '*', sum, newAdd) ||
         dfs(nums, index + 1, '+', sum, newMul) ||
         dfs(nums, index + 1, '+', sum, newAdd);
}

bool vtry(vector<int> &nums, long long sum) {
  long long currAnsSum = nums[0];
  long long currAnsMul = nums[0];
  return dfs(nums, 1, '*', sum, currAnsMul) ||
         dfs(nums, 1, '+', sum, currAnsSum);
}

int main() {
  ifstream f("input.txt");
  //ifstream f("input1.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  long long ans = 0;
  int j = 0;
  vector<int> unsafeLines;
  while (getline(f, s)) {
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
    if (vtry(v, sum)) {
      ans += sum;
    } else {
      unsafeLines.push_back(j);
    }

    j++;
  }

  cout << ans << endl;
  for (auto it : unsafeLines) {
    cout << it << endl;
  }

  return 0;
}
