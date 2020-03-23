#include <fstream>
#include <vector>
#include <queue>
using namespace std;

struct Point {
    int x;
    int y;
};

int main() {
    ifstream in("input.txt");
    ofstream out("output.txt");
    int n = 0, m = 0;
    Point start {-1, -1}, stop {-1, -1};
    char ch;
    in >> n >> m;
    int matrix[m][n];

    /*                                       Чтение                                   */
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            in >> ch;
            if (ch == '#')
                matrix[j][i] = -1;
            else if (ch == '.')
                matrix[j][i] = 0;
            else if (ch == 'S') {
                matrix[j][i] = 1;
                start.x = j;
                start.y = i;
            }
            else if (ch == 'T') {
                matrix[j][i] = 0;
                stop.x = j;
                stop.y = i;
            }
        }
    }

    /*                                                                                 */
    queue<Point> Qu;
    Qu.push(start);
    while (!Qu.empty()) {
        Point b = Qu.front();

        if (b.x != stop.x || b.y != stop.y) {

            if (b.x > 0) {
                Point Left = {b.x - 1, b.y};
                if (matrix[Left.x][Left.y] != -1 && (matrix[Left.x][Left.y] == 0 || matrix[Left.x][Left.y] > matrix[b.x][b.y] + 1)) {
                    matrix[Left.x][Left.y] = matrix[b.x][b.y] + 1;
                    Qu.push(Left);
                }
            }

            if (b.x < m - 1) {
                Point Right = {b.x + 1, b.y};
                if (matrix[Right.x][Right.y] != -1 && (matrix[Right.x][Right.y] == 0 || matrix[Right.x][Right.y] > matrix[b.x][b.y] + 1)) {
                    matrix[Right.x][Right.y] = matrix[b.x][b.y] + 1;
                    Qu.push(Right);
                }
            }

            if (b.y > 0) {
                Point Up = {b.x, b.y - 1};
                if (matrix[Up.x][Up.y] != -1 && (matrix[Up.x][Up.y] == 0 || matrix[Up.x][Up.y] > matrix[b.x][b.y] + 1)) {
                    matrix[Up.x][Up.y] = matrix[b.x][b.y] + 1;
                    Qu.push(Up);
                }
            }

            if (b.y < n - 1) {
                Point Down = {b.x, b.y + 1};
                if (matrix[Down.x][Down.y] != -1 && (matrix[Down.x][Down.y] == 0 || matrix[Down.x][Down.y] > matrix[b.x][b.y] + 1)) {
                    matrix[Down.x][Down.y] = matrix[b.x][b.y] + 1;
                    Qu.push(Down);
                }
            }
        }

        Qu.pop();
    }



    /*                                       Вывод                                                     */
    

    int count = matrix[stop.x][stop.y];
    char road[count - 1];
    for (int i = count - 1; i > 0; i--) {
        if (stop.x > 0 && matrix[stop.x - 1][stop.y] == i) {
            road[i - 1] = 'R';
            stop = {stop.x - 1, stop.y};
        }
	/* привет кравцову */
        else if (stop.x < m - 1 && matrix[stop.x + 1][stop.y] == i) {
            road[i - 1] = 'L';
            stop = {stop.x + 1, stop.y};
        } else if (stop.y > 0 && matrix[stop.x][stop.y - 1] == i) {
            road[i - 1] = 'D';
            stop = {stop.x, stop.y - 1};
        } else if (stop.y < n - 1 && matrix[stop.x][stop.y + 1] == i) {
            road[i - 1] = 'U';
            stop = {stop.x, stop.y + 1};
        }
    }

    out << --count << '\n';
    for (int i = 0; i < count; i++)
        out << road[i];
    return 0;
}