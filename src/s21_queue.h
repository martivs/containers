#ifndef SRC_S21_QUEUE_H_
#define SRC_S21_QUEUE_H_

// #include <iostream> // nah! 

namespace s21 {

  template <typename T>
  class s21_queue 
  {
    using value_type = T; // T the template parameter T
    using reference = T &;  // defines the type of the reference to an element
    using const_reference = const T &;  // defines the type of the constant reference
    using size_type = size_t; // defines the type of the container size (standard type is size_t)
    class Node;

  public:
    s21_queue() : head_(nullptr), tail_(nullptr), size_(0) {} // default constructor, creates empty stack
    
    s21_queue(std::initializer_list<value_type> const &items) : s21_queue() // initializer list constructor, creates stack initizialized using std::initializer_list
    {
      for (const auto &tmp : items) {
        this->push(tmp);  
      }
    }

    s21_queue(const s21_queue &s) : s21_queue() //copy constructor
    {
      Node *ptr = s.head_;
      while (ptr)
      {
        this->push(*ptr->data_);
        ptr = ptr->prev_;
      }
    }

    s21_queue operator=(s21_queue &s) noexcept
    {
      Node *ptr = s.head_;
      while (ptr)
      {
        this->push(*ptr->data_);
        ptr = ptr->prev_;
      }

      return *this;
    }


    s21_queue(s21_queue &&s) : s21_queue() // move constructor
    {
      this->head_ = s.head_;
      this->tail_ = s.tail_;
      this->size_ = s.size_;
      s.head_ = nullptr;
      s.tail_ = nullptr;
      s.size_ = 0;
    }

    s21_queue operator=(s21_queue &&s) noexcept  // assignment operator overload for moving object
    {
      this->head_ = s.head_;
      this->tail_ = s.tail_;
      this->size_ = s.size_;
      s.head_ = nullptr;
      s.tail_ = nullptr;
      s.size_ = 0;
      return *this;
    }
    
    ~s21_queue() { while (head_) {pop();}} // destructor

// Element access ===============================================================================
    const_reference front() const noexcept// access the first element
    {
      return *(head_->data_);
    }

    const_reference back() const noexcept //access the last element
    {
      return *(tail_->data_);
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

      if (!head_) {
        head_ = new_node;
        tail_ = new_node;
        new_node->next_ = nullptr;
        new_node->prev_ = nullptr;
      } else {
        new_node->next_ = tail_;
        tail_->prev_ = new_node;
        tail_ = new_node;
        tail_->prev_ = nullptr;        
      }
      
      new_node->data_ = reinterpret_cast<value_type*>(operator new(sizeof(value_type)));
      try {
        new (new_node->data_) T(value);  // placement new
        ++size_;  
      } catch (...) {
          throw;
      }
    }

    void pop() noexcept // removes the top element
    {
      if (head_) {
        head_->data_->~T();
        delete reinterpret_cast<int8_t*>(head_->data_);
        if (tail_ != head_) {
          Node *tmp = head_;
          head_ = head_->prev_;
          head_->next_ = nullptr;
          delete tmp;
          --size_;
        } else {
          delete head_;
          head_ = nullptr;
          tail_ = nullptr;
          --size_;
        }
      }
    }  
    
    void swap(s21_queue &other) // swaps the contents
    {
      Node * tmp = this->head_;
      this->head_ = other.head_;
      other.head_ = tmp;

      tmp = this->tail_;
      this->tail_ = other.tail_;
      other.tail_ = tmp;

      size_type tmp2 = this->size_;
      this->size_ = other.size_;
      other.size_ = tmp2;
    }

  private:
    Node * head_;
    Node * tail_;
    size_type size_;
    class Node {
      public:
        value_type * data_;
        Node * next_;
        Node * prev_;
    };
  
  };  // class s21_queue

} // namespace s21

#endif  // SRC_S21_QUEUE_H_