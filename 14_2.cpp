#include <bits/stdc++.h>
using namespace std;

vector<string> adv_tokenizer(string s, char del) {
  stringstream ss(s);
  string word;
  vector<string> temp;

  while (!ss.eof()) {
    getline(ss, word, del);
    temp.push_back(word);
  }
  return temp;
}

vector<int> adv_itokenizer(string s, char del) {
  stringstream ss(s);
  string word;
  vector<int> temp;

  while (!ss.eof()) {
    getline(ss, word, del);
    temp.push_back(stoi(word));
  }
  return temp;
}

bool christmas_checker_two(vector<vector<int>> somev) {
  int n = (int)somev.size();
  int m = (int)somev[0].size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (somev[i][j] > 1) {
        return false;
      }
    }
  }
  return true;
}

bool christmas_checker(vector<vector<int>> somev) {
  int n = (int)somev.size();
  int m = (int)somev[0].size();
  cout << n << m << endl;
  int nR = 0;
  int nC = (m / 2);
  if (somev[nR][nC] != 1) {
    return false;
  }

  int leftCounterCol = nC - 1;
  int leftCounterRow = 1;
  while (leftCounterCol >= 0 && leftCounterRow < n - 1) {
    if (somev[leftCounterRow][leftCounterCol] == 0) {
      return false;
    }
    leftCounterRow++;
    leftCounterCol--;
  }

  int rightCounterCol = nC + 1;
  int rightCounterRow = 1;

  while (rightCounterCol < m && rightCounterRow < n - 1) {
    if (somev[rightCounterRow][rightCounterCol] == 0) {
      return false;
    }
    rightCounterRow++;
    rightCounterCol++;
  }

  /*cout << leftCounterCol << leftCounterRow << endl;*/
  /*cout << rightCounterCol << rightCounterRow << endl;*/
  if (leftCounterRow == n - 1 && rightCounterRow == n - 1 &&
      leftCounterCol == -1 && rightCounterCol == m) {
    return true;
  }
  return false;
}

int main() {

  /*vector<vector<int>> tree = {*/
  /*    {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0},*/
  /*    {0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0}, {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},*/
  /*    {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},*/
  /*    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};*/
  /*cout << christmas_checker(tree) << endl;*/

  ifstream f("input1.txt");
  regex pattern("p\\=\\d{1,3},\\d{1,3}");
  regex pattern_v("v=-?\\d{1,3},-?\\d{1,3}");
  smatch match;

  if (!f.is_open()) {
    cerr << " error opening file" << endl;
    return 1;
  }

  string s;
  /*int n = 7;*/
  /*int m = 11;*/
  int n = 103;
  int m = 101;
  auto inside = [&](int x, int y) {
    if (x >= 0 && x < n && y >= 0 && y < m) {
      return true;
    }
    return false;
  };

  /*vector<vector<int>> v(n, vector<int>(m, 0));*/
  vector<vector<int>> newv(n, vector<int>(m, 0));
  unordered_map<int, vector<pair<int, int>>> robots;
  unordered_map<int, pair<int, int>> newrobots;

  int robotNo = 0;
  while (getline(f, s)) {
    string val = s;
    while (regex_search(val, match, pattern)) {
      string multiplier = match[0];
      vector<string> temp2 = adv_tokenizer(multiplier, '=');
      string comma = temp2[1];
      vector<int> position = adv_itokenizer(comma, ',');
      /*v[position[1]][position[0]]++;*/
      robots[robotNo].push_back({position[1], position[0]});
      val = match.suffix();
    }

    while (regex_search(val, match, pattern_v)) {
      string multiplier = match[0];
      vector<string> temp2 = adv_tokenizer(multiplier, '=');
      string comma = temp2[1];
      vector<int> position = adv_itokenizer(comma, ',');
      robots[robotNo].push_back({position[1], position[0]});
      val = match.suffix();
    }
    robotNo++;
  }

  int seconds = 0;
  while (true) {
    set<pair<int, int>> se;
    for (auto it : robots) {
      int robot = it.first;
      int posX = it.second[0].first;
      int posY = it.second[0].second;
      int speedX = it.second[1].first;
      int speedY = it.second[1].second;
      int dx = posX + speedX;
      int dy = posY + speedY;
      if (inside(dx, dy)) {
        posX = dx;
        posY = dy;
      } else {
        while (!inside(dx, dy)) {
          if (dx < 0) {
            dx += n;
          }
          if (dx >= n) {
            dx = dx - n;
          }

          if (dy >= m) {
            dy = dy - m;
          } else if (dy < 0) {
            dy += m;
          }
        }
      }
      posX = dx;
      posY = dy;
      se.insert({posX, posY});
      robots[robot].clear();
      robots[robot].push_back({posX, posY});
      robots[robot].push_back({speedX, speedY});
    }

    if (se.size() == robots.size()) {
      cout << se.size() << robots.size() << endl;
      vector<vector<int>> vec;
      for (auto it : robots) {
        newv[it.second[0].first][it.second[0].second] = 1;
      }
      for (auto it : newv) {
        for (auto k : it) {
          cout << k;
        }
        cout << "\n";
      }
      break;
    }
    seconds++;
  }

  cout << seconds << endl;

  return 0;
}
