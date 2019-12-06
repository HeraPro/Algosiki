#include <iostream>
#include <vector>
#include <fstream>

using namespace std;
typedef struct Node{
    int value = 0;
    int height = 1;
    //Node* left = nullptr;
    //Node* right = nullptr;
    Node* parent = nullptr;
} Node;

int main() {
    ifstream fin("height.in");
    ofstream fout("height.out");
    int n, left, right, maxh = 0;
    fin >> n;
    Node a[n];
    for (int i = 0; i < n; i++) {
        fin >> a[i].value >> left >> right;
        a[left - 1].parent = &a[i];
        a[right - 1].parent = &a[i];
        if (a[i].parent != nullptr)
            a[i].height = a[i].parent->height + 1;
        if (a[i].height > maxh)
            maxh = a[i].height;
    }
    fout << maxh;
    fin.close();
    fout.close();
}