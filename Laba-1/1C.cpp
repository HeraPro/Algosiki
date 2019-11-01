#include <iostream>
#include <fstream>
using namespace std;
 
int main() {
    ifstream fin; fin.open("turtle.in");
    int w, h;
    fin >> h >> w;
    int XY[w][h];
    for (int g = 0; g < h; g++) for (int i = 0; i < w; i++) {
        fin >> XY[i][g];
    }
    int left, down;
    for (int g = h-1; g>=0; g--) for (int i = 0; i < w; i++) {
        if (i == 0) left = 0; else left = XY[i-1][g];
        if (g == h-1) down = 0; else down = XY[i][g+1];
        if (left > down) XY[i][g] += left; else XY[i][g] += down;
    }
    fin.close();
    ofstream fout; fout.open("turtle.out");
    fout << XY[w-1][0];
    fout.close();
    return 0;
}