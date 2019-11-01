#include <fstream>
using namespace std;
long n, a[100005];
int main()
{
    ifstream fin("isheap.in");
    ofstream fout("isheap.out");
    fin >> n;
    for (int i = 1; i < n+1; i++) fin >> a[i];
    for (int i = 1; i < n / 2 + 2; i++) {
        if (2 * i + 1 >= n) break;
        if (a[i] > a[2 * i] || a[i] > a[2 * i + 1]) {
            fout << "No";
            fin.close();
            fout.close();
            return 0;
        }
    }
    fout << "Yes";
    fin.close();
    fout.close();
    return 0;
}