#include <fstream>
using namespace std;
long n,result[300000],a[300000];
void mergeSort(long left, long right){
    if (left < right){
        long mid = (left + right) / 2;
        mergeSort(left, mid);
        mergeSort(mid + 1, right);
        long i = 0, j = 0;
        while (left + i <= mid && mid + 1 + j <= right) {
            if (a[left + i] > a[mid + 1 + j]) {
                result[i + j] = a[mid + 1 + j];
                j++;
            } else {
                result[i + j] = a[left + i];
                i++;
            }
        }
        while (left + i <= mid){
            result[i + j] = a[left + i];
            i++;
        }
 
        while (mid + 1 + j <= right){
            result[i + j] = a[mid + 1 + j];
            j++;
        }
 
        for (i = 0; i < right - left + 1; i++)
            a[left + i] = result[i];
    }
}
 
int main() {
    ifstream fin; fin.open("sort.in");
    fin >> n;
    for (int i = 0; i < n; i++)
        fin >> a[i];
    fin.close();
    mergeSort(0, n - 1);
    ofstream fout; fout.open("sort.out");
    for (int i = 0; i < n; i++)
        fout << a[i] << ' ';
    fout.close();
    return 0;
}