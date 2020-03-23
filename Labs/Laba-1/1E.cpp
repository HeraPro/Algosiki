#include <iostream>
#include <fstream>
using namespace std;
int main() {
    int n, j;
    ifstream fin; fin.open("sortland.in");
    fin >> n;
    double *M = new double[n];
    double *N = new double[n];
    double b;
    for (int i = 0; i < n; i++) {
        fin >> b; N[i] = b;
        j = i - 1;
        while (j >= 0 && M[j] > b) {
            M[j + 1] = M[j]; j--;
        }
        M[j + 1] = b;
    }
    fin.close();
    ofstream fout; fout.open("sortland.out");
    b = M[0];double Last = M[n - 1]; double Result[3]; double Seredina = M[(n+1)/2-1];
    for (int i = 0; i < n; i++) {
        if (N[i] == b) Result[0] = i+1;
        if (N[i] == Seredina) Result[1] = i+1;
        if (N[i] == Last) Result[2] = i+1;
    }
    for (int i = 0; i < 3; i++)
        fout << Result[i] << " ";
    fout.close();
    return 0;
}