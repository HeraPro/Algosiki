#include <fstream>
#include <vector>

using namespace std;

int native(string p, string t, int pos) {

    for (int j = 1; j < p.length(); j++) {
        if (t[pos + j] != p[j]) {
            return -1;
        }
    }

    return pos;
}

int main() {
    ifstream in("search1.in");
    ofstream out("search1.out");
    string p, t;
    int pos;
    vector<int> ans;
    in >> p >> t;

    if ((int)t.length() - (int)p.length() + 1 < 0) {
        out << 0 << '\n';
        return 0;
    }
    int a = t.length() - p.length() + 1;
    for (int i = 0; i < t.length() - p.length() + 1; i++) {
        if (t[i] == p[0]) {
            pos = native(p, t, i);
            if (pos > -1)
                ans.push_back(i + 1);
        }
    }

    out << ans.size() << '\n';

    for (int an : ans)
        out << an << ' ';
    return 0;
}