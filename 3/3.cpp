#include <bits/stdc++.h>
using namespace std;

int main() {

  ifstream f("input2.txt");
  // regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)");
  regex pattern("mul\\(\\d{1,3},\\d{1,3}\\)|do\\(\\)|don't\\(\\)");
  // figure out how to regexify don't and do
  smatch match;

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  int ans = 0;
  bool doflag = true;
  while (getline(f, s)) {
    string val = s;
    while (regex_search(val, match, pattern)) {
      string multiplier = match[0];
      if (multiplier == "don't()") {
        doflag = false;
      } else if (multiplier == "do()") {
        doflag = true;
      } else {
        if (doflag == true) {
          stringstream ss(multiplier);
          string word;
          vector<string> v;
          while (getline(ss, word, ',')) {
            v.push_back(word);
          }
          int first = stoi(v[0].substr(4));
          int second = stoi(v[1].substr(0, v[1].size() - 1));
          ans += first * second;
        }
      }
      val = match.suffix();
    }
  }

  cout << ans << endl;

  return 0;
}
