#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

class Point {
public:
    int x = 0, y = 0;
    double len2p(const Point& B) {
        return sqrt((B.x - x) * (B.x - x) + (B.y - y) * (B.y - y));
    };
};

int main() {
    ifstream in("spantree.in");
    ofstream out("spantree.out");
    int n, x, y;
    double res = 0;
    in >> n;

    Point buff[n];
    int vis[n];
    double edges[n];

    for (int i = 0; i < n; i++) {
        in >> x >> y;
        buff[i] = Point{x, y};
        vis[i] = 0;
        if (i > 0) {
            edges[i] = buff[0].len2p(buff[i]);
        }
    }
    vis[0] = 1;


    for (int j = 1; j < n; j++) {
        double minLen = INT_MAX;
        int help = 0;
        for(int i = 1; i < n; i++)
            if (edges[i] < minLen && !vis[i]) {
                minLen = edges[i];
                help = i;
            }
        vis[help] = 1;
        res += minLen;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                double len = buff[help].len2p(buff[i]);
                if (len < edges[i])
                    edges[i] = len;
            }
        }
    }
    out << fixed << setprecision(20) << res;
    return 0;
}
