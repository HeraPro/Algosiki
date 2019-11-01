#include <fstream>
using namespace std;
 
struct Stack {
    long val;
    Stack *last;
};
 
Stack* add(long val, Stack* last) {
    Stack* B = (Stack*)malloc(sizeof(Stack));
    B->val = val;
    B->last = last;
    return B;
}
 
int main() {
    ifstream fin("stack.in");
    ofstream fout("stack.out");
    long n;
    fin >> n;
    char Com;
    long val;
    Stack* A;
    for (int i = 0; i < n; i++) {
        fin >> Com;
        if (Com == '+') {
            fin >> val;
            A = add(val, A);
        } else {
            fout << A->val << "\n";
            A = A->last;
        }
    }
}