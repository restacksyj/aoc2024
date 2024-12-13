#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> nums) {
  pair<int, int> A = {nums[0], nums[1]};
  pair<int, int> B = {nums[2], nums[3]};
  pair<int, int> p = {nums[4], nums[5]};

  int j = 0;
  int A_cost, B_cost;
  bool found = false;
  while (j <= 100) {
    int x1 = A.first * j;
    if (x1 > p.first) {
      j++;
      continue;
    }
    int x2 = (p.first - x1) % B.first;
    int y1 = A.second * j;
    if (y1 > p.second) {
      j++;
      continue;
    }
    int y2 = (p.second - y1) % B.second;
    if (x2 == 0 && y2 == 0) {
      found = true;
      A_cost = j;
      B_cost = (p.first - x1) / B.first;
      break;
    }
    j++;
  }

  if (found) {
    return A_cost * 3 + B_cost;
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
      ans += solve2(temp);
      temp.clear();
    }
  }

  cout << ans << endl;
  return 0;
}
