#include <bits/stdc++.h>
using namespace std;

vector<long long> solver(vector<long long> v) {
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

  int j = 0;
  int size = (int)v.size();
  while (j < size) {
    if (v[j] == 0) {
      v[j] = 1;
      j++;
      continue;
    }
    int count_digits = floor(log10(v[j])) + 1;
    if (count_digits % 2 == 0) {
      long long tens = pow(10, (count_digits / 2));

      long long firsthalf = v[j] / tens;
      long long secondhalf = v[j] % tens;
      if (allZeroes(secondhalf)) {
        secondhalf = 0;
      }
      // insert at j+1
      vector<long long> temp(size + 1);
      int m = 0;
      for (m = 0; m < j; m++) {
        temp[m] = v[m];
      }
      temp[m] = firsthalf;
      temp[m + 1] = secondhalf;
      for (int l = j + 1; l < size; l++) {
        temp[l + 1] = v[l];
      }
      v = temp;
      size = size + 1;
      j += 2;
    } else {
      v[j] = v[j] * 2024;
      j++;
    }
  }
  return v;
}

int main() {
  ifstream f("input.txt");

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  /*vector<long long> v = {0, 1, 10, 99, 999};*/
  /*vector<long long> v = {125, 17};*/
  vector<long long> v = {28, 4, 3179, 96938, 0, 6617406, 490, 816207 };
  /*vector<long long> v = {253000, 1, 7};*/

  int blinks = 25;

  auto printVec = [&](vector<long long> vecvec) {
    for (auto it : vecvec) {
      cout << it << " ";
    }
    cout << "\n";
  };

  for (int i = 0; i < blinks; i++) {
    cout << "On blink" << i << "size" << v.size() << endl;
    v = solver(v);
  }

  cout << v.size() << endl;

  return 0;
}
