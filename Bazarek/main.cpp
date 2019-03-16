#include <cstdio>
#include <algorithm>

using namespace std;
//TODO zmien na  1000000
const int MAXN = 1000009;
const int MAXM = MAXN;

int n, m;
long long tp[MAXN], tnp[MAXN];
int np, nnp;

long long wynik[MAXN];

int main() {
    scanf ("%d", &n);

    for (int i = 0; i < n; ++i) {
        long long temp;
        scanf ("%lld", &temp);
        if (temp % 2 == 0)
            tp[np++] = temp;
        else
            tnp[nnp++] = temp;
    }
    long long sum = 0;
    int k = 0;

    for (int wp = np - 1, wnp = nnp - 1; wnp >= 0 || wp >= 0; ) {
        if (wnp >= 0) {
            if ((sum + tnp[wnp]) % 2 == 1)
                wynik[k + 1] = max(sum + tnp[wnp], wynik[k + 1]);
        }

        if (wp >= 0) {
            if ((sum + tp[wp]) % 2 == 1)
                wynik[k + 1] = max(sum + tp[wp], wynik[k + 1]);
        }

        if (wp >= 0 && wnp >= 0) {
            if (tp[wp] > tnp[wnp])
                sum += tp[wp--];
            else sum += tnp[wnp--];
        }
        else {
            if (wp >= 0)
                sum += tp[wp--];

            if (wnp >= 0)
                sum += tnp[wnp--];

        }
        k++;

        if (sum % 2 == 1)
            wynik[k] = max(sum, wynik[k]);

        if (wp < np - 1 && wnp >= 0 && k > 0 && sum % 2 == 0) {
            wynik[k] = max(wynik[k], sum - tp[wp + 1] + tnp[wnp]);
        }

        if (wnp < nnp - 1 && wp >= 0 && k > 0 && sum % 2 == 0) {
            wynik[k] = max(wynik[k], sum - tnp[wnp + 1] + tp[wp]);
        }


    }
    scanf ("%d", &m);


    for (int i = 0; i < m; ++i) {
        int k;
        scanf ("%d", &k);
        if (wynik[k] == 0)
            wynik[k] = -1;
        printf ("%lld\n", wynik[k]);
    }





    return 0;
}

