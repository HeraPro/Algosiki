#include <fstream>
using namespace std;
long n, a[100000];
int bin_up(long key) {
    long left = -1, right = n, mid;
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (a[mid] <= key) left = mid;
        else right = mid;
    }
    if (a[left] != key) return -1;
    else return left+1;
}
 
int bin_down(long key) {
    long left = -1, right = n, mid;
    while (right - left > 1) {
        mid = (left + right) / 2;
        if (a[mid] < key) left = mid;
        else right = mid;
    }
    if (a[right] != key) return -1;
    else return right+1;
}
 
int main()
{
    long m, key;
    ifstream fin("binsearch.in");
    ofstream fout("binsearch.out");
    fin >> n;
    for (int i = 0; i < n; i++) fin >> a[i];
    fin >> m;
    for (int i = 0; i < m; i++) {
        fin >> key;
        fout << bin_down(key) << " " << bin_up(key) << "\n";
    }
    fin.close();
    fout.close();
    return 0;
}