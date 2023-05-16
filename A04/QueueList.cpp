#include <iostream>
using namespace std;

template <class NodeType> struct Node {
  NodeType data;
  Node<NodeType> *next = nullptr;
  Node<NodeType> *prev = nullptr;
};

template <class NodeType> class LinkedList {
public:
  LinkedList() = default;
  LinkedList(const LinkedList<NodeType> &that);
  LinkedList<NodeType> &operator=(const LinkedList<NodeType> &that);
  virtual ~LinkedList();
  int size() const;
  bool empty() const;
  void insert_front(const NodeType &item);
  NodeType remove_front();
  void print();
  void insert_back(const NodeType &item);
  NodeType remove_back();
  void clear();
  bool contains(const NodeType &value) const;
  Node<NodeType> *gethead();

  friend LinkedList<NodeType> list_union(const LinkedList<NodeType> &u,
                                         const LinkedList<NodeType> &v) {
    LinkedList<NodeType> result(u);
    for (Node<NodeType> *curr = v.head_; curr != nullptr; curr = curr->next) {
      if (!result.contains(curr->data)) {
        result.insert_back(curr->data);
      }
    }
    return result;
  }
  friend LinkedList<NodeType> list_intersection(const LinkedList<NodeType> &u,
                                                const LinkedList<NodeType> &v) {
    LinkedList<NodeType> result;
    for (Node<NodeType> *curr = u.head_; curr != nullptr; curr = curr->next) {
      if (v.contains(curr->data)) {
        result.insert_back(curr->data);
      }
    }
    return result;
  }

public:
  Node<NodeType> *head_ = nullptr;
  Node<NodeType> *tail_ = nullptr;
  int size_ = 0;
};

template <class NodeType>
LinkedList<NodeType>::LinkedList(const LinkedList<NodeType> &that) {
  for (Node<NodeType> *curr = that.head_; curr != nullptr; curr = curr->next) {
    insert_back(curr->data);
  }
}
template <class NodeType> Node<NodeType> *LinkedList<NodeType>::gethead() {
  return this->head_;
}

template <class NodeType>
LinkedList<NodeType> &
LinkedList<NodeType>::operator=(const LinkedList<NodeType> &that) {
  if (this != &that) {
    clear();
    for (Node<NodeType> *curr = that.head_; curr != nullptr;
         curr = curr->next) {
      insert_back(curr->data);
    }
  }
  return *this;
}

template <class NodeType> LinkedList<NodeType>::~LinkedList() { clear(); }

template <class NodeType> int LinkedList<NodeType>::size() const {
  return size_;
}

template <class NodeType> bool LinkedList<NodeType>::empty() const {
  return size_ == 0;
}

template <class NodeType>
void LinkedList<NodeType>::insert_front(const NodeType &item) {
  Node<NodeType> *new_node = new Node<NodeType>{item};
  if (empty()) {
    head_ = tail_ = new_node;
  } else {
    new_node->next = head_;
    head_->prev = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <class NodeType> NodeType LinkedList<NodeType>::remove_front() {
  if (empty()) {
    cout << "remove_front() called on empty list" << endl;
    return NULL;
  }
  NodeType data = head_->data;
  Node<NodeType> *temp = head_;
  if (size_ == 1) {
    head_ = tail_ = nullptr;
  } else {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  delete temp;
  --size_;
  return data;
}

template <class NodeType>
void LinkedList<NodeType>::insert_back(const NodeType &item) {
  Node<NodeType> *new_node = new Node<NodeType>{item};
  if (empty()) {
    head_ = tail_ = new_node;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }
  ++size_;
}

template <class NodeType> NodeType LinkedList<NodeType>::remove_back() {
  if (empty()) {
    cout << "remove_back() called on empty list" << endl;
  }
  NodeType data = tail_->data;
  Node<NodeType> *temp = tail_;
  if (size_ == 1) {
    head_ = tail_ = nullptr;
  } else {
    tail_ = tail_->prev;
    tail_->next = nullptr;
  }
  delete temp;
  --size_;
  return data;
}

template <class NodeType> void LinkedList<NodeType>::clear() {
  while (this->head_ != nullptr) {
    Node<NodeType> *temp = this->head_;
    this->head_ = this->head_->next;
    delete temp;
  }
  this->size_ = 0;
}
template <class NodeType> void LinkedList<NodeType>::print() {
  cout << "The elements in the list are: ";
  Node<NodeType> *temp = this->head_;
  while (temp != NULL) {
    cout << temp->data << " ";
    temp = temp->next;
  }
  cout << endl;
}

template <class NodeType>
bool LinkedList<NodeType>::contains(const NodeType &value) const {
  Node<NodeType> *current = head_;
  while (current != nullptr) {
    if (current->data == value) {
      return true;
    }
    current = current->next;
  }
  return false;
}
template <class NodeType> class StackList {
public:
  StackList() : n(0) {} // initialize n to zero in the constructor
  void push(NodeType data) {
    list.insert_front(data); // insert at the front of the list
    n++;                     // increment the stack counter
  }
  void pop() {
    if (!empty()) {
      list.remove_front(); // remove from the front of the list
      n--;                 // decrement the stack counter
    }
  }
  NodeType top() {
    if (!empty()) {
      return list.head_
          ->data; // return the data stored in the head node of the list
    }
  }
  bool empty() {
    return n == 0; // check if the stack counter is zero
  }
  int size() {
    return n; // return the value of the stack counter
  }

private:
  LinkedList<NodeType> list;
  int n;
};

void postfix_calculator() {
  StackList<double> stack;
  string input;
  double op1, op2, result;
  char op;

  cout << "Enter a postfix expression ending with '=': ";
  getline(cin, input);

  for (char c : input) {
    if (c == ' ')
      continue;
    else if (isdigit(c))
      stack.push(c - '0');
    else {
      op2 = stack.top();
      stack.pop();
      op1 = stack.top();
      stack.pop();
      switch (c) {
      case '+':
        result = op1 + op2;
        break;
      case '-':
        result = op1 - op2;
        break;
      case '*':
        result = op1 * op2;
        break;
      case '/':
        result = op1 / op2;
        break;
      default:
        cerr << "Invalid operator" << endl;
        exit(EXIT_FAILURE);
      }

      stack.push(result);
      cout << result << endl;
    }
  }

  if (!stack.empty()) {
    result = stack.top();
    stack.pop();
    if (stack.empty()) {
      cout << "Result: " << result << endl;
      return;
    } else
      cerr << "Invalid expression" << endl;
  } else {
    cerr << "Invalid expression" << endl;
  }
}



template <class NodeType>
class QueueList {
public:
    QueueList() = default;

    void enqueue(const NodeType& data) {
        list.insert_back(data);
        ++n;
    }

    void dequeue() {
        if (!empty()) {
            list.remove_front();
            --n;
        }
    }

    NodeType front() const {
        return list.head_->data;
    }

    bool empty() const {
        return n == 0;
    }

private:
    LinkedList<NodeType> list;
    int n = 0;
};

bool palindrome_checker(const std::string& str) {
    QueueList<char> queue;
    StackList<char> stack;
    for (char c : str) {
        if (std::isalpha(c)) {
            queue.enqueue(std::tolower(c));
            stack.push(std::tolower(c));
        }
    }

    while (!queue.empty() && !stack.empty()) {
        if (queue.front() != stack.top()) {
            return false;
        }
        queue.dequeue();
        stack.pop();
    }

    return true;
}

int main() {
    // Create a queue and enqueue some elements
    QueueList<int> q;
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.enqueue(40);

    // Dequeue some elements and print the front of the queue
    q.dequeue();
    q.dequeue();
    cout << "Front of the queue: " << q.front() << endl;

    // Check if a string is a palindrome
    string word1 = "racecar";
    string word2 = "hello";
    string sentence = "A man, a plan, a canal, Panama!";
    cout << word1 << " is a palindrome: " << palindrome_checker(word1) << endl;
    cout << word2 << " is a palindrome: " << palindrome_checker(word2) << endl;
    cout << sentence << " is a palindrome: " << palindrome_checker(sentence) << endl;

    return 0;
}