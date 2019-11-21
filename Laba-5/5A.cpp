#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

vector<long> HashTable[1000001];

unsigned Find(vector<long> a, long el) {
    for (unsigned i = 0; i < a.size(); i++)
        if (a[i] == el)
            return i;
    return 0;
}



int main() {
    ifstream fin("set.in");
    ofstream fout("set.out");
    string Com;
    while (fin >> Com) {
        if (Com == "insert") {
            long el;
            fin >> el;
            long i = abs(el % 1000001);
            unsigned b = Find(HashTable[i], el);
            if (HashTable[i].empty() || HashTable[i][b] != el)
                HashTable[i].push_back(el);
        } else if (Com == "delete") {
            long el;
            fin >> el;
            long i = abs(el % 1000001);
            unsigned b = Find(HashTable[i], el);
            if (!HashTable[i].empty() && HashTable[i][b] == el) {
                swap(HashTable[i][b], HashTable[i][HashTable[i].size() - 1]);
                HashTable[i].pop_back();
            }

        } else if (Com == "exists") {
            long el;
            fin >> el;
            long i = abs(el % 1000001);
            unsigned b = Find(HashTable[i], el);
            if (!HashTable[i].empty() && HashTable[i][b] == el) {
                fout << "true\n";
            } else {
                fout << "false\n";
            }
        }
    }

    return 0;
}