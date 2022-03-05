#include "priority_queue.h"

struct PriorityQueue::Node {  
 public:
  int value;
  friend class PriorityQueue; 

 private:
  Node* next_{nullptr};
  Priority priority_{Priority:: low};

  Node(const int& value, Node* next_, Priority priority) : 
      value(value), next_(next_), priority_(priority) {}
  Node(int&& value, Node* previous, Node* next_, Priority priority) : 
      value(std::move(value)), next_(next_), priority_(priority) {}
  Node() = default;                             
};

PriorityQueue::PriorityQueue(const PriorityQueue& queue) {
  Node* current = queue.head_;
  while (current != nullptr) {
    Push(current->value, current->priority_);
    current = current->next_;
  }
  head_ = queue.head_;
  count_of_high_priority = queue.count_of_high_priority;
  count_of_medium_priority = queue.count_of_medium_priority;
  count_of_low_priority = queue.count_of_low_priority;
  size_ = queue.size_;
}

PriorityQueue::PriorityQueue(PriorityQueue&& queue) noexcept
    : head_(queue.head_),
      count_of_high_priority(queue.count_of_high_priority),
      count_of_medium_priority(queue.count_of_medium_priority),
      count_of_low_priority(queue.count_of_low_priority), size_(queue.size_) {
  queue.head_ = nullptr;
  queue.size_ = 0;
  queue.count_of_high_priority = 0;
  queue.count_of_medium_priority = 0;
  queue.count_of_low_priority = 0;
}

PriorityQueue& PriorityQueue::operator=(
    const PriorityQueue& queue) {
  if (this == &queue) {
    return *this;
  }
  Clear();
  Node* current = queue.head_;
  while (current != nullptr) {
    Push(current->value, current->priority_);
    current = current->next_;
  }
  return *this;
}

PriorityQueue& PriorityQueue::operator=(
    PriorityQueue&& queue) noexcept {
  if (this == &queue) {
    return *this;
  }
  Clear();
  size_ = queue.size_;
  head_ = queue.head_;
  count_of_high_priority = queue.count_of_high_priority;
  count_of_medium_priority = queue.count_of_medium_priority;
  count_of_low_priority = queue.count_of_low_priority;
  queue.size_ = 0;
  queue.head_ = nullptr;
  queue.count_of_high_priority = 0;
  queue.count_of_medium_priority = 0;
  queue.count_of_low_priority = 0;
  return *this;
}

int PriorityQueue::Size() const {
  return size_;
}

bool PriorityQueue::IsEmpty() const {
  return size_ == 0;
}

void PriorityQueue::Push(const int& value, Priority priority) {
  if (IsEmpty() || (count_of_high_priority == 0 &&
      (priority == Priority::high || (count_of_medium_priority == 0 && priority == Priority::medium)))) {
    Node* new_element = new Node(value, head_, priority);
    head_ = new_element;
    switch (priority) {
      case Priority::high : {
        ++count_of_high_priority;
        break;
      }
      case Priority::medium : {
        ++count_of_medium_priority;
        break;
      }
      case Priority::low : {
        ++count_of_low_priority;
        break;
      }
    }
    ++size_;
    return;
  }
  Node* new_element = new Node(value, head_, priority);
  switch (priority) {
    case Priority::high : {
      for (int i = 0; i < count_of_high_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_high_priority;
      ++size_;
      break;
    }
    case Priority::medium : {
      for (int i = 0;
           i < count_of_high_priority + count_of_medium_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_medium_priority;
      ++size_;
      break;
    }
    case Priority::low : {
      for (int i = 0; i < size_ - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_low_priority;
      ++size_;
      break;
    }
  }
}

void PriorityQueue::Pop() {
  assert(!IsEmpty());
  --size_;
  switch (head_->priority_) {
    case Priority::high : {
      --count_of_high_priority;
      break;
    }
    case Priority::medium : {
      --count_of_medium_priority;
    }
    case Priority::low : {
      --count_of_low_priority;
    }
  }
  Node* ptr = head_;
  head_ = head_->next_;
  delete ptr;
}

int PriorityQueue::GetValueOfHead() const {
  assert(!IsEmpty());
  return head_->value;
}

typename PriorityQueue::Priority PriorityQueue::GetPriorityOfHead() const {
  assert(!IsEmpty());
  return head_->priority_;
}

void PriorityQueue::Push(int&& value, Priority priority) {
  if (IsEmpty() || (count_of_high_priority == 0 &&
      (priority == Priority::high || (count_of_medium_priority == 0 &&
          (priority == Priority::medium || count_of_low_priority == 0))))) {
    Node* new_element = new Node(std::move(value), nullptr, priority);
    head_ = new_element;
    switch (priority) {
      case Priority::high : {
        ++count_of_high_priority;
        break;
      }
      case Priority::medium : {
        ++count_of_medium_priority;
      }
      case Priority::low : {
        ++count_of_low_priority;
      }
    }
    ++size_;
    return;
  }
  Node* new_element = new Node(std::move(value), head_, priority);
  switch (priority) {
    case Priority::high : {
      for (int i = 0; i < count_of_high_priority - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_high_priority;
      ++size_;
      break;
    }
    case Priority::medium : {
      for (int i = 0; i < count_of_high_priority + count_of_medium_priority - 1;
           ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_medium_priority;
      ++size_;
      break;
    }
    case Priority::low : {
      for (int i = 0; i < size_ - 1; ++i) {
        new_element->next_ = new_element->next_->next_;
      }
      Node* ptr = new_element->next_->next_;
      new_element->next_->next_ = new_element;
      new_element->next_ = ptr;
      ++count_of_low_priority;
      ++size_;
      break;
    }
  }
}

PriorityQueue::~PriorityQueue() {
  Clear();
}

void PriorityQueue::Clear() {
  while (size_ > 0) {
    Pop();
  }
}

int PriorityQueue::GetCountOfHighPriority() const {
  return count_of_high_priority;
}

int PriorityQueue::GetCountOfMediumPriority() const {
  return count_of_medium_priority;
}

int PriorityQueue::GetCountOfLowPriority() const {
  return count_of_low_priority;
}