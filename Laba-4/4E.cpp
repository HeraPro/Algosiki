#include <fstream>
using namespace std;

long n = 0;
pair <long, long> a[1000000];


void siftDown(int i) {
    int help = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && a[left].first < a[i].first) help = left;
    if (right < n && a[right].first < a[help].first) help = right;
    if (help != i) {
        swap(a[i], a[help]);
        siftDown(help);
    }
}

void siftUp(int i) {
    if (i != 0){
        if (a[i].first < a[(i - 1) / 2].first){
            swap(a[i], a[(i - 1) / 2]);
            siftUp((i - 1) / 2);
        }
    }
}

int Find(int y){
    for (int i = 0; i < n; i++)
        if (a[i].second == y)
            return i;
}

int main() {
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");

    string Com;
    for (int i = 0; i < 1000000; i++) {
        getline(fin, Com);
        if (Com.length() == 0)
            break;
        if (Com.find("push") == 0) {

            long val = stoi(Com.substr(5, Com.length()));
            n++;
            a[n - 1].first = val;
            a[n - 1].second = n;
            siftUp(n - 1);

        } else if (Com.find("extract-min") == 0) {

            if (n == 0) {
                fout << "*\n";
            } else {
                fout << a[0].first << "\n";
                swap(a[0], a[n - 1]);
                n--;
                siftDown(0);
            }

        } else if (Com.find("decrease-key") == 0) {

            Com = Com.substr(13, Com.length());
            long x = stoi(Com.substr(0, Com.find(" "))),
                 y = stoi(Com.substr(Com.find(" "), Com.length()));
            int i = Find(x);
            a[i].first = y;
            if (i != 0 && a[i].first < a[(i - 1) / 2].first)
                siftUp(i);
            else
                siftDown(i);

        } else {
            break;
        }
    }
    return 0;
}