//
// Created by nikita on 25/12/2018.
//

#ifndef IMPLEMENTATION_BESTPERFECTMATCHING_H
#define IMPLEMENTATION_BESTPERFECTMATCHING_H

#include "blossom5-v2.05.src/PerfectMatching.h"

#define INF (long long)1e15

using std::vector;

vector<long long> get_min_perfect_matching(vector<vector<long long>>& g) {

    long long n = (long long)g.size();

    PerfectMatching matching(n, (n * (n - 1)) / 2);

    for (long long i = 0; i < n; i++) {
        for (long long j = i + 1; j < n; j++) {
            if (g[i][j] != INF) {
                matching.AddEdge(i, j, (long long)g[i][j]);
            }
        }
    }

    matching.Solve();

    vector <long long> ans(n);
    for(long long i = 0;i < n;++i) {
        ans[i] = matching.GetMatch(i);
    }

    return ans;
}

#endif //IMPLEMENTATION_BESTPERFECTMATCHING_H
