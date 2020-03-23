#include <fstream>
using namespace std;
int main() {
    ifstream fin; fin.open("antiqs.in");
    long n;
    fin >> n; int a[n];
    fin.close();
    for (int i=0;i<n;i++) a[i]=i+1;
    for (int i = 0; i<n; i++)
        swap(a[i], a[i / 2]);
    ofstream fout; fout.open("antiqs.out");
    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    fout.close();
    return 0;
}