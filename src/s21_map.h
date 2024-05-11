#ifndef GRANDFATHER_H
#define GRANDFATHER_H
#include "rbtree.h"
#endif /* GRANDFATHER_H */
#include <iostream>
namespace s21
{
    template <typename Key, typename T>
    class Map
    {
        class Comparator;

        using key_type = Key;
        using mapped_type = T;
        using value_type = std::pair<key_type, mapped_type>;
        using reference = value_type &;
        using const_reference = const value_type &;
        using size_type = size_t;
        using tree = RBTree<value_type, Comparator>;

    public:
        using iterator = typename tree::iterator;
        using const_iterator = typename tree::const_iterator;

        Map() : tree_() {}
        Map(std::initializer_list<value_type> const &items) : Map()
        {
            for (const auto &tmp : items)
                tree_.insert(tmp);
        }

        Map(const Map &m) : tree_(m.tree_) {}

        Map &operator=(Map &&m)
        {
            tree_ = std::move(m.tree_);
            return *this;
        }

        Map(Map &&m) : tree_(std::move(m.tree_)) {}

        mapped_type &at(const Key &value)
        {
            value_type a(value, mapped_type{});
            iterator it = tree_.find(a);
            if (it == tree_.end())
                throw std::out_of_range("Map::at");

            return (*it).second;
        }
        mapped_type &operator[](const Key &value)
        {
            value_type forward(value, mapped_type{});
            iterator it = tree_.find(forward);
            if (it == tree_.end())
                it = tree_.insert(forward).first;

            return (*it).second;
        }

        void erase(iterator pos)
        {
            tree_.erase(*pos);
        }

        void swap(Map &other) { std::swap(tree_, other.tree_); }

        void merge(Map &other) { this->tree_.merge(other.tree_); }

        bool empty() const { return tree_.empty(); }

        size_t size() const { return tree_.size(); }

        size_type max_size() const { return tree_.max_size(); }

        void clear() { tree_.clear(); }

        std::pair<iterator, bool> insert(const value_type &value) { return tree_.insert(value); }

        std::pair<iterator, bool> insert(const Key &key, const T &obj)
        {
            value_type forward(key, obj);
            return tree_.insert(forward);
        }

        std::pair<iterator, bool> insert_or_assign(const Key &key, const T &obj)
        {
            value_type forward(key, obj);
            iterator it = tree_.find(forward);
            bool check = true;
            if (it == tree_.end())
                it = (insert(forward)).first;
            else
            {
                std::swap(*it, forward);
                check = false;
            }

            return {it, check};
        }

        iterator begin() { return tree_.begin(); }
        iterator end() { return tree_.end(); }

        const_iterator begin() const { return tree_.begin(); }
        const_iterator end() const { return tree_.end(); }

        bool contains(const Key &key) const
        {
            value_type forward(key, mapped_type{});
            if (tree_.find(forward) != tree_.end())
                return true;
            else
                return false;
        }

    private:
        tree tree_;

        class Comparator
        {
        public:
            bool operator()(const_reference a, const_reference b) const { return a.first < b.first; }
        };
    };
}