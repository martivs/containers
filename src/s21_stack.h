#ifndef SRC_S21_STACK_H_
#define SRC_S21_STACK_H_

// #include <iostream> // nah! 

namespace s21 {

  template <typename T>
  class s21_stack 
  {
    using value_type = T; // T the template parameter T
    using reference = T &;  // defines the type of the reference to an element
    using const_reference = const T &;  // defines the type of the constant reference
    using size_type = size_t; // defines the type of the container size (standard type is size_t)
    class Node;

  public:
    s21_stack() : size_(0), top_(nullptr) {} // default constructor, creates empty stack
    
    s21_stack(std::initializer_list<value_type> const &items) : s21_stack() // initializer list constructor, creates stack initizialized using std::initializer_list
    {
      for (const auto &tmp : items) {
        this->push(tmp);  
      }
    }

    s21_stack(const s21_stack &s) : s21_stack() //copy constructor
    {
      if (s.top_) { 
        Node *current_node = s.top_;
        Node** array_next = new Node*[s.size_];
        
        array_next[0] = current_node;
        for (size_t i = 1; i < s.size_; ++i) {
          array_next[i] = current_node->next_;
          current_node = current_node->next_;
        }
        
        for (size_t i = s.size_ - 1; i > 0; --i) {
          this->push(*(array_next[i]->data_));
        }
        this->push(*(array_next[0]->data_));
        
        delete [] array_next;
      }
    }

    s21_stack operator=(s21_stack &s) noexcept
    {
      if (s.top_) { 
        Node *current_node = s.top_;
        Node** array_next = new Node*[s.size_];
        
        array_next[0] = current_node;
        for (size_t i = 1; i < s.size_; ++i) {
          array_next[i] = current_node->next_;
          current_node = current_node->next_;
        }
        
        for (size_t i = s.size_ - 1; i > 0; --i) {
          this->push(*(array_next[i]->data_));
        }
        this->push(*(array_next[0]->data_));
        
        delete [] array_next;
      }

      return *this;
    }

    s21_stack(s21_stack &&s) noexcept // move constructor
    {
      top_ = s.top_;
      size_ = s.size_;
      s.top_ = nullptr;
      s.size_ = 0; 
    }

    s21_stack operator=(s21_stack &&s) noexcept  // assignment operator overload for moving object
    {
      top_ = s.top_;
      size_ = s.size_;
      s.top_ = nullptr;
      s.size_ = 0;
      return *this;
    }
    
    ~s21_stack() { while (top_) {pop();}} // destructor

// Element access ===============================================================================
    const_reference top() const noexcept // accesses the top element
    {
     return *top_->data_;
    }

// Capacity =====================================================================================
    bool empty() const noexcept // checks whether the container is empty
    {
      return size_ ? 0 : 1;
    }

    size_type size() const noexcept // returns the number of elements
    {
      return size_;
    }

// Modifiers ====================================================================================
    void push(const_reference value) // inserts element at the top
    {
      Node *new_node = new Node;

      if (!top_) {
        top_ = new_node;
        new_node->next_ = nullptr;
      } else {
        new_node->next_ = top_;
        top_ = new_node;
      }
      
      new_node->data_ = reinterpret_cast<value_type*>(operator new(sizeof(value_type)));
      try {
        new (new_node->data_) T(value);  // placement new
        ++size_;  
      } catch (...) {
          throw;
      }
    }

    void pop() // removes the top element
    {
      if (top_) {
        top_->data_->~T();
        delete reinterpret_cast<int8_t*>(top_->data_);
        Node * tmp = top_->next_;
        delete top_;
        top_ = tmp;
        --size_;    
      }
    }
    
    void swap(s21_stack &other) // swaps the contents
    {
      Node *tmp_top = this->top_;
      size_type tmp_size = this->size_;
      this->size_ = other.size_;
      this->top_ = other.top_;
      other.top_ = tmp_top;
      other.size_ = tmp_size;
    }

  private:
    size_type size_;
    Node * top_;
    class Node {
      public:
        value_type * data_;
        Node * next_;
    };
  };
}

#endif  // SRC_S21_STACK_H_