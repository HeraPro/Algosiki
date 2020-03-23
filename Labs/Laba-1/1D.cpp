#include <iostream>
#include <fstream>
using namespace std;
int main() {
    long n,j;
    ifstream fin; fin.open("smallsort.in");
    fin >> n;
    long long M[n]; long long b,help;
    for (int i=0;i<n;i++) {
        fin >> b;
        j=i-1; help = M[j];
        while (j>=0&&M[j]>b) {
            M[j+1]=M[j]; j--;
        }
        M[j+1]=b;
    }
    fin.close();
    ofstream fout; fout.open("smallsort.out");
    for (int i=0;i<n-1;i++) {
        fout << M[i] << " ";
    }
    fout << M[n-1];
    fout.close();
    return 0;
}