#include <bits/stdc++.h>
using namespace std;

void dfs(long long num, int &ans, int blinkCurr, int blinks) {
  auto allZeroes = [&](long long num) {
    while (num > 0) {
      if (num % 10 != 0)
        return false;
      num = num/10;
    }
    return true;
  };

  if (blinkCurr == blinks) {
    ans++;
    return;
  }

  int count_digits = floor(log10(num)) + 1;
  if (num == 0) {
    dfs(1, ans, blinkCurr + 1, blinks);
  } else if (count_digits % 2 == 0) {
    long long tens = pow(10, (count_digits / 2));
    long long firsthalf = num / tens;
    long long secondhalf = num % tens;
    if (allZeroes(secondhalf)) {
      dfs(0, ans, blinkCurr + 1, blinks);
    } else {
      dfs(firsthalf, ans, blinkCurr + 1, blinks);
    }
    dfs(secondhalf, ans, blinkCurr + 1, blinks);
  } else {
    dfs(num * 2024, ans, blinkCurr + 1, blinks);
  }
}

int main() {
  ifstream f("input.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  /*vector<long long> v = {0, 1, 10, 99, 999};*/
  vector<long long> v = {125, 17};
  /*vector<long long> v = {28, 4, 3179, 96938, 0, 6617406, 490, 816207 };*/
  /*vector<long long> v = {253000, 1, 7};*/

  int blinks = 6;
  int finalAns = 0;
  for (auto it : v) {
    int tempAns = 0;
    dfs(it, tempAns, 1, blinks);
    finalAns += tempAns;
  }

  cout << finalAns << endl;

  return 0;
}
