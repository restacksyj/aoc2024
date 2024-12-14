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

int main() {

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

  vector<vector<int>> v(n, vector<int>(m, 0));
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
      v[position[1]][position[0]]++;
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

  /*for (auto it : robots) {*/
  /*  cout << it.first << endl;*/
  /*  cout << "positon" << it.second[0].first << it.second[0].second << endl;*/
  /*  cout << "sepeed" << it.second[1].first << it.second[1].second << endl;*/
  /*}*/

  // x is column and y is row
  /*for (auto it : v) {*/
  /*  for (auto k : it) {*/
  /*    cout << k;*/
  /*  }*/
  /*  cout << "\n";*/
  /*}*/

  int seconds = 100;
  for (auto it : robots) {
    int robot = it.first;
    int posX = it.second[0].first;
    int posY = it.second[0].second;
    int speedX = it.second[1].first;
    int speedY = it.second[1].second;
    /*cout << "init" << posX << posY << endl;*/

    for (int sec = 0; sec < seconds; sec++) {
      int dx = posX + speedX;
      int dy = posY + speedY;
      if (inside(dx, dy)) {
        posX = dx;
        posY = dy;
      } else {
        /*cout << "robot" << robot << "aiming for" << dx << dy << endl;*/
        // wrap them
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
    }
    newrobots[robot] = {posX, posY};
    /*cout << "robot" << robot << " " << posX << posY << "second" << endl;*/
  }

  for (auto q : newrobots) {
    int newx = q.second.first;
    int newy = q.second.second;
    /*cout << newx << newy << endl;*/
    newv[newx][newy]++;
  }
  for (auto it : newv) {
    for (auto some : it) {
      cout << some;
    }
    cout << endl;
  }

  int nQ = n / 2;
  int mQ = m / 2;
  // 1st quad
  cout << nQ << mQ << endl;

  int safeQuad1 = 0;
  for (int l = 0; l < nQ; l++) {
    for (int t = 0; t < mQ; t++) {
      if (newv[l][t] > 0) {
        safeQuad1 += newv[l][t];
      }
    }
  }

  int safeQuad2 = 0;
  for (int l = 0; l < nQ; l++) {
    for (int t = mQ + 1; t < m; t++) {
      if (newv[l][t] > 0) {
        safeQuad2 += newv[l][t];
      }
    }
  }

  int safeQuad3 = 0;
  for (int l = nQ + 1; l < n; l++) {
    for (int t = 0; t < mQ; t++) {
      if (newv[l][t] > 0) {
        safeQuad3 += newv[l][t];
      }
    }
  }

  int safeQuad4 = 0;
  for (int l = nQ + 1; l < n; l++) {
    for (int t = mQ + 1; t < m; t++) {
      if (newv[l][t] > 0) {
        safeQuad4 += newv[l][t];
      }
    }
  }

  cout << safeQuad2 * safeQuad1 * safeQuad3 * safeQuad4 << endl;
  return 0;
}
