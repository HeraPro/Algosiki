#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

vector<pair<string, string>> HashTable[100001];

unsigned Find(vector<pair<string, string>> a, const string& el) {
    for (unsigned i = 0; i < a.size(); i++)
        if (a[i].first == el)
            return i;
    return 0;
}

int GetElement(string key) {
    int hashValue = 0;
    for(char i : key) {
        hashValue = 13 * hashValue + (int)i;
    }
    return abs(hashValue % 100001);
}

int main() {
    ifstream fin("map.in");
    ofstream fout("map.out");
    string Com;

    while (fin >> Com) {
        if (Com == "put") {
            string first, second;
            fin >> first >> second;
            long i = GetElement(first);
            unsigned b = Find(HashTable[i], first);
            if (!HashTable[i].empty() && HashTable[i][b].first == first)
                HashTable[i][b].second = second;
            if (HashTable[i].empty() || HashTable[i][b].first != first)
                HashTable[i].emplace_back(first, second);
        } else if (Com == "delete") {
            string first;
            fin >> first;
            long i = GetElement(first);
            unsigned b = Find(HashTable[i], first);
            if (!HashTable[i].empty() && HashTable[i][b].first == first) {
                swap(HashTable[i][b], HashTable[i][HashTable[i].size() - 1]);
                HashTable[i].pop_back();
            }
        } else if (Com == "get") {
            string first;
            fin >> first;
            long i = GetElement(first);
            unsigned b = Find(HashTable[i], first);
            if (!HashTable[i].empty() && HashTable[i][b].first == first) {
                fout << HashTable[i][b].second << '\n';
            } else {
                fout << "none\n";
            }
        }
    }
    return 0;
}