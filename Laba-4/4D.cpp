#include <fstream>
using namespace std;

struct Stack {
    long val;
    Stack *last = NULL;
};

Stack* add(long val, Stack* last) {
    Stack* B = (Stack*)malloc(sizeof(Stack));
    B->val = val;
    B->last = last;
    return B;
}

int main() {
    ifstream fin("postfix.in");
    ofstream fout("postfix.out");
    char Com;
    Stack* A = NULL;
    for (int i = 0; i < 100; i++) {
        fin >> Com;
        if (Com == '+') {

            if (A==NULL||A->last==NULL)
                break;
            A->last->val = A->val+A->last->val;
            A = A->last;

        } else if (Com == '-') {

            if (A==NULL||A->last==NULL)
                break;
            A->last->val = A->last->val-A->val;
            A = A->last;

        } else if (Com == '*') {

            if (A==NULL||A->last==NULL)
                break;
            A->last->val = A->val*A->last->val;
            A = A->last;

        } else if ((int)Com>=48&&(int)Com<=58) {
            A = add((int)Com - 48, A);
        }
    }
    fout << A->val;
    return 0;
}