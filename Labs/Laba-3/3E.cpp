#include <fstream>
using namespace std;
 
string a[1000], result[1000];
long n, len, k;
 
void Sort(int pos) {
    char help = 'a';
    int j = 0;
    for (int i = 0; i < 26; i++) {
        for (int g = 0; g < n; g++) {
            if (a[g][pos]==help) {
                result[j] = a[g];
                j++;
            }
        }
        help++;
    }
    for (int i = 0; i < n; i++)
        a[i]=result[i];
}
 
int main() {
    ifstream fin("radixsort.in");
    ofstream fout("radixsort.out");
    fin >> n >> len >> k;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    for (int i = len-1; i >= len-k; i--)
        Sort(i);
 
    for (int i = 0; i < n; i++)
        fout << a[i] << '\n';
    return 0;
}