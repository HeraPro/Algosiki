#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct ListElem {
    string key;
    string value;
    struct ListElem* next;
    struct ListElem* prev;
    struct ListElem* nextQueue;
};

class List {
    ListElem* list;
public:
    List() {
        list = new ListElem();
        list->value = list->key = "";
        list->nextQueue = nullptr;
    }
    void insert(const string& key, const string& value, ListElem *head) {
        ListElem *newEl = exists(key);
        if (exists(key) == nullptr) {
            ListElem *Tail = head->prev;
        } else
            newEl->value = value;
    }
    void del(const string& key) {
        ListElem *current_element = list;
        while (current_element->nextQueue != nullptr) {
            if (current_element->nextQueue->key == key) {
                ListElem *to_delete = current_element->nextQueue;
                ListElem *prev_element = to_delete->prev, *NextNode = to_delete->next;
                delete to_delete;
                return;
            } else
                current_element = current_element->nextQueue;
        }
    }
    ListElem* exists(const string& key) {
        ListElem *currentEl = list;
        while (currentEl->nextQueue != nullptr) {
            if (currentEl->nextQueue->key == key)
                return currentEl->nextQueue;
            currentEl = currentEl->nextQueue;
        }
        return nullptr;
    }
};

class LinkedMap
{
    vector <List> lm;
    ListElem *head;
    static int GetElement(const string& key) {
        int hash_value = 0;
        for(char i : key) {
            hash_value = 41 * hash_value + i;
        }
        return abs(hash_value % 1000001);
    }
public:
    LinkedMap() {
        lm.resize(1000001);
        head = new ListElem;
        head->prev = head->next = head;
    }
    void insert(const string& key, const string& value) {
        lm[GetElement(key)].insert(key, value, head);
    }
    void del(const string& key) {
        lm[GetElement(key)].del(key);
    }
    string get(const string& key) {
        ListElem *result = lm[GetElement(key)].exists(key);
        if (result == nullptr)
            return "none";
        else
            return result->value;
    }
    string next(const string& K)
    {
        ListElem *result = lm[GetElement(K)].exists(K);
        if (result == nullptr || result->next == head)
            return "none";
        else
            return result->next->value;
    }
    string prev(const string& key)
    {
        ListElem *result = lm[GetElement(key)].exists(key);
        if (result == nullptr || result->prev == head) {
            return "none";
        }
        else {
            return result->prev->value;
        }
    }
};

int main() {
    ifstream fin("linkedmap.in");
    ofstream fout("linkedmap.out");
    string key;
    string value;
    string command;
    LinkedMap new_map;
    while(fin >> command) {
        if (command == "put") {
            fin >> key >> value;
            new_map.insert(key, value);
        } else if (command == "delete") {
            fin >> key;
        } else if (command == "get") {
            fin >> key;
            fout << new_map.get(key) << '\n';
        } else if (command == "next") {
            fin >> key;
            fout << new_map.next(key) << '\n';
        } else if (command == "prev") {
            fin >> key;
            fout << new_map.prev(key) << '\n';
        }
    }
}
