#include <fstream>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

int GetElement(const string& key, int hashSize){
    int hashCode = 0;
    int help = 1;
    for (char i : key){
        hashCode += help * (int)i;
        hashCode %= hashSize;
        help = (help * 37) % hashSize;
    }
    return hashCode;
}

struct Set{
    string key;
    vector <vector <string> > element;
    Set(){
        element.resize(311);
    }
};

struct multiMap{
    vector < vector<Set> > set;
    multiMap(){
        set.resize(100003);
    }
};

multiMap mMap;

void put(const string& key, const string& el){
    int keyHash = GetElement(key, 100003);
    for (auto & i : mMap.set[keyHash]){
        if (i.key == key){
            int elHash = GetElement(el, 311);
            for (const auto & j : i.element[elHash]){
                if (j == el)
                    return;
            }
            i.element[elHash].push_back(el);
            return;
        }
    }
    Set* newSet = new Set;
    newSet->key = key;
    newSet->element[GetElement(el, 311)].push_back(el);
    mMap.set[keyHash].push_back(*newSet);
    delete newSet;
}

void del(const string& key, const string& el){
    int keyHash = GetElement(key, 100003);
    for (auto & i : mMap.set[keyHash]){
        if (i.key == key){
            int elHash = GetElement(el, 311);
            for (int j = 0; j < i.element[elHash].size(); j++){
                if (i.element[elHash][j] == el) {
                    i.element[elHash].erase(i.element[elHash].begin() + j);
                    return;
                }
            }
        }
    }
}

void deleteAll(const string& key){
    int keyHash = GetElement(key, 100003);
    for (auto & i : mMap.set[keyHash]){
        if (i.key == key){
            for(auto & j : i.element){
                while(!j.empty())
                    j.pop_back();
            }
            return;
        }
    }
}

vector<string> Get (const string& key){
    vector<string> Result;
    int keyHash = GetElement(key, 100003);
    for (auto & i : mMap.set[keyHash]){
        if (i.key == key){
            for(auto & j : i.element){
                for(const auto & k : j) {
                    Result.push_back(k);
                }
            }
            return Result;
        }
    }
    return Result;
}

int main(){
    ifstream in;
    ofstream out;
    in.open("multimap.in");
    out.open("multimap.out");
    while(!in.eof()) {
        string com;
        in >> com;
        if (com == "put") {
            string first, second;
            in >> first >> second;
            put(first, second);
        }
        if (com == "delete") {
            string first, second;
            in >> first >> second;
            //del(first, second);
        }
        if (com == "deleteall") {
            string first;
            in >> first;
            deleteAll(first);
        }
        if (com == "get") {
            string first;
            in >> first;
            vector<string> getA = Get(first);
            out << getA.size() << ' ';
            for (const string& i : getA)
                out << i << ' ';
            out << "\n";
        }

    }
    in.close();
    out.close();
    return 0;
}
