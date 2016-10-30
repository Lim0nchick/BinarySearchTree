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
    struct Node;
    BinarySearchTree();
    BinarySearchTree(const initializer_list<T>& list);
    BinarySearchTree(const BinarySearchTree& tree);
    BinarySearchTree(BinarySearchTree&& tree);
    ~BinarySearchTree();

    auto size() const noexcept -> size_t;
    auto insert(const T& value) noexcept -> bool;
    auto find(const T& value) const noexcept -> const T*;

    auto operator = (const BinarySearchTree& tree) -> BinarySearchTree&;
    auto operator = (BinarySearchTree&& tree) -> BinarySearchTree&;
    auto operator == (const BinarySearchTree& tree) -> bool;

    friend auto operator >> <> (istream& in, BinarySearchTree<T>& tree) -> istream&;
    friend auto operator << <> (ostream& out, const BinarySearchTree<T>& tree) -> ostream&;
    friend auto operator >> <> (ifstream& in, BinarySearchTree<T>& tree) -> ifstream&;
    friend auto operator << <> (ofstream& out, const BinarySearchTree<T>& tree) -> ofstream&;

private:
    Node* root_;
    size_t size_;

    struct Node {
        Node(T value) : value_(value), left_(nullptr), right_(nullptr) {}
        T value_;
        Node* left_;
        Node* right_;
    };
};