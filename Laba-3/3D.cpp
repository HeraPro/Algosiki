#include <fstream>
using namespace std;
 
long a[100000], n;
 
void siftDown(int size, int i) {
    int help = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && a[left] > a[i]) help = left;
    if (right < size && a[right] > a[help]) help = right;
    if (help != i) {
        swap(a[i], a[help]);
        siftDown(size , help);
    }
}
 
void HeapSort() {
    for (int i = n / 2; i > -1; i--) {
        siftDown(n, i);
    }
    for (int i = n - 1; i > -1; i--) {
        swap(a[0], a[i]);
        siftDown(i, 0);
    }
}
 
int main() {
    ifstream fin("sort.in");
    ofstream fout("sort.out");
    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    HeapSort();
    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    return 0;
}