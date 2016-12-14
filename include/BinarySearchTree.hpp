//
// Created by root on 30.10.16.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_BINARYSEARCHTREE_HPP

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_HPP

#include <iostream>
#include <cstddef>
#include <fstream>
#include <memory>
using namespace std;

template <typename T>
class BinarySearchTree;

template <typename T> auto operator >> (istream& in, BinarySearchTree<T>& tree) -> istream&;
template <typename T> auto operator << (ostream& out, const BinarySearchTree<T>& tree) -> ostream&;
template <typename T> auto operator >> (ifstream& in, BinarySearchTree<T>& tree) -> ifstream&;
template <typename T> auto operator << (ofstream& out, const BinarySearchTree<T>& tree) -> ofstream&;

template <typename T>
class BinarySearchTree {
public:
    struct Node
    {
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        T value;
        
        Node(T value_) : value(value_), left(nullptr), right(nullptr) {}
        
        auto _value() const noexcept -> T { return value; }

        auto symmetric(ostream& out, string lvl) const noexcept -> ostream&
        {
            if (right)
                right -> symmetric(out, lvl + '-');
            out << lvl << value << "\n";
            if (left)
                left -> symmetric(out, lvl + '-');
            return out;
        }
        
         auto direct(ofstream& out, string lvl) const noexcept -> ofstream&
        {
            out << lvl << value << "\n";
            if (left)
                left -> direct(out, lvl + '-');
            if (right)
                right -> direct(out, lvl + '-');
            return out;
        }
        
        auto equal(shared_ptr<Node> rhs) const noexcept -> bool
        {
            if ((left && !rhs->left) || (right && !rhs->right))
                return false;
            if ((!left && rhs->left) || (!right && rhs->right))
                return false;
        
            bool equalLeft = true; bool equalRight = true;
            if (value != rhs->value)
                return false;
            else 
            {
                if (!left && !right)
                    return true;
                if (left)
                    equalLeft = left->equal(rhs->left);
                if (right)
                    equalRight = right->equal(rhs->right);
                return equalLeft && equalRight;
            }
        }
      
        static auto remove(const T& value_, shared_ptr<Node>& thisNode) noexcept ->  bool
        {
            if (!thisNode)
                return false;

            if (value_ < thisNode->value)
                remove(value_, thisNode->left);
            if (value_ > thisNode->value)
                remove(value_, thisNode->right);
            if (value_ == thisNode->value) // если нашли нужный элемент
            {
                if (!thisNode->left && !thisNode->right) // если это последний лист
                {
                    thisNode = nullptr;  // удаляем его
                    return true;
                } else if (thisNode->left && !thisNode->right) // если есть путь налево, но нет направо
                {
                    thisNode = thisNode->left;
                    return true;
                } else if (!thisNode->left && thisNode->right) // если есть путь направо, но нет налево
                {
                    thisNode = thisNode->right;
                    return true;
                } else // если оба пути существуют
                {
                    shared_ptr<Node> newRight = thisNode->right;
                    thisNode = thisNode->left;
                    shared_ptr<Node> newThisNode = thisNode;
                    while (newThisNode->right)
                        newThisNode = newThisNode->right;
                    newThisNode->right = newRight;
                    return true;
                }
            }
        }

        static auto copy(shared_ptr<Node> lhs, shared_ptr<Node> rhs) -> shared_ptr<Node>
        {
            if (lhs->value != rhs->value) // если данные узлы не равны
                lhs->value = rhs->value;  // делаем их равными

            if (!lhs->left && rhs->left) // если левой ветви нет, а должна быть, выделяем под левый узел память
                lhs->left = std::make_shared<Node>(rhs->left->value); // и инициализируем нужным значением
            if (!lhs->right && rhs->right) // аналогично если правой ветки нет
                lhs->right = std::make_shared<Node>(rhs->right->value);

            if (lhs->left && !rhs->left) // если левая ветка есть, а ее быть не должно
                lhs->left = nullptr;
            if (lhs->right && !rhs->right) // аналогично если правая ветка есть, а ее быть не должно
                lhs->right = nullptr;

            if (lhs->left)
                lhs->left = copy(lhs->left, rhs->left);
            if (lhs->right)
                lhs->right = copy(lhs->right, rhs->right);

            return lhs;
        }

        ~Node()
        {
            left = nullptr;
            right = nullptr;
        }
    };

    BinarySearchTree() : root(nullptr), size_(0) {}
    BinarySearchTree(const initializer_list<T>& list);
    BinarySearchTree(BinarySearchTree&& rhs);
    BinarySearchTree(const BinarySearchTree& tree);
    
    auto size() const noexcept -> size_t;
    bool empty() const noexcept;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;
    auto remove(const T& value) noexcept -> bool;

    auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&;
    auto operator = (BinarySearchTree&& tree) -> BinarySearchTree&;
    auto operator == (const BinarySearchTree& tree) -> bool;

    friend auto operator >> (istream& in, BinarySearchTree<T>& tree) -> istream&;
    friend auto operator << (ostream& out, const BinarySearchTree<T>& tree) -> ostream&;
    friend auto operator >> (ifstream& in, BinarySearchTree<T>& tree) -> ifstream&;
    friend auto operator << (ofstream& out, const BinarySearchTree<T>& tree) -> ofstream&;

    friend auto operator << (ostream& out, const BinarySearchTree<T>& tree) -> ostream&
    {
        tree.root->direct(out, "");
        return out;
    }
    
    friend auto operator << (ostream& out, const BinarySearchTree<T>& tree) -> ostream&
    {
        tree.root->symmetric(out, "");
        return out;
    }
    friend auto operator >> (istream& in, BinarySearchTree<T>& tree) -> istream&
    {
        size_t n;
        if (!(in >> n))
        {
            cout << "wrong type of number of elements" << endl;
            return in;
        }
        tree.size_ = n;
        for (int i = 0; i < n; ++i)
        {
            T value;
            if(in >> value)
                tree.insert(value);
            else
            {
                cout << "wrong input data" << endl;
                return in;
            }
        }
        return in;
    }

    auto operator = (BinarySearchTree&& rhs) -> BinarySearchTree&;
    auto operator = (const BinarySearchTree& rhs) -> BinarySearchTree&;
    auto operator == (const BinarySearchTree& rhs) -> bool;

    ~BinarySearchTree();
    
    private:
    size_t size_;
    shared_ptr<Node> root;
};

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const initializer_list<T> &list) : size_(list.size()), root(nullptr)
{
    for (auto it = list.begin(); it != list.end(); ++it)
        insert(*it);
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree &&rhs) : size_(rhs.size_), root(rhs.root)
{
    rhs.size_ = 0;
    rhs.root = nullptr;
}

template <typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs) : size_(rhs.size_), root(std::make_shared<Node>(0))
{
    root = Node::copy(root, rhs.root);
}

template <typename T>
auto BinarySearchTree<T>::size() const noexcept -> size_t { return size_; }

template <typename T>
auto BinarySearchTree<T>::empty() const noexcept -> bool
{
    if (size())
        return false;
    else
        return true;
}

template <typename T>
auto BinarySearchTree<T>::insert(const T& value) noexcept -> bool
{
    bool foundPlace = false;
    if (root == nullptr)
    {
        root = make_shared<Node>(value);
        return true;
    }
    shared_ptr<Node> thisNode = root;
    while (!foundPlace)
    {
        if (value == thisNode->value)
            return false;
        if (value < thisNode->value)
        {
            if (!thisNode->left)
            {
                thisNode->left = std::make_shared<Node>(value);
                foundPlace = true;
            } else
                thisNode = thisNode->left;
        } else if (!thisNode->right)
        {
            thisNode->right = make_shared<Node>(value);
            foundPlace = true;
        } else
            thisNode = thisNode->right;
    }
    size_++;
    return foundPlace;
}

template <typename T>
auto BinarySearchTree<T>::find(const T& value) const noexcept -> const T*
{
    if (!root)
        return nullptr;
    shared_ptr<Node> thisNode = root;
    while(1)
    {
        if (value == thisNode->value) {
            return &thisNode->value;
        }
        else if (value < thisNode->value)
            if (thisNode->left)
                thisNode = thisNode->left;
            else {
                return nullptr;
            }
        else {
            if (thisNode->right)
                thisNode = thisNode->right;
            else
                return nullptr;
        }
    }
}

template <typename T>
auto BinarySearchTree<T>::remove(const T& value) noexcept -> bool
{
    bool foundValue = false;
    if (root)
        foundValue = Node::remove(value, root);
    else
        return false;
    if (foundValue)
        size_--;
    return foundValue;
}

template <typename T>
auto BinarySearchTree<T>::operator=(BinarySearchTree &&rhs) -> BinarySearchTree&
{
    if (this == &rhs)
        return *this;

    size_ = rhs.size_;
    rhs.size_ = 0;
    root = rhs.root;
    rhs.root = nullptr;
    return *this;
}

template <typename T>
auto BinarySearchTree<T>::operator=(const BinarySearchTree &rhs) -> BinarySearchTree&
{
    if (this == &rhs)
        return *this;

    size_ = rhs.size_;
    cout << "ok\n";
    root = Node::copy(root, rhs.root);
    cout << "ok2\n";
    return *this;
}

template <typename T>
auto BinarySearchTree<T>::operator==(const BinarySearchTree &rhs) -> bool
{
    if (root->equal(rhs.root))
        return true;
    else
        return false;
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    root = nullptr;
    size_ = 0;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
