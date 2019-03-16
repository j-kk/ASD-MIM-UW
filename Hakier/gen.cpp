//
// Created by Jakub Kowalski on 2019-02-10.
//

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

const int MINA = 1;
const int MAXA = 30;

int N, K;
string op[] = {"in", "over", "some", "none"};

int random(int a, int b) {
    return rand() % (b - a + 1) + a;
}

int main(int argc, char* argv[]) {
    srand(atoi(argv[1]));

    N = random(1, 10);
    K = random (1, 10);
    cout<<N<<endl;
    for (int i = 0; i < N; i++) {
        int a = random (MINA, MAXA);
        int b = random (a, MAXA);
        cout<<a<<" "<<b<<endl;
    }

    cout<<K<<endl;

    for (int i = 0; i < K; i++) {
        int id = random(0, 3);
        cout<<op[id]<<endl;
        int a = random (MINA, MAXA);
        int b = random (a, MAXA);
        cout<<a<<" "<<b<<endl;
    }


    return 0;
}
