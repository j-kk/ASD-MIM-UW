#include <vector>
#include <map>
#include <set>
#include <tuple>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

const int MAXLOGN = 24;
int pow2[MAXLOGN];

using trip = tuple<int, int, int>;

bool operator!=(const trip &lhs, const trip &rhs) {
    pair<int, int> l, r;
    l = {get<1>(lhs), get<2>(lhs)};
    r = {get<1>(rhs), get<2>(rhs)};
    return l != r;
}
//struct trip_compare {
//    bool operator< const (const trip &lhs, const trip &rhs) {
//
//    }
//};
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

    int maxp2 = log2floor(n);

    vector<vector<int> > bf(maxp2 + 1);

    vector<trip> buffer;

    for (int i = 0; i < n; ++i)
        word[i] -= 'a';

    for (int i = 0; pow2[i] <= n; i++)
        bf[i] = vector<int>(n - pow2[i] + 1);

    for (int i = 0; i < n; i++)
        bf[0][i] = word[i];

    int prev = 1, len = 1, max_id = 25, count;
    while (pow2[len] <= n) {
        count = n - pow2[len] + 1;

        for (int i = 0; i < count; ++i)
            buffer.emplace_back(i, bf[log2floor(prev)][i], bf[log2floor(prev)][i + prev]);

//        vector<vector<int> > k1(max_id + 1), k2(max_id + 1);
//        vector<trip> tmp;
        set<trip> total;

        for (auto &it: buffer)
            total.insert({get<1>(it), get<2>(it), get<0>(it)});
//            k2[get<2>(it)].push_back(get<0>(it));
//        for (auto &it: k2)
//            for (auto &iti: it)
//                k1[get<1>(buffer[iti])].push_back(iti);
////                tmp.push_back(buffer[iti]);
//        for (auto &it: k1)
//            for (auto &iti: it)
//                tmp.push_back(buffer[iti]);

        int id = 0;
        bf[len][get<2>(*total.begin())] = id;
        auto it = total.begin();
        auto previt = total.begin();
        it++;
        while (it != total.end()) {
            if (it != previt)
                ++id;
            bf[len][get<2>(*it)] = id;
            it++;
            previt++;
        }
        max_id = id;
        buffer.clear();
        prev = pow2[len];
        ++len;
    }

    while (k > 0) {
        --k;
        pair<int, int> a, b;
        cin >> a.first >> a.second >> b.first >> b.second;

        int a_len = a.second - a.first + 1;
        int b_len = b.second - b.first + 1;

        --a.first;
        --b.first;

        int len = min(a_len, b_len);

        int p2_len = log2floor(len);
        int leng = 1 << p2_len;

        int mask = 1 << p2_len;

        char out = 0;
        while (p2_len >= 0) {
            if ((mask & len) != 0) {
                int tmp = bf[p2_len][a.first] - bf[p2_len][b.first];
                if (tmp < 0)
                    out = 1;
                else if (tmp > 0)
                    out = -1;
                a.first += leng;
                b.first += leng;
                a_len -= leng;
                b_len -= leng;
                if (out != 0)
                    break;
            }
            mask >>= 1;
            leng >>= 1;
            --p2_len;
        }
        if (out == 0) {
            if (a_len == b_len)
                cout << "=" << endl;
            else {
                if (a_len > b_len)
                    cout << ">" << endl;
                else
                    cout << "<" << endl;
            }
            continue;
        } else {
            if (out > 0)
                cout << "<" << endl;
            else
                cout << ">" << endl;
        }
    }
    return 0;
}
