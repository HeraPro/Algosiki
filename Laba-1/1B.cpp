#include <iostream>
#include <fstream>
using namespace std;
int main() {
    long long a,b;
    ifstream fin; fin.open("aplusbb.in");
    ofstream fout; fout.open("aplusbb.out");
    fin >> a >> b;
    fin.close();
    fout << a+b*b;
    fout.close();
    return 0;
}