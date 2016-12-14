#include "../include/BinarySearchTree.hpp"
#include <string>
using namespace std;
template <typename T>
void print(std::ostream& out, BinarySearchTree<T>& tree, std::string name)
{
    out << name.c_str() << ": \n";
    if (tree.empty()) out << "is empty.\n";
    else out << tree << "\n";
    return;
}

template <typename T>
void print(std::ofstream& out, BinarySearchTree<T>& tree, std::string name)
{
    out << name.c_str() << ": ";
    if (tree.empty()) out << "is empty.\n";
    else out << tree << "\n";
    return;
}

int main()
{
    BinarySearchTree<int> Tree_tmp;
    cout << "input Tree_tmp: ";
    cin << Tree_tmp;

    auto t1 = {4, 2, 3, 5, 1};

    BinarySearchTree<int> Tree1(t1);
    if (Tree1.find(5)) cout << "5 found" << endl;
    if (Tree1.find(8)) cout << "8 found" << endl;
    print(cout, Tree1, "Tree");
    if (Tree.insert(4)) cout << "4  inserted" << endl;   // Ничего не изменится, так как 4 уже есть в дереве
    if (Tree.insert(10)) cout << "10 inserted" << endl;
    print(cout, Tree, "Tree");


    print(cout, Tree_tmp, "Tree_tmp");
    ofstream fout("file.txt", ios::out);
    if (!fout.is_open()) {
        cout << "Error: can't open file" << endl;
        return 0;
    }

    BinarySearchTree<int> Tree_out;
    ifstream fin("file1.txt", ios::in);
    fin.seekg(0, ios::beg);
    fin >> Tree_out;
    cout << "file2.txt" << endl;
    print(cout, Tree_out, "Tree_out");

    auto t2 = {1, 2, 3, 4, 5};
    BinarySearchTree<int> Tree2(t2);
    print(cout, Tree2, "Tree2 before moving");
    BinarySearchTree<int> Tree2m(move(Tree2));
    print(cout, Tree2m, "Tree2 after move constructor");
    print(cout, Tree2, "Tree2 after moving");

    auto t3 = {9, 8, 10, 6, 7, 5};
    BinarySearchTree<int> Tree3(t3);
    print(cout, Tree3, "Tree3");
    Tree2m = move(Tree3);
    print(cout, Tree3, "Tree3 after moving to Tree2m by move=");
    print(cout, Tree2m, "Tree2m");

    BinarySearchTree<int> tree1(t3);
    print(cout, tree1, "tree1");
    BinarySearchTree<int> tree2(t1);
    print(cout, tree2, "tree2");
    BinarySearchTree<int> tree3(tree2);
    print(cout, tree3, "tree3 (after move constructor)");
    tree2 = tree1;
    print(cout, tree2, "tree2 (after copy= of tree1");

    if (tree2 == tree2) cout << "tree2 = tree3" << endl;
    else cout << "tree1 != tree2" << endl;
    if (tree2 == tree1) cout << "tree2 = tree1" << endl;
    else cout << "tree2 != tree1" << endl;

    auto FR = {20, 10, 26, 24, 27, 22, 21, 23, 25};
    BinarySearchTree<int> ForRemove(FR);
    print(cout, ForRemove, "ForRemove");
    ForRemove.remove(20);
    print(cout, ForRemove, "ForRemove without 20");
    if (!ForRemove.remove(12)) cout << "12 doesn't exist in ForRemove" << endl;
    return 0;
}
