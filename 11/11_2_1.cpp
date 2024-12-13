#include <bits/stdc++.h>
using namespace std;

void solver(unordered_map<long long, long long> &u) {
  unordered_map<long long, long long> temp = u;
  auto allZeroes = [&](long long num) {
    string numify = to_string(num);
    int count = 0;
    for (auto it : numify) {
      if (it == '0') {
        count++;
      }
    }
    if (count == (int)numify.size())
      return true;
    return false;
  };

  for (auto it : temp) {
    long long key = it.first;
    long long value = it.second;
    u[key] -= value;
    if (key == 0) {
      u[1] += value;
      continue;
    }
    int count_digits = floor(log10(key)) + 1;
    if (count_digits % 2 == 0) {
      long long tens = pow(10, (count_digits / 2));

      long long firsthalf = key / tens;
      long long secondhalf = key % tens;
      /*if (allZeroes(secondhalf)) {*/
      /*  secondhalf = 0;*/
      /*}*/
      u[firsthalf] += value;
      u[secondhalf] += value;
    } else {
      long long nkey = key * 2024;
      u[nkey] += value;
    }
  }
}

int main() {
  /*vector<long long> v = {0, 1, 10, 99, 999};*/
  /*vector<long long> v = {125, 17};*/
  vector<long long> v = {28, 4, 3179, 96938, 0, 6617406, 490, 816207 };
  unordered_map<long long, long long> u;
  for (auto it : v) {
    u[it]++;
  }
  /*vector<long long> v = {253000, 1, 7};*/

  int blinks = 75;
  long long finalAns = 0;
  for (int i = 0; i < blinks; i++) {
    solver(u);
  }

  for (auto k : u) {
    finalAns += k.second;
  }

  cout << finalAns << endl;

  return 0;
}
