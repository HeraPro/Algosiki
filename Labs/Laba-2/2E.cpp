#include <fstream>
#include <iostream>
using namespace std;
int a[30000000],n;
 
int Part(int k) {
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        if (right <= left + 1) {
            if (right == left + 1 && a[right] < a[left])
                swap (a[left], a[right]);
            return a[k];
        }
 
        int mid  = (left + right) / 2;
        swap (a[mid], a[left + 1]);
        if (a[left] > a[right])
            swap (a[left], a[right]);
        if (a[left + 1] > a[right])
            swap (a[left + 1], a[right]);
        if (a[left] > a[left + 1])
            swap (a[left], a[left + 1]);
        int pivot = a[left + 1];
        int i = left + 1;
        int j = right;
        while (i <= j) {
            while (a[++i] < pivot);
            while (a[--j] > pivot);
            if (i > j) break;
            swap(a[i], a[j]);
        }
        swap(a[j], a[left + 1]);
        if (j >= k) right = j - 1;
        if (i <= k) left = i;
    }
}
 
int main() {
    ifstream fin("kth.in");
    ofstream fout("kth.out");
    int k, A, B, C;
    fin >> n >> k >> A >> B >> C >> a[0] >> a[1];
    for (int i = 2 ; i < n ; i++ ) a[i] = A * a[i - 2] + B * a[i - 1] + C;
    fout << Part(k - 1);
    fin.close();
    fout.close();
    return 0;
}