#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef struct Node{
    int value = 0;
    int max;
    int min;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
} Node;

int main() {
    ifstream fin("check.in");
    ofstream fout("check.out");
    int n, left, right;
    fin >> n;
    Node a[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i].value >> left >> right;
        if (left != 0) {
            a[i].left = &a[left - 1];
            a[i].left->parent = &a[i];
        }
        if (right != 0) {
            a[i].right = &a[right - 1];
            a[i].right->parent = &a[i];
        }
        if (i != 0) {
            if (a[i].parent == nullptr) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            }
            if (a[i].parent->value == a[i].value) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            } else if (a[i].parent->value > a[i].value && a[i].parent->left != &a[i]) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            } else if (a[i].parent->value < a[i].value && a[i].parent->right != &a[i]) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            } else if (a[i].parent->value > a[i].value && a[i].value <= a[i].parent->min) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            } else if (a[i].parent->value < a[i].value && a[i].value >= a[i].parent->max) {
                fout << "NO";
                fin.close();
                fout.close();
                return 0;
            }
            if (a[i].parent->value > a[i].value) {
                a[i].max = a[i].parent->value;
                a[i].min = a[i].parent->min;
            }else if (a[i].parent->value < a[i].value) {
                a[i].min = a[i].parent->value;
                a[i].max = a[i].parent->max;
            }
        } else {
            a[i].min = INT32_MIN;
            a[i].max = INT32_MAX;
        }

    }
    fout << "YES";
    fin.close();
    fout.close();
    return 0;
}