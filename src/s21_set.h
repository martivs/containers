#ifndef GRANDFATHER_H
#define GRANDFATHER_H
#include "rbtree.h"
#endif /* GRANDFATHER_H */

#include <iostream>
namespace s21
{
    template <typename Key>
    class Set
    {
        using key_type = Key;
        using value_type = Key;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;
        using tree = RBTree<value_type>;

    public:
        using iterator = typename tree::iterator;
        using const_iterator = typename tree::const_iterator;

        Set() : tree_() {}
        Set(std::initializer_list<value_type> const &items) : Set()
        {
            for (const auto &tmp : items)
                tree_.insert(tmp);
        }

        Set(const Set &m) : tree_(m.tree_) {}

        Set &operator=(Set &&m)
        {
            tree_ = std::move(m.tree_);
            return *this;
        }

        Set(Set &&m) : tree_(std::move(m.tree_)) {}

        void erase(iterator pos) { tree_.erase(*pos); }

        void swap(Set &other) { std::swap(tree_, other.tree_); }

        void merge(Set &other) { this->tree_.merge(other.tree_); }

        bool empty() const { return tree_.empty(); }

        size_t size() const { return tree_.size(); }

        size_type max_size() const { return tree_.max_size(); }

        void clear() { tree_.clear(); }

        std::pair<iterator, bool> insert(const value_type &value) { return tree_.insert(value); }

        iterator begin() { return tree_.begin(); }
        iterator end() { return tree_.end(); }

        const_iterator begin() const { return tree_.begin(); }
        const_iterator end() const { return tree_.end(); }

        iterator find(const Key &key) { return tree_.find(key); }

        bool contains(const Key &key) const
        {
            if (tree_.find(key) != tree_.end())
                return true;
            else
                return false;
        }

    private:
        tree tree_;
    };
}