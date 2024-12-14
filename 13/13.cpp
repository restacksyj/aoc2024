#include <bits/stdc++.h>
#include <climits>
using namespace std;

long long solve(vector<int> nums) {
  pair<int, int> A = {nums[0], nums[1]};
  pair<int, int> B = {nums[2], nums[3]};
  pair<long long, long long> p = {nums[4]+1'00'000'000'000'000, nums[5]+1'00'000'000'000'000};

  for (long long j = 0; j <= 100000000; j++) {
    long long x1 = A.first * j;
    if (x1 > p.first) {
      break;
    }
    long long rem_x = p.first - x1;
    if (rem_x % B.first != 0) {
      continue;
    }

    long long y1 = A.second * j;
    if (y1 > p.second) {
      continue;
    }
    long long rem_y = p.second - y1;
    if (rem_y % B.second != 0) {
      continue;
    }
    if (rem_x / B.first != rem_y / B.second) {
      continue;
    }
    return j * 3 + rem_y / B.second;
  }

  return 0;
}

long long solve2(vector<int> &nums) {
  pair<long long, long long> A = {nums[0], nums[1]};
  pair<long long, long long> B = {nums[2], nums[3]};
  pair<long long, long long> p = {nums[4], nums[5]};
  long double A_cost, B_cost = 0;
  long long x0 = A.first;
  long long x1 = B.first;
  long long y0 = A.second;
  long long y1 = B.second;
  long long xf = p.first + 100'000'000'000'00;
  long long yf = p.second + 100'000'000'000'00;

  B_cost = (long double)((xf * y0) - (x0 * yf)) / ((x1 * y0) - (x0 * y1));
  A_cost = (long double)(yf - (y1 * B_cost)) / y0;
  long double integralPart;
  long double fractionalPartA = std::modfl(A_cost, &integralPart);
  long double fractionalPartB = std::modfl(B_cost, &integralPart);
  if (fractionalPartA != 0.0 || fractionalPartB != 0.0) {
    return 0;
  }

  return (long long)A_cost * 3 + (long long)B_cost;
}

int main() {

  ifstream f("input1.txt");
  regex pattern("X\\+\\d{1,10}|Y\\+\\d{1,10}|X\\=\\d{1,10}|Y\\=\\d{1,10}");
  smatch match;

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  long long ans = 0;
  vector<int> temp;
  while (getline(f, s)) {
    string val = s;
    while (regex_search(val, match, pattern)) {
      string multiplier = match[0];
      temp.push_back(stoi(multiplier.substr(2)));
      val = match.suffix();
    }
    if (temp.size() == 6) {
      ans += solve(temp);
      temp.clear();
    }
  }

  cout << ans << endl;
  return 0;
}
