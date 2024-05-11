#include <functional>
#include <limits>

template <typename Key, typename Comparator = std::less<Key>>
class RBTree
{
    enum colorRB
    {
        Red,
        Black
    };
    class RBTreeNode;
    class RBTreeIterator;
    class constRBTreeIterator;
    using node = RBTreeNode;

public:
    using iterator = RBTreeIterator;
    using const_iterator = constRBTreeIterator;

    RBTree() : head_(new node()), size_(0) {} // default constructor

    RBTree(const RBTree &other) : RBTree() // copy constructor
    {
        for (const auto &tmp : other)
            insert(tmp);
    }

    RBTree &operator=(RBTree &&other)
    {
        if (this != &other)
        {
            clear();
            std::swap(head_, other.head_);
            std::swap(size_, other.size_);
        }
        return *this;
    }

    RBTree(RBTree &&other) : RBTree() { *this = std::move(other); } // move constructor

    RBTree(std::initializer_list<Key> const &items) : RBTree()
    {
        for (const auto &tmp : items)
            insert(tmp);
    }

    iterator find(const Key &value)
    {
        iterator it = search(value);
        if (it.current_ == nullptr)
            return end();

        return it;
    }

    const_iterator find(const Key &value) const
    {
        iterator it = search(value);
        if (it.current_ == nullptr)
            return end();

        return it;
    }

    bool empty() const
    {
        if (head_->parrent_ == nullptr)
            return true;
        else
            return false;
    }

    size_t size() const { return size_; }

    std::pair<iterator, bool> insert(const Key &value)
    {
        node *tmp = new node(value);
        return insert(tmp, true);
    }

    void clear()
    {
        recursiveClear(getRoot());
        head_->parrent_ = nullptr;
        size_ = 0;
    }

    void erase(const Key &value)
    {
        hubDeletion(search(value).current_);
        --size_;
    }

    void merge(RBTree &other)
    {
        if (this->head_ != other.head_ && other.getRoot() != nullptr)
            recursiveMerge(other.getRoot());

        other.head_->parrent_ = nullptr;
        other.head_->right_ = nullptr;
        other.head_->left_ = nullptr;
        other.size_ = 0;
    }

    size_t max_size() const { return std::numeric_limits<size_t>::max() / 2 / sizeof(RBTreeNode); }

    iterator begin()
    {
        if (head_->left_ == nullptr)
            return iterator(head_);
        else
            return iterator(head_->left_);
    }
    iterator end() { return iterator(head_); }

    const_iterator begin() const
    {
        if (head_->left_ == nullptr)
            return const_iterator(head_);
        else
            return const_iterator(head_->left_);
    }
    const_iterator end() const { return const_iterator(head_); }

    ~RBTree()
    {
        recursiveClear(getRoot());
        delete head_;
    }

private:
    void recursiveMerge(node *current)
    {
        if (current->left_ != nullptr)
            recursiveMerge(current->left_);

        if (current->right_ != nullptr)
            recursiveMerge(current->right_);

        if (this->find(current->key_) == this->end())
        {
            current->right_ = nullptr;
            current->left_ = nullptr;
            current->color_ = Red;
            this->insert(current, true);
        }
        else
            delete current;

        return;
    }

    void recursiveClear(node *current)
    {
        if (current == nullptr)
            return;

        if (current->left_ != nullptr)
            recursiveClear(current->left_);

        if (current->right_ != nullptr)
            recursiveClear(current->right_);

        delete current;
    }

    iterator search(const Key &value) const
    {
        node *current = getRoot();
        while (current != nullptr)
        {
            if (!comparator_(current->key_, value) && !comparator_(value, current->key_))
                return current;

            if (comparator_(current->key_, value)) // (value > current->key_
                current = current->right_;
            else
                current = current->left_;
        }
        return current;
    }

    node *getRoot() const { return head_->parrent_; } // хед это заглушка

    void swap(node **grandfather) // вставка
    {
        (*grandfather)->color_ = Red;
        (*grandfather)->left_->color_ = Black;
        (*grandfather)->right_->color_ = Black;
        if (*grandfather == head_->parrent_)
            (*grandfather)->color_ = Black;
    }

    void rightSmallTwist(node **grandfather, node **father, node **son)
    {
        (*grandfather)->left_ = *son;
        (*son)->parrent_ = *grandfather;
        (*son)->left_ = *father;
        (*father)->parrent_ = *son;
        (*father)->right_ = nullptr;

        *father = (*father)->parrent_;
        (*son) = (*son)->left_;
    }

    void leftSmallTwist(node **grandfather, node **father, node **son)
    {
        (*grandfather)->right_ = *son;
        (*son)->parrent_ = *grandfather;
        (*son)->right_ = *father;
        (*father)->parrent_ = (*son);
        (*father)->left_ = nullptr;

        *father = (*father)->parrent_;
        (*son) = (*son)->right_;
    }

    void rightTwist(node **grandfather, node **father)
    {
        if ((*grandfather)->parrent_->parrent_ == *grandfather)
        {
            head_->parrent_ = *father;
            (*father)->parrent_ = head_;
        }
        else
        {
            if ((*grandfather)->parrent_->left_ == *grandfather)
                (*grandfather)->parrent_->left_ = *father;
            else
                (*grandfather)->parrent_->right_ = *father;

            (*father)->parrent_ = (*grandfather)->parrent_;
        }

        (*grandfather)->parrent_ = *father;

        (*grandfather)->color_ = Red;
        if ((*father)->right_ != nullptr)
        {
            (*grandfather)->left_ = (*father)->right_;
            (*father)->right_->parrent_ = *grandfather;
        }
        else
            (*grandfather)->left_ = nullptr;

        (*father)->right_ = *grandfather;
        (*father)->color_ = Black;
    }

    void leftTwist(node **grandfather, node **father)
    {
        if ((*grandfather)->parrent_->parrent_ == *grandfather)
        {
            head_->parrent_ = *father;
            (*father)->parrent_ = head_;
        }
        else
        {
            if ((*grandfather)->parrent_->right_ == *grandfather)
                (*grandfather)->parrent_->right_ = *father;
            else
                (*grandfather)->parrent_->left_ = *father;

            (*father)->parrent_ = (*grandfather)->parrent_;
        }

        (*grandfather)->parrent_ = *father;

        (*grandfather)->color_ = Red;
        if ((*father)->left_ != nullptr)
        {
            (*grandfather)->right_ = (*father)->left_;
            (*father)->left_->parrent_ = *grandfather;
        }
        else
            (*grandfather)->right_ = nullptr;

        (*father)->left_ = *grandfather;
        (*father)->color_ = Black;
    }

    void balancingAfterInsert(node *current)
    {
        node *father = current->parrent_;
        while (current != getRoot() && father->color_ == Red)
        {
            node *grandfather = current->parrent_->parrent_;
            if (grandfather->left_ == father)
            {
                node *right_uncle = grandfather->right_;
                if (right_uncle != nullptr && right_uncle->color_ == Red)
                {
                    swap(&grandfather);
                }
                else
                {
                    if (father->right_ == current && grandfather->left_ == father)
                        rightSmallTwist(&grandfather, &father, &current);
                    else
                        rightTwist(&grandfather, &father);
                }
            }
            else
            {
                node *left_uncle = grandfather->left_;
                if (left_uncle != nullptr && left_uncle->color_ == Red)
                {
                    swap(&grandfather);
                }
                else
                {
                    if (father->left_ == current && grandfather->right_ == father)
                        leftSmallTwist(&grandfather, &father, &current);
                    if (father->right_ == current && grandfather->right_ == father)
                        leftTwist(&grandfather, &father);
                }
            }
            if (father->color_ != Red)
            {
                current = current->parrent_->parrent_;
                father = current->parrent_;
            }
        }
    }
    std::pair<iterator, bool> insert(node *new_node, bool unique) // булл - проверка на уникальность для мультисета
    {
        node *parrent_current = nullptr;
        node *current = head_->parrent_; // хед паррент всегда равен первому элементу

        while (current != nullptr) // начинаем перебор с первого элемента.
        {
            parrent_current = current;

            if (!comparator_(current->key_, new_node->key_) && !comparator_(new_node->key_, current->key_))
            {
                unique = false;
                delete new_node;
                return {iterator(current), unique};
            }
            else
            {
                if (this->comparator_(new_node->key_, current->key_))
                    current = current->left_;
                else
                    current = current->right_;
            }
        }                               // спустились вниз
        if (parrent_current == nullptr) // если дерево пустое
        {
            new_node->color_ = Black;
            new_node->parrent_ = head_;
            head_->parrent_ = new_node;
        }
        else
        {
            new_node->parrent_ = parrent_current; // цепляем парента новой ноды к текущей последней
            if (this->comparator_(new_node->key_, parrent_current->key_))
            {
                parrent_current->left_ = new_node;
            }
            else
            {
                parrent_current->right_ = new_node; // цепляем райт текущей ноды к новой
            }
            balancingAfterInsert(new_node);
        }

        ++size_;

        if (this->head_->left_ == this->head_ || this->head_->left_->left_ != nullptr) // самый маленький элемент
            this->head_->left_ = new_node;

        if (this->head_->right_ == this->head_ || this->head_->right_->right_ != nullptr) // самый большой элемент
            this->head_->right_ = new_node;

        return {iterator(new_node), true};
    }

    void hubDeletion(node *current) // распределение каким способом удалять
    {
        if (current->color_ == Red)
        {
            if (current->left_ != nullptr && current->right_ != nullptr)
                redWithTwo(current);
            else
                redWithNone(current);
        }
        else
        {
            if (current == getRoot() && current->right_ == nullptr && current->left_ == nullptr)
            {
                delete head_->parrent_;
                head_->parrent_ = nullptr;
            }
            else if (current->left_ != nullptr && current->right_ != nullptr)
                blackWithTwo(current);
            else if (current->left_ == nullptr && current->right_ == nullptr) // удаление одного черного
                blackWithNone(current);
            else
                blackWithOne(current);
        }
    }

    void leftBiggerSwap(node *current) // удаление
    {
        node *tmp = current->left_->right_;
        while (tmp->right_ != nullptr)
            tmp = tmp->right_;

        std::swap(current->key_, tmp->key_);
        hubDeletion(tmp);
    }

    void rightSmallerSwap(node *current)
    {
        node *tmp = current->right_->left_;
        while (tmp->left_ != nullptr)
            tmp = tmp->left_;

        std::swap(current->key_, tmp->key_);
        hubDeletion(tmp);
    }

    void redWithTwo(node *current)
    {
        if (current->left_->right_ != nullptr)
            leftBiggerSwap(current);
        else
        {
            std::swap(current->key_, current->left_->key_);
            hubDeletion(current->left_);
        }
    }

    void redWithNone(node *current)
    {
        if (current == head_->right_)
            head_->right_ = current->parrent_;
        else if (current == head_->left_)
            head_->left_ = current->parrent_;

        if (current->parrent_->right_ == current)
            current->parrent_->right_ = nullptr;
        else
            current->parrent_->left_ = nullptr;

        delete current;
    }

    void blackWithTwo(node *current)
    {
        if (current->left_->right_ != nullptr)
            leftBiggerSwap(current);
        else
        {
            std::swap(current->key_, current->left_->key_);
            hubDeletion(current->left_);
        }
    }

    void blackWithOne(node *current)
    {
        if (current->right_ != nullptr)
        {
            std::swap(current->key_, current->right_->key_);
            delete current->right_;
            current->right_ = nullptr;
        }
        else
        {
            std::swap(current->key_, current->left_->key_);
            delete current->left_;
            current->left_ = nullptr;
        }
    }

    void blackWithNone(node *current)
    {
        bool blackHeihgt = true;
        bool end = false;

        if (current == head_->right_)
            head_->right_ = current->parrent_;
        else if (current == head_->left_)
            head_->left_ = current->parrent_;

        while (current != head_ && !end)
        {
            if (current->parrent_->right_ == current || current == getRoot()) // запуск левостороннего алгоритма
            {
                current = current->parrent_;
                node *son = current->left_;
                node *leftGrandson = son->left_;
                node *rightGrandson = son->right_;

                if (current->color_ == Red) // 1.1-1.2 right
                {
                    if ((leftGrandson == nullptr || leftGrandson->color_ == Black) && (rightGrandson == nullptr || rightGrandson->color_ == Black))
                    {
                        std::swap(current->color_, son->color_);
                        // if (blackHeihgt)
                        // current->right_ = nullptr;
                    }
                    else
                    {
                        if (rightGrandson != nullptr && rightGrandson->color_ == Red)
                        {
                            son->right_ = rightGrandson->left_;
                            son->parrent_ = rightGrandson;
                            rightGrandson->left_ = son;
                            current->left_ = rightGrandson->right_;
                            rightGrandson->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = rightGrandson;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = rightGrandson;
                            else
                                current->parrent_->left_ = rightGrandson;
                            rightGrandson->right_ = current;
                            current->parrent_ = rightGrandson;
                            // if (blackHeihgt)
                            // current->right_ = nullptr;
                            current->color_ = Black;
                        }
                        else if (leftGrandson->color_ == Red)
                        {
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->left_ = son->right_;
                            son->right_ = current;
                            son->parrent_ = current->parrent_;
                            current->parrent_ = son;
                            // if (blackHeihgt)
                            // current->right_ = nullptr;
                            leftGrandson->color_ = Black;
                            son->color_ = Red;
                            current->color_ = Black;
                        }
                    }
                    end = true;
                }
                else
                {
                    if (son->color_ == Red)
                    {
                        if ((rightGrandson->left_ == nullptr ||rightGrandson->left_->color_ == Black) && (rightGrandson->right_ == nullptr || rightGrandson->right_->color_ == Black)) // 2.1.2
                        {
                            son->right_ = current;
                            son->color_ = Black;
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->parrent_ = son;
                            current->left_ = rightGrandson;
                            rightGrandson->parrent_ = current;
                            rightGrandson->color_ = Red;
                            // if (blackHeihgt)
                            // current->right_ = nullptr;
                        }
                        else if (rightGrandson->right_ != nullptr && rightGrandson->right_->color_ == Red) // 2.1.1
                        {
                            node *greatGrandson = rightGrandson->right_;

                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            son->right_ = greatGrandson;
                            greatGrandson->parrent_ = son;
                            rightGrandson->right_ = greatGrandson->left_;
                            greatGrandson->left_ = rightGrandson;
                            rightGrandson->parrent_ = greatGrandson;
                            current->left_ = greatGrandson->right_;
                            greatGrandson->right_ = current;
                            current->parrent_ = greatGrandson;
                            son->color_ = Black;
                            // if (blackHeihgt)
                            //     current->right_ = nullptr;
                        }
                        else if (rightGrandson->left_->color_ == Red)
                        {
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->left_ = son->right_;
                            son->right_->parrent_ = current;
                            son->right_ = current;
                            // if (blackHeihgt)
                            //     current->left_ = nullptr;

                            son->color_ = Black;
                           current->color_ = Red;
                        }
                        end = true;
                    }
                    else
                    {
                        if (rightGrandson == nullptr && leftGrandson == nullptr) // 2.2.2 - нарушает черную высоту, опустить флаг
                        {
                            son->color_ = Red;
                            delete current->right_;
                            current->right_ = nullptr;
                            if (current == getRoot())
                                current = current->parrent_;

                            blackHeihgt = false;
                        }
                        else if (leftGrandson != nullptr && leftGrandson->color_ == Red)
                        {
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->left_ = son->right_;
                            son->right_ = current;
                            current->parrent_ = son;
                            // if (blackHeihgt)
                            //     current->right_ = nullptr;
                            leftGrandson->color_ = Black;
                            rightGrandson->parrent_ = current;
                            end = true;
                        }
                        else if (rightGrandson != nullptr && rightGrandson->color_ == Red) // 2.2.1
                        {
                            son->right_ = rightGrandson->left_;
                            son->parrent_ = rightGrandson;
                            rightGrandson->left_ = son;
                            current->left_ = rightGrandson->right_;
                            rightGrandson->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = rightGrandson;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = rightGrandson;
                            else
                                current->parrent_->left_ = rightGrandson;
                            rightGrandson->right_ = current;
                            current->parrent_ = rightGrandson;
                            // if (blackHeihgt)
                            //     current->right_ = nullptr;
                            rightGrandson->color_ = Black;
                            end = true;
                        }
                    }
                }
                if (blackHeihgt)
                {
                    delete current->right_;
                    current->right_ = nullptr;
                }
                else if (current == getRoot() && !blackHeihgt)
                {
                    son->color_ = Red;
                    blackHeihgt = true;
                    current = head_;
                }
            }
            else // зеркально левая сторона
            {
                current = current->parrent_;
                node *son = current->right_;
                node *leftGrandson = son->left_;
                node *rightGrandson = son->right_;

                if (current->color_ == Red) // 1.1-1.2 left
                {
                    if ((leftGrandson == nullptr || leftGrandson->color_ == Black) && (rightGrandson == nullptr || rightGrandson->color_ == Black))
                    {
                        std::swap(current->color_, son->color_);
                        // if (blackHeihgt)
                        // current->left_ = nullptr;
                    }
                    else
                    {
                        if (leftGrandson != nullptr && leftGrandson->color_ == Red) // с
                        {
                            son->left_ = leftGrandson->right_;
                            son->parrent_ = leftGrandson;
                            leftGrandson->right_ = son;
                            current->right_ = leftGrandson->left_;
                            leftGrandson->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = leftGrandson;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = leftGrandson;
                            else
                                current->parrent_->left_ = leftGrandson;
                            leftGrandson->left_ = current;
                            current->parrent_ = leftGrandson;
                            // if (blackHeihgt)
                            // current->left_ = nullptr;
                            current->color_ = Black;
                        }
                        else if (rightGrandson->color_ == Red) // c
                        {
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->right_ = son->left_;
                            son->left_ = current;
                            son->parrent_ = current->parrent_;
                            current->parrent_ = son;
                            // if (blackHeihgt)
                            // current->left_ = nullptr;
                            rightGrandson->color_ = Black;
                            son->color_ = Red;
                            current->color_ = Black;
                        }
                    }
                    end = true;
                }
                else
                {
                    if (son->color_ == Red)
                    {
                        if ((leftGrandson->left_ == nullptr || leftGrandson->left_->color_ == Black) && (leftGrandson->right_ == nullptr || leftGrandson->right_->color_ == Black)) // 2.1.2 c
                        {
                            son->left_ = current;
                            son->color_ = Black;
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->parrent_ = son;
                            current->right_ = leftGrandson;
                            leftGrandson->parrent_ = current;
                            leftGrandson->color_ = Red;
                            // if (blackHeihgt)
                            // current->left_ = nullptr;
                        }
                        else if (leftGrandson->left_ != nullptr && leftGrandson->left_->color_ == Red) // 2.1.1 c
                        {
                            node *greatGrandson = leftGrandson->left_;

                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            son->left_ = greatGrandson;
                            greatGrandson->parrent_ = son;
                            leftGrandson->left_ = greatGrandson->right_;
                            greatGrandson->right_ = leftGrandson;
                            leftGrandson->parrent_ = greatGrandson;
                            current->right_ = greatGrandson->left_;
                            greatGrandson->left_ = current;
                            current->parrent_ = greatGrandson;
                            son->color_ = Black;
                            // if (blackHeihgt)
                            //     current->left_ = nullptr;
                        }
                        else if (leftGrandson->right_->color_ == Red) // c
                        {
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->right_ = son->left_;
                            son->left_->parrent_ = current;
                            son->left_ = current;
                            // if (blackHeihgt)
                            //     current->left_ = nullptr;

                            son->color_ = Black;
                           current->color_ = Red;
                        }
                        end = true;
                    }
                    else
                    {
                        if (rightGrandson == nullptr && leftGrandson == nullptr) // 2.2.2 - нарушает черную высоту, опустить флаг - c
                        {
                            son->color_ = Red;
                            delete current->left_;
                            current->left_ = nullptr;
                            if (current == getRoot())
                                current = current->parrent_;

                            blackHeihgt = false;
                        }
                        else if (rightGrandson != nullptr && rightGrandson->color_ == Red)
                        {
                            son->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = son;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = son;
                            else
                                current->parrent_->left_ = son;

                            current->right_ = son->left_;
                            son->left_ = current;
                            current->parrent_ = son;
                            // if (blackHeihgt)
                            //     current->left_ = nullptr;
                            rightGrandson->color_ = Black;
                            leftGrandson->parrent_ = current;
                            end = true;
                        }
                        else if (leftGrandson != nullptr && leftGrandson->color_ == Red) // 2.2.1 c
                        {
                            son->left_ = leftGrandson->right_;
                            son->parrent_ = leftGrandson;
                            leftGrandson->right_ = son;
                            current->right_ = leftGrandson->left_;
                            leftGrandson->parrent_ = current->parrent_;
                            if (current->parrent_->parrent_ == current)
                                current->parrent_->parrent_ = leftGrandson;
                            else if (current->parrent_->right_ == current)
                                current->parrent_->right_ = leftGrandson;
                            else
                                current->parrent_->left_ = leftGrandson;
                            leftGrandson->left_ = current;
                            current->parrent_ = leftGrandson;
                            // if (blackHeihgt)
                            //     current->left_ = nullptr;
                            leftGrandson->color_ = Black;
                            end = true;
                        }
                    }
                }
                if (blackHeihgt)
                {
                    delete current->left_;
                    current->left_ = nullptr;
                }
                else if (current == getRoot() && !blackHeihgt && !end)
                {
                    son->color_ = Red;
                    blackHeihgt = true;
                    current = head_;
                }
            }
        }
    }

    class RBTreeIterator
    {
        friend RBTree;

    public:
        Key &operator*() { return current_->key_; }

        iterator &operator++()
        {
            if (current_ == current_->parrent_->parrent_ && current_->color_ == Red)
            {
                current_ = current_->left_;
            }
            else
            {
                if (current_->right_ != nullptr)
                {
                    current_ = current_->right_;
                    while (current_->left_ != nullptr)
                        current_ = current_->left_;
                }
                else
                {
                    while (current_ != father()->left_ && current_ != grandfather())
                        current_ = father();

                    current_ = father();
                }
            }

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
            if (current_ == current_->parrent_->parrent_ && current_->color_ == Red)
            {
                current_ = current_->right_;
            }
            else if (current_->left_ != nullptr)
            {
                current_ = current_->left_;
                while (current_->right_ != nullptr)
                {
                    current_ = current_->right_;
                }
            }
            else
            {
                node *tmp = current_;
                while (current_ != father()->right_ && current_ != grandfather())
                    current_ = father();

                if (current_ == father()->right_)
                    current_ = father();
                else
                    current_ = tmp;
            }

            return *this;
        }

        iterator operator--(int)
        {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }

        bool operator==(const iterator &other) const { return current_ == other.current_; }
        bool operator!=(const iterator &other) const { return current_ != other.current_; }

    private:
        node *current_;
        RBTreeIterator(node *node_) : current_(node_) {}

        node *grandfather() { return current_->parrent_->parrent_; }
        node *father() { return current_->parrent_; }
    };

    class constRBTreeIterator
    {
        friend RBTree;

    public:
        constRBTreeIterator(const RBTreeIterator &other) : current_(other.current_) {}

        const Key &operator*() const { return current_->key_; }

        const_iterator &operator++()
        {
            if (current_ == current_->parrent_->parrent_ && current_->color_ == Red)
            {
                current_ = current_->left_;
            }
            else
            {
                if (current_->right_ != nullptr)
                {
                    current_ = current_->right_;
                    while (current_->left_ != nullptr)
                        current_ = current_->left_;
                }
                else
                {
                    while (current_ != father()->left_ && current_ != grandfather())
                        current_ = father();

                    current_ = father();
                }
            }

            return *this;
        }

        const_iterator operator++(int)
        {
            const_iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        const_iterator &operator--()
        {
            if (current_ == current_->parrent_->parrent_ && current_->color_ == Red)
            {
                current_ = current_->right_;
            }
            else if (current_->left_ != nullptr)
            {
                current_ = current_->left_;
                while (current_->right_ != nullptr)
                {
                    current_ = current_->right_;
                }
            }
            else
            {
                const node *tmp = current_;
                while (current_ != father()->right_ && current_ != grandfather())
                    current_ = father();

                if (current_ == father()->right_)
                    current_ = father();
                else
                    current_ = tmp;
            }

            return *this;
        }

        const_iterator operator--(int)
        {
            const_iterator tmp = *this;
            --(*this);
            return tmp;
        }

        friend bool operator==(const_iterator it1, const_iterator it2) { return it1.current_ == it2.current_; }
        friend bool operator!=(const_iterator it1, const_iterator it2) { return it1.current_ != it2.current_; }

    private:
        const node *current_;

        explicit constRBTreeIterator(const node *node_) : current_(node_) {}

        const node *grandfather() const { return current_->parrent_->parrent_; }
        const node *father() const { return current_->parrent_; }
    };

    class RBTreeNode
    {
    public:
        RBTreeNode() : key_(Key{}), parrent_(nullptr), right_(this), left_(this), color_(Red) {}
        RBTreeNode(const Key &key) : key_(key), parrent_(nullptr), right_(nullptr), left_(nullptr), color_(Red) {}
        Key key_;
        RBTreeNode *parrent_;
        RBTreeNode *right_;
        RBTreeNode *left_;
        colorRB color_;
    };

    node *head_; // узел-заглушка. паррент начало дерева. лефт - меньший эл. райт - больший эл.
    std::size_t size_;
    Comparator comparator_;
};