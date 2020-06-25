#include <fstream>
#include <vector>

using namespace std;


vector<int> prefixFunction(string s) {
    vector<int> p(s.length());

    for (int i = 1; i < s.length(); i++) {
        int k = p[i - 1];

        while (k > 0 && s[i] != s[k])
            k = p[k - 1];
        if (s[i] == s[k])
            k++;
        p[i] = k;
    }

    return p;
}

int main() {
    ifstream in("search2.in");
    ofstream out("search2.out");
    string p, t;
    vector<int> ans;
    in >> p >> t;

    vector<int> prefix = prefixFunction(p + "#" + t);

    for (int i = 0; i < t.length(); i++) {
        if (prefix[p.length() + 1 + i] == p.length()) {
            ans.push_back(i - p.length() + 2);
        }
    }

    out << ans.size() << '\n';

    for (int an : ans)
        out << an << ' ';

    return 0;
}