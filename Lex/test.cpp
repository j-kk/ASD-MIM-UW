#include <vector>
#include <list>
#include <set>
#include <tuple>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXLOGN = 24;
int pow2[MAXLOGN];

using trip = tuple<int, int, int>;


inline int log2floor(int q) {
    if (q == 0)
        return 0;
    return (int)(floor(log((double) q ) / log(2.0)));
}



inline void calc_pow2(int x) {
    int b = 1;
    for (int i = 0; i < x; ++i) {
        pow2[i] = b;
        b*=2;
    }
}

int main() {
    ios::sync_with_stdio(0);

    calc_pow2(MAXLOGN);

    int n, k;
    string word;


    cin >> n >> k;
    cin >> word;

    vector<vector<int> > bf;

    for (int i = 0; i < n; i++)
        bf.emplace_back(1, word[i] - 'a');

    int len = 1, count;
    while (pow2[len] <= n) {
        list<trip> t1;
        count = n - pow2[len];

        int mb1 = 0;
        int mb2 = 0;
        for (int i = count; i >= 0; i--) {
            mb1 = max(mb1, bf[i][len - 1]);
            mb2 = max(mb2, bf[i + pow2[len - 1]][len - 1]);

            t1.emplace_back(bf[i][len - 1], bf[i + pow2[len - 1]][len - 1], i);
        }
        if (!t1.empty()) {
            vector<list<trip> > t2(mb2 + 1);

            while (!t1.empty()) {
                t2[get<1>(*t1.begin())].splice(t2[get<1>(*t1.begin())].end(), t1, t1.begin());
            }

            for (auto &t: t2) {
                t1.splice(t1.end(), t);
            }

            if (mb2 < mb1) {
                for (int i = 0; i < mb1 - mb2; ++i) {
                    t2.emplace_back();
                }
            }

            while(!t1.empty()) {
                t2[get<0>(*t1.begin())].splice(t2[get<0>(*t1.begin())].end(), t1, t1.begin());
            }

            for (auto &t: t2) {
                t1.splice(t1.end(), t);
            }

            int r = 0;
            auto it = t1.begin();

            bf[get<2>(*it)].push_back(r);
            ++it;
            while (it != t1.end()) {
                if(get<0>(*it) != get<0>(*(--it)) || get<1>(*(++it)) != get<1>(*(--it)))
                    ++r;
                bf[get<2>(*(++it))].push_back(r);
                ++it;
            }
        }

        len++;

    }



    while (k > 0) {
        --k;
        pair<int, int> a, b;
        cin >> a.first >> a.second >> b.first >> b.second;

        int a_len = a.second - a.first + 1;
        int b_len = b.second - b.first + 1;

        --a.first;
        --b.first;
        --a.second;
        --b.second;

        int len = min(a_len, b_len);
        int p = log2floor(len - 1);

        if (bf[a.first][p] < bf[b.first][p]) {
            std::cout << "<\n";
        } else if (bf[a.first][p] > bf[b.first][p]) {
            std::cout << ">\n";
        } else {
            if (bf[a.first + len - pow2[p]][p] < bf[b.first + len - pow2[p]][p]) {
                std::cout << "<\n";
            } else if (bf[a.first + len - pow2[p]][p] > bf[b.first + len - pow2[p]][p]) {
                std::cout << ">\n";
            } else {
                if (a.second - a.first == b.second - b.first) {
                    std::cout << "=\n";
                } else if (a.second - a.first < b.second - b.first) {
                    std::cout << "<\n";
                } else {
                    std::cout << ">\n";
                }
            }
        }

    }
    return 0;
}
