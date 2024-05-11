#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_

namespace s21 {

  template <typename T>
  class s21_vector 
  {
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using size_type = size_t;
    
  public:
    class s21_vectorIterator;
    using iterator = s21_vectorIterator;
    
    // using const_iterator = s21_vectorConstIterator;
    
    s21_vector() noexcept : array_(nullptr), size_array_(0), capacity_array_(0) {}; // default constructor, creates empty vector
    
    s21_vector(size_type n) : s21_vector()  // parameterized constructor, creates the vector of size n
    {
      if (n) {
        resize(n);
      }
    }

    s21_vector(std::initializer_list<value_type> const &items) : s21_vector() // initializer list constructor, creates vector initizialized using std::initializer_list
    {
      reserve(items.size());
      for (const auto &tmp : items) {
        try {
          new (array_ + size_array_) T(tmp);   // placement new
          ++size_array_;  
        } catch (...) {
            throw;
        }
      }
    }

    s21_vector(const s21_vector &v) // copy constructor
    {
      array_ = 
          reinterpret_cast<value_type*>(new int8_t[v.capacity_array_ * sizeof(value_type)]);
      
      try {
          std::uninitialized_copy(v.array_, v.array_ + v.size_array_, array_);
        } catch (...) {
            delete [] reinterpret_cast<int8_t*>(array_);
            throw;
        }
      
      capacity_array_ = v.capacity_array_;
      size_array_ = v.size_array_;
    }

    s21_vector(s21_vector &&v) noexcept : s21_vector() // move constructor
    {
      this->clear();
      delete [] reinterpret_cast<int8_t*>(this->array_);
      
      array_ = v.array_;
      size_array_ = v.size_array_;
      capacity_array_ = v.capacity_array_;
      
      v.array_ = nullptr;
    }

    s21_vector &operator=(s21_vector &&v) noexcept // assignment operator overload for moving object
    {
      this->clear();
      delete [] reinterpret_cast<int8_t*>(this->array_);
      
      array_ = v.array_;
      size_array_ = v.size_array_;
      capacity_array_ = v.capacity_array_;
      
      v.array_ = nullptr;

      return *this;
    }

    ~s21_vector() noexcept // destructor
    {
      if (array_) {
        for (size_t j = 0; j != size_array_; ++j) {
          (array_ + j)->~T();
        }        
        delete [] reinterpret_cast<int8_t*>(array_);
      }
    }

// Capacity =====================================================================================
    bool empty() const noexcept // checks whether the container is empty
    {
      return size_array_ ? false : true;
    }

    size_type size() const noexcept  // returns the number of elements
    {
      return size_array_;
    }

    size_type max_size() const noexcept // returns the maximum possible number of elements
    {
      size_type j = 0;
      return (j - 1) / sizeof(value_type) / 2;
    }

    void reserve(size_type new_capacity_array_)  // allocate storage of size elements and copies current array_ elements to a newely allocated array_
    {
      if (new_capacity_array_ > capacity_array_) {
        value_type *new_array = 
          reinterpret_cast<value_type*>(new int8_t[new_capacity_array_ * sizeof(value_type)]);

        try {
          std::uninitialized_copy(array_, array_ + size_array_, new_array);
        } catch (...) {
            delete [] reinterpret_cast<int8_t*>(new_array);
            throw;
        }

        for (size_t j = 0; j < size_array_; ++j) {
          array_[j].~T();  
        }
        delete [] reinterpret_cast<int8_t*>(array_); // doesn't call the destructor!
        array_ = new_array;
        capacity_array_ = new_capacity_array_;
      }
    }

    void resize(size_type new_size_array, const_reference value = T())  
    {
      if (new_size_array > capacity_array_) 
        reserve(new_size_array);
      
      try {
        for (size_t j = size_array_; j < new_size_array; ++j) {
          new (array_ + j) T(value); // placement new
        }
        size_array_ = new_size_array; 
      } catch (...) {
          throw;
      }
      
      if (new_size_array < size_array_) {
        size_array_ = new_size_array;
      }
    }

    size_type capacity() const noexcept // returns the number of elements that can be held in currently allocated storage
    {
      return capacity_array_;
    }

    void shrink_to_fit()  // reduces memory usage by freeing unused memory
    {
      if (capacity_array_ > size_array_) {
        value_type *new_array = 
          reinterpret_cast<value_type*>(new int8_t[size_array_ * sizeof(value_type)]);

        try {
          std::uninitialized_copy(array_, array_ + size_array_, new_array);
        } catch (...) {
            delete [] reinterpret_cast<int8_t*>(new_array);
            throw;
        }

        for (size_t j = 0; j < size_array_; ++j) {
          array_[j].~T();  
        }
        delete [] reinterpret_cast<int8_t*>(array_); // doesn't call the destructor!
        array_ = new_array;
        capacity_array_ = size_array_;
      }
    }

// Modifiers ====================================================================================

    void clear() noexcept  // clears the contents
    {
      for (size_t j = 0; j != size_array_; ++j) {
        (array_ + j)->~T();
      }

      size_array_ = 0;
    }

    iterator insert(iterator pos, const_reference value)  // inserts elements into concrete pos and returns the iterator that points to the new element
    {
      value_type *ptr_ = &(*this->end());
      if (pos == this->end()) {
        push_back(value);
        ptr_ = &(this->back());
      } else {
          value_type *new_pos = this->array_;
          size_t count = 0;
          while (new_pos != &(*pos))
          {
            new_pos++;
            count++;
          }
          if (capacity_array_ == size_array_) {
            reserve(2 * capacity_array_);
          }
          new_pos = this->array_;
          for (size_t i = 0; i < count; i++) {
            new_pos++;
          }
          ptr_ = &(*this->end());
          size_type j = this->size_array_;
          while(ptr_ != new_pos) {
            try {
              new (array_ + j) T(*(array_ + j - 1));  // placement new
              (array_ + j - 1)->~T();
              --ptr_;
              --j;
            } catch (...) {
                throw;
            }      
          }
          try {
            new (array_ + j) T(value);  // placement new
            ++size_array_;  
          } catch (...) {
              throw;
          }      
      }
      return iterator(ptr_);
    }

    void erase(iterator pos)  // erases element at pos
    {      
      value_type *ptr_ = &(*pos);
      
      if (ptr_ >= &(*(this->end()))) {
        throw std::out_of_range("Invalid pointer");
      }

      ptr_->~T();
      while(ptr_ != &(*(this->end())) - 1)
      {
        try {
          new (ptr_) T(*(ptr_ + 1));  // placement new  
          ptr_++;
        } catch (...) {
            throw;
        }      
      }
      ptr_->~T();
      --size_array_;
    }

    void push_back(const_reference value) 
    {
      if (!capacity_array_) {
        // array_ = new value_type[1];
        array_ = reinterpret_cast<value_type*>(new int8_t[sizeof(value_type)]);
        ++capacity_array_;
      } else {
          if (capacity_array_ == size_array_) {
            reserve(2 * capacity_array_);
          }
      }
      
      try {
        new (array_ + size_array_) T(value);   // placement new
        ++size_array_;  
      } catch (...) {
          throw;
      }
    }

    void pop_back() noexcept // removes the last element 
    {
      --size_array_;
      (array_ + size_array_)->~T();
    }

    void swap(s21_vector& other) noexcept // swaps the contents
    {
      value_type * temp_arr = this->array_;
      size_type temp_capacity_array = this->capacity_array_;
      size_type temp_size_array = this->size_array_;

      this->array_ = other.array_;
      this->capacity_array_ = other.capacity_array_;
      this->size_array_ = other.size_array_;

      other.array_ = temp_arr;
      other.capacity_array_ = temp_capacity_array;
      other.size_array_ = temp_size_array;
    }

// Element access =============================================================================

    reference at(size_type j) // access specified element with bounds checking
    {
      if (j >= size_array_) {
        throw std::out_of_range("s21_vector::_M_range_check: WTF?!");
      }
      return array_[j];
    }

    const_reference at(size_type j) const //
    {
      if (j >= size_array_) {
        throw std::out_of_range("s21_vector::_M_range_check: WTF?!");
      }
      return array_[j];
    }

    reference operator[](size_type j) noexcept // access specified element
    {
      return array_[j];
    }

    const_reference operator[](size_type j) const noexcept // access specified element
    {
      return array_[j];
    }

    reference front() noexcept// access the first element
    {
      return array_[0];
    }

    const_reference front() const noexcept// access the first element
    {
      return array_[0];
    }

    reference back() noexcept // access the last element
    {
      return array_[size_array_ - 1];
    }

    const_reference back() const noexcept // access the last element
    {
      return array_[size_array_ - 1];
    }

    value_type * data() noexcept  // direct access to the underlying array
    {
      return array_;
    }

    const value_type * data() const noexcept  // direct access to the underlying array
    {
      return array_;
    }

// Iterators ====================================================================================
    class s21_vectorIterator {
      public:
        s21_vectorIterator() : current_(nullptr) {}
        s21_vectorIterator(value_type * ptr) : current_(ptr) {}

        reference operator*() noexcept
        { 
          return *current_; 
        }

        iterator &operator++() noexcept  // prefix increment
        {
          ++current_;
          return *this;
        }

        iterator operator++(int) noexcept // postfix increment
        {
          iterator temp = *this;
          ++(*this);
          return temp;
        }

        iterator &operator--() noexcept // prefix decrement
        {
          --current_;
          return *this;
        }

        iterator operator--(int)  // postfix decrement
        {
          iterator temp = *this;
          --(*this);
          return temp;
        }

        bool operator==(const iterator &other) const noexcept
        {
          return current_ == other.current_;
        }

        bool operator!=(const iterator &other) const noexcept
        {
            return this->current_ != other.current_;
        }
      
      private:
        value_type * current_;
    };

    iterator begin()  // returns an iterator to the beginning
    {
      return s21_vectorIterator(array_);
    }

    iterator end()  //returns an iterator to the end
    {
      return s21_vectorIterator(array_ + size_array_);
    }

  private:
    T *array_;
    size_type size_array_;
    size_type capacity_array_;
  };

}

#endif  // SRC_S21_VECTOR_H_