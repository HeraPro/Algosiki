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

/*
int[] prefixFunction(string s):
  p[0] = 0
  for i = 1 to s.length - 1
      k = p[i - 1]
      while k > 0 and s[i] != s[k]
          k = p[k - 1]
      if s[i] == s[k]
          k++
      p[i] = k
  return p
  */

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
    ifstream in("prefix.in");
    ofstream out("prefix.out");
    string p, t;
    int pos;
    vector<int> ans;
    in >> p;

    vector<int> prefix = prefixFunction(p);
    for (auto i : prefix)
        out << i << ' ';

    return 0;
}