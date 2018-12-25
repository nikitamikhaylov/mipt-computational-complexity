//
// Created by nikita on 25/12/2018.
//

#ifndef IMPLEMENTATION_TEST_GENERATION_H
#define IMPLEMENTATION_TEST_GENERATION_H

#define TESTS       10
#define VERTEX_MAX  1000
#define VERTEX_MIN  10

#include <stdlib.h>
#include <time.h>

void gen_test(long long v, long long num) {
    srand(time(nullptr));

    set<pair<long long, long long>> s;

    string filename = "input" + to_string(num) + ".txt";

    freopen(filename.c_str(), "w", stdout);

    printf("%d %d\n", v, (v * (v - 1)) / 2);

    vector<long long> circ;

    for (long long i = 1; i <= v; i++) {
        circ.push_back(i);
    }

    random_shuffle(circ.begin(), circ.end());

    for (long long i = 0; i < circ.size() - 1; i++) {
        s.insert(make_pair(circ[i], circ[i + 1]));
        s.insert(make_pair(circ[i + 1], circ[i]));
        printf("1 %d %d\n", circ[i], circ[i + 1]);
    }

    s.insert(make_pair(circ[v - 1], circ[0]));
    s.insert(make_pair(circ[0], circ[v - 1]));
    printf("1 %d %d\n", circ[v - 1], circ[0]);

    for (long long i = 1; i <= v; i++) {
        for (long long j = 1; j <= v; j++) {

            if (i == j) {
                continue;
            }

            if (s.find(make_pair(i, j)) != s.end()) {
                continue;
            } else {
                int weight = rand() % 2 + 1;
                s.insert(make_pair(i, j));
                s.insert(make_pair(j, i));
                printf("%d %d %d\n", weight, i, j);
            }
        }
    }

    fclose(stdout);
}

#endif //IMPLEMENTATION_TEST_GENERATION_H
