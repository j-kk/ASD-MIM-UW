#include <cstdio>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;


const long long MOD = 1000000000;
int n;
int tab[1005];
int wyn[1005];
int out;

//
//long long f (int ln, int type, int* first, int* last) {
//    if (first == last)
//        return 1;
//
//    long long w = 0;
//    if (type == -1) //moge zdjac tylko mniejszy
//    {
//        if (ln > *first)
//            w += f (*first, 1, first + 1, last);
//
//        if (ln > *last)
//            w += f (*last, -1, first, last - 1);
//    }
//
//    if (type == 1) //moge zdjac tylko wiekszy
//    {
//        if (ln < *first)
//            w += f (*first, 1, first + 1, last);
//
//        if (ln < *last)
//            w += f (*last, -1, first, last - 1);
//    }
//
//    return w % MOD;
//}

void f () {
    list<int> w;
    w.push_back(tab[0]);
    for (int i = 1; i < n; ++i) {
        if (tab[i - 1] > tab[i])
            w.push_front(tab[i]);
        else
            w.push_back(tab[i]);
    }
    int ok = 1;
    for (int i = 0; i < n; ++i) {
        if (w.front() != wyn[i])
            return;
//        printf ("%d ", w.front());
        w.pop_front();
    }
    out += ok;
    out %= MOD;
    for (int i = 0; i < n; i++) {
        printf ("%d ", tab[i]);
    }
    printf("\n");
}

int main() {
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i) {
        tab[i] = i + 1;
        scanf ("%d", &wyn[i]);
    }
    do {
        f();
    } while (next_permutation(tab, tab + n));

    printf ("%d\n", out);

    return 0;
}