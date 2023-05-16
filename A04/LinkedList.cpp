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
  bool contains(const NodeType& value) const;

friend LinkedList<NodeType> list_union(const LinkedList<NodeType>& u, const LinkedList<NodeType>& v) {
    LinkedList<NodeType> result(u);
    for (Node<NodeType>* curr = v.head_; curr != nullptr; curr = curr->next) {
        if (!result.contains(curr->data)) {
            result.insert_back(curr->data);
        }
    }
    return result;
}
 friend LinkedList<NodeType> list_intersection(const LinkedList<NodeType>& u, const LinkedList<NodeType>& v) {
    LinkedList<NodeType> result;
    for (Node<NodeType>* curr = u.head_; curr != nullptr; curr = curr->next) {
        if (v.contains(curr->data)) {
            result.insert_back(curr->data);
        }
    }
    return result;
}

    
private:
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
bool LinkedList<NodeType>::contains(const NodeType& value) const {
    Node<NodeType>* current = head_;
    while (current != nullptr) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}


// friend functions


int main(void) 
{
    LinkedList<int> list1;
    LinkedList<int> list2;

    // Add elements to list1
    list1.insert_back(8);
    list1.insert_back(1);
    list1.insert_back(6);

    // Add elements to list2

    list2.insert_back(9);
    list2.insert_back(1);
    list2.insert_back(2);

    // Print the two original lists
    std::cout << "List 1: ";
    list1.print();

    std::cout << "List 2: ";
    list2.print();
    cout << endl;
    // Call the union function
    LinkedList<int> union_list = list_union(list1, list2);
    std::cout << "Union of list1 and list2: ";
    union_list.print();
    cout << endl;

    // Call the intersection function
    LinkedList<int> intersection_list = list_intersection(list1, list2);
    std::cout << "Intersection of list1 and list2: ";
    intersection_list.print();

    return 0;
}