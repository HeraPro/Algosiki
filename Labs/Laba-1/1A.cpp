#include <iostream>
#include <fstream>
using namespace std;
int main() {
    ifstream fin; fin.open("aplusb.in");
    ofstream fot; fot.open("aplusb.out");
    long a,b;
    fin >> a >> b;
    fin.close();
    fot << a+b;
    fot.close();
    return 0;
}