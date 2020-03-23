#include <fstream>

using namespace std;

struct Node {
    int value;
    Node* left,* right,* parent;
    int bBalance, height;
    Node() {
        value = INT32_MIN;
        left = nullptr, right = nullptr, parent = nullptr;
        bBalance = 0, height = 1;
    }
};


int main() {
    ifstream fin("balance.in");
    ofstream fout("balance.out");
    int n, left, right;
    fin >> n;
    if (n == 0)
        return 0;
    Node* Arr[n];
    for (int i = 0; i < n; i++)
        Arr[i] = new Node();
    for (int i = 0; i < n; i++) {
        fin >> Arr[i]->value >> left >> right;
        if (left) {
            Arr[i]->left = Arr[left - 1];
            Arr[left - 1]->parent = Arr[i];
        }
        if (right) {
            Arr[i]->right = Arr[right - 1];
            Arr[right - 1]->parent = Arr[i];
        }
    }
    for (int i = n - 1; i > -1; i--) {
        int h = 0;
        if (Arr[i]->right) {
            Arr[i]->bBalance = Arr[i]->right->height;
            if (Arr[i]->right->height > h)
                h = Arr[i]->right->height;
        }
        if (Arr[i]->left) {
            Arr[i]->bBalance -= Arr[i]->left->height;
            if (Arr[i]->left->height > h)
                h = Arr[i]->left->height;
        }
        Arr[i]->height = h + 1;
    }
    for (int i = 0; i < n; i++) {
        fout << Arr[i]->bBalance << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}