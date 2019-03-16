#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 1000007;

int n;
int k = MAXN;

int main() {
    char c = '0';
    char ostatnia = '0';
    int gdzieOstatnia = 0;

    while (true) {
        scanf("%c", &c);
        if (c == '\n')
            break;
        n++;

        if (c == ostatnia)
            gdzieOstatnia = n;

        if (c != '*' && c != ostatnia) {
            if (ostatnia != '0')
                k = min (k, n - gdzieOstatnia);

            ostatnia = c;
            gdzieOstatnia = n;
        }
    }

    printf("%d\n", max(n - k + 1, 1));

    return 0;
}