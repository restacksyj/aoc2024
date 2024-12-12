#include <bits/stdc++.h>
using namespace std;

struct Node {
  long long data;
  Node *next;
};

class LinkedList {

  // Pointer to the first node in the list
  Node *head;

public:
  // Constructor initializes head to NULL
  LinkedList() : head(NULL) {}

  // Function to Insert a new node at the beginning of the list
  void insertAtBeginning(long long value) {
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = head;
    head = newNode;
  }

  // Function Insert a new node at the end of the list
  void insertAtEnd(long long value) {
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = NULL;

    // If the list is empty, update the head to the new node
    if (!head) {
      head = newNode;
      return;
    }

    // Traverse to the last node
    Node *temp = head;
    while (temp->next) {
      temp = temp->next;
    }

    // Update the last node's next to the new node
    temp->next = newNode;
  }

  // Function to Insert a new node at a specific position in the list
  void insertAtPosition(long long value, int position) {
    if (position < 1) {
      cout << "Position should be >= 1." << endl;
      return;
    }

    if (position == 1) {
      insertAtBeginning(value);
      return;
    }

    Node *newNode = new Node();
    newNode->data = value;

    // Traverse to the node before the desired position
    Node *temp = head;
    for (int i = 1; i < position - 1 && temp; ++i) {
      temp = temp->next;
    }

    // If the position is out of range, print an error message
    if (!temp) {
      cout << "Position out of range." << endl;
      delete newNode;
      return;
    }

    // Insert the new node at the desired position
    newNode->next = temp->next;
    temp->next = newNode;
  }

  // Function to Delete the first node of the list
  void deleteFromBeginning() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    Node *temp = head;
    head = head->next;
    delete temp;
  }

  // Function to Delete the last node of the list
  void deleteFromEnd() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    if (!head->next) {
      delete head;
      head = NULL;
      return;
    }

    // Traverse to the second-to-last node
    Node *temp = head;
    while (temp->next->next) {
      temp = temp->next;
    }

    //  Delete the last node
    delete temp->next;
    // Set the second-to-last node's next to NULL
    temp->next = NULL;
  }

  // Function to Delete a node at a specific position in the list
  void deleteFromPosition(int position) {
    if (position < 1) {
      cout << "Position should be >= 1." << endl;
      return;
    }

    if (position == 1) {
      deleteFromBeginning();
      return;
    }

    Node *temp = head;
    for (int i = 1; i < position - 1 && temp; ++i) {
      temp = temp->next;
    }

    if (!temp || !temp->next) {
      cout << "Position out of range." << endl;
      return;
    }
    // Save the node to be deleted
    Node *nodeToDelete = temp->next;
    // Update the next pointer
    temp->next = temp->next->next;
    // Delete the node
    delete nodeToDelete;
  }

  // Function to print the nodes of  the linked list
  void display() {
    if (!head) {
      cout << "List is empty." << endl;
      return;
    }

    Node *temp = head;
    while (temp) {
      cout << temp->data << " -> ";
      temp = temp->next;
    }
    cout << "NULL" << endl;
  }
};

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

vector<long long> solver2(LinkedList &linklist) {
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

  int size = (int)v.size();
  while (linklist->) {
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
  vector<long long> v = {28, 4, 3179, 96938, 0, 6617406, 490, 816207};
  LinkedList linklist;
  for (auto it : v) {
    linklist.insertAtEnd(it);
  }
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
