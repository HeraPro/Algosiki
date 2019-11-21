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

int Find(int X){
    for (int i = 0; i < n; i++)
        if (a[i].second == X)
            return i;
}

int main() {
    ifstream fin("priorityqueue.in");
    ofstream fout("priorityqueue.out");

    string Com;
    int i = 0;
    while (fin >> Com) {
        i++;
        if (Com.length() == 0)
            break;
        if (Com == "push") {
            long val;
            fin >> val;
            n++;
            a[n - 1].first = val;
            a[n - 1].second = i;
            siftUp(n - 1);

        } else if (Com == "extract-min") {

            if (n == 0) {
                fout << "*\n";
            } else {
                fout << a[0].first << "\n";
                swap(a[0], a[n - 1]);
                n--;
                siftDown(0);
                /*for (int j = 0; j < n; j++) {
                    if (a[j].second > a[n - 1].second)
                        a[j].second--;
                }*/
            }

        } else if (Com == "decrease-key") {
            long x, y;
            fin >> x >> y;
            int j = Find(x);
            a[j].first = y;
            if (j != 0 && a[j].first < a[(j - 1) / 2].first)
                siftUp(j);
            else
                siftDown(j);

        } else {
            break;
        }
    }
    return 0;
}