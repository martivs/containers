#include <iostream>
#include <limits>

namespace s21
{
    template <typename T>
    class list
    {
        class ListConstIterator;
        class ListIterator;

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using size_type = size_t;

    public:
        using iterator = ListIterator;
        using const_iterator = ListConstIterator;

        list() : size_(size_type()), head_(new ListNode()), tail_(head_) {}

        list(size_type n) : list()
        {
            for (size_t i = 0; i < n; i++)
                push_front(value_type());
        }

        list(const list &l) : list()
        {
            for (const auto tmp : l)
                push_back(tmp);
        }

        list &operator=(const list &other)
        {
            if (this->head_ != other.head_)
            {
                this->clear();
                for (const auto tmp : other)
                    push_back(tmp);
            }
            return *this;
        }

        list(std::initializer_list<value_type> const &items) : list()
        {
            for (const auto tmp : items)
                push_back(tmp);
        }

        const_reference front() const { return head_->value_; }
        const_reference back() const { return tail_->prev_->value_; }

        bool empty() const { return (size_ == 0); }

        size_type size() const { return size_; }

        list &operator=(list &&l)
        {
            if (this->head_ != l.head_)
            {
                clear();
                std::swap(head_, l.head_);
                std::swap(tail_, l.tail_);
                std::swap(size_, l.size_);
            }
            return *this;
        }

        list(list &&l) : list() { *this = std::move(l); }

        size_type max_size() const { return std::numeric_limits<size_type>::max() / 2 / sizeof(ListNode); }

        iterator insert(iterator pos, const_reference value)
        {
            ListNode *new_node = new ListNode(pos.current_, pos.current_->prev_, value);
            if (pos.current_ == head_)
                head_ = new_node;
            else
                pos.current_->prev_->next_ = new_node;

            pos.current_->prev_ = new_node;
            size_++;

            return iterator(new_node);
        }

        void push_front(const_reference value) { insert(begin(), value); }

        void push_back(const_reference value) { insert(end(), value); }

        void erase(iterator pos)
        {
            pos.current_->next_->prev_ = pos.current_->prev_;
            if (pos.current_ == head_)
                head_ = pos.current_->next_;
            else
                pos.current_->prev_->next_ = pos.current_->next_;

            delete pos.current_;

            size_--;
        }
        void pop_front() { erase(begin()); }

        void pop_back() { erase(--(end())); }

        void clear()
        {
            while (head_ != tail_)
                erase(begin());
        }

        void swap(list &other)
        {
            ListNode *tmp_head_ = head_;
            ListNode *tmp_tail_ = tail_;
            head_ = other.head_;
            tail_ = other.tail_;
            other.head_ = tmp_head_;
            other.tail_ = tmp_tail_;
        }

        void reverse()
        {
            iterator it(head_);
            for (; it.current_ != tail_; --it)
                std::swap(it.current_->next_, it.current_->prev_);

            head_->next_ = tail_;
            --it;
            tail_->prev_ = head_;
            head_ = it.current_;
        }

        void unique()
        {
            iterator it(head_);
            while (it.current_ != tail_)
            {
                value_type compared_value = it.current_->value_;
                ++it;
                while (compared_value == it.current_->value_)
                {
                    iterator it_del = it++;
                    erase(it_del);
                }
            }
        }

        void splice(const_iterator pos, list &other)
        {
            ListNode *no_const = const_cast<ListNode *>(pos.current_);

            if (no_const == head_)
            {
                head_ = other.head_;
            }
            else
            {
                other.head_->prev_ = no_const->prev_;
                no_const->prev_->next_ = other.head_;
            }
            other.tail_->prev_->next_ = no_const;
            no_const->prev_ = other.tail_->prev_;
            size_+= other.size_;

            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0;
        }

        void sort()
        {
            ListNode *block_[size_]; // массив указателей на узлы из листа

            iterator it_first(head_), it_last(tail_);

            for (int i = 0; it_first.current_ != it_last.current_; ++it_first, i++)
                block_[i] = it_first.current_;

            int first = 0, last = size_ - 1;

            hoarasort(block_, first, last);
        }

        void merge(list &other)
        {
            iterator it_this = this->begin();

            while (it_this.current_->next_ != nullptr && other.head_->next_ != nullptr)
            {
                while (other.head_->next_ != nullptr && it_this.current_->value_ > other.head_->value_)
                {
                    insert(it_this, other.head_->value_);
                    other.pop_front();
                }
                if (it_this.current_->value_ <= other.head_->value_)
                    ++it_this;
            }

            if (it_this.current_->next_ == nullptr && other.head_->next_ != nullptr)
                splice(iterator(end()), other);
        }
        iterator begin() { return iterator(head_); }
        iterator end() { return iterator(tail_); }

        const_iterator begin() const { return const_iterator(head_); }
        const_iterator end() const { return const_iterator(tail_); }

        ~list()
        {
            clear();
            delete tail_;
        }

    private:
        class ListNode
        {
        public:
            ListNode() : next_(nullptr), prev_(nullptr), value_(value_type()) {}
            ListNode(ListNode *next, ListNode *prev, const_reference value) : next_(next), prev_(prev), value_(value) {}

            ListNode *next_;
            ListNode *prev_;
            value_type value_;
        };

        class ListIterator
        {
            friend list;

        public:
            reference operator*() { return current_->value_; }

            iterator &operator++()
            {
                this->current_ = this->current_->next_;
                return *this;
            }
            iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            iterator &operator--()
            {
                this->current_ = this->current_->prev_;
                return *this;
            }

            iterator operator--(int)
            {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            bool operator==(const iterator &other) const { return this->current_ == other.current_; }

            bool operator!=(const iterator &other) const { return this->current_ != other.current_; }

        private:
            ListIterator(ListNode *node) : current_(node) {}
            ListIterator(const_iterator &other) : current_(other.current_) {}
            ListNode *current_;
        };

        class ListConstIterator
        {
            friend list;

        public:
            ListConstIterator(const ListIterator &other) { current_ = other.current_; }

            const_reference operator*() const { return current_->value_; }

            const_iterator &operator++()
            {
                this->current_ = this->current_->next_;
                return *this;
            }
            const_iterator operator++(int)
            {
                iterator tmp = *this;
                ++(*this);
                return tmp;
            }

            const_iterator &operator--()
            {
                this->current_ = this->current_->prev_;
                return *this;
            }

            const_iterator operator--(int)
            {
                iterator tmp = *this;
                --(*this);
                return tmp;
            }

            friend bool operator==(const_iterator &it1, const_iterator &it2) { return it1.current_ == it2.current_; }

            friend bool operator!=(const_iterator &it1, const_iterator &it2) { return it1.current_ != it2.current_; }

        private:
            const ListNode *current_;
        };

        size_type size_;
        ListNode *head_;
        ListNode *tail_;

        void hoarasort(ListNode **block_, int first, int last)
        {
            value_type tmp, x = block_[(first + last) / 2]->value_;
            int i = first, j = last;
            do
            {
                while (block_[i]->value_ < x)
                    i++;
                while (block_[j]->value_ > x)
                    j--;

                if (i <= j)
                {
                    if (i < j)
                    {
                        tmp = block_[i]->value_;
                        block_[i]->value_ = block_[j]->value_;
                        block_[j]->value_ = tmp;
                    }
                    i++;
                    j--;
                }
            } while (i <= j); // от сюда получаем новый j который равен концу нового массива
                              // и новый i который равен началу второго нового массива
            if (i < last)
                hoarasort(block_, i, last);

            if (first < j)
                hoarasort(block_, first, j);

            // отсортировать сначала левую сторону потом правую
        }
    };
}