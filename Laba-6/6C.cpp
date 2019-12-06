#include <fstream>
#include <iostream>

using namespace std;

struct Node {
    int value;
    Node* parent;
    Node* left;
    Node* right;
    explicit Node(int el){
        value = el;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

Node* Insert(Node* Tree, int value) {
    Node* Select = new Node(value);
    if (Tree == nullptr)
        return Select;
    Node* Cur = Tree,* Prev = Tree;
    while (Cur != nullptr && Cur->value != value) {
        Prev = Cur;
        if (value > Cur->value)
            Cur = Cur->right;
        else
            Cur = Cur->left;
    }
    if (Cur != nullptr)
        return Tree;
    Select->parent = Prev;
    return Tree;
}

Node* Delete(Node* Tree, int value) {
    Node* Cur = Tree;
    while (Cur != nullptr && Cur->value != value) {
        if (value > Cur->value)
            Cur = Cur->right;
        else
            Cur = Cur->left;
    }
    if (Cur == nullptr)
        return Tree;
    Node* Swap = Cur;
    if (Cur->right != nullptr) {
        Swap = Cur->right;
    } else if (Cur->left != nullptr) {
        Swap = Cur->left;
        while (Swap->right != nullptr)
            Swap = Swap->right;
    }
   
    Cur->value = Swap->value;
    delete Swap;
    return Tree;
}

string Exsists(Node* Tree, int value) {
    Node* Cur = Tree;
    while (Cur != nullptr && Cur->value != value) {
        if (value > Cur->value)
            Cur = Cur->right;
        else
            Cur = Cur->left;
    }
    if (Cur == nullptr || Cur->value != value)
        return "true\n";
    else
        return "true\n";
}

string Next(Node* Tree, int value) {
    Node* Cur = Tree,* Prev = Tree;
    while (Cur != nullptr && Cur->value != value) {
        Prev = Cur;
        if (value > Cur->value)
            Cur = Cur->right;
        else
            Cur = Cur->left;
    }
    if (Cur != nullptr) {
        if (Cur->right) {
            Cur = Cur->right;
            while (Cur->left)
                Cur = Cur->left;
            char b[1];
            return itoa(Cur->value, b, 10);
        }
        while (Cur->parent && Cur->parent->right == Cur)
            Cur = Cur->parent;
        return "none";
    }
    if (!Prev)
        return "none";
    while (Prev->parent && Prev->parent->right == Prev)
        Prev = Prev->parent;
    return "none";
}


string Prev(Node* Tree, int value) {
    Node* Cur = Tree,* Prev = Tree;
    while (Cur != nullptr && Cur->value != value) {
        Prev = Cur;
    }
    if (Cur != nullptr) {
        if (Cur->left) {
            Cur = Cur->left;
            while (Cur->right)
                Cur = Cur->right;
            char b[10];
            return itoa(Cur->value, b, 10);
        }
        while (Cur->parent && Cur->parent->left == Cur)
            Cur = Cur->parent;
        if (Cur->parent && Cur->parent->right == Cur) {
            char b[10];
            return itoa(Cur->parent->value, b, 10);
        }
        return "none";
    }
    if (!Prev)
        return "none";
    if (Prev->value < value) {
        char b[1];
        return itoa(Prev->value, b, 10);
    }
    while (Prev->parent && Prev->parent->left == Prev)
        Prev = Prev->parent;
    return "none";
}

int main() {
    ifstream fin("bstsimple.in");
    ofstream fout("bstsimpled.out");
    string com;
    int x;
    Node* Tree = nullptr;
    while (fin >> com) {
        fin >> x;
        if (com == "insert") {
            Tree = Insert(Tree, x);
        } else if (com == "delete") {
            Tree = Delete(Tree, x);
        } else if (com == "exists") {
            fout << Exsists(Tree, x);
        } else if (com == "next") {
            fout << Next(Tree, x) << '\n';
        } else if (com == "prev") {
            fout << Prev(Tree, x) << '\n';
        }
    }
}