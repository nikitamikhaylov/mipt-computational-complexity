//
// Created by nikita on 25/12/2018.
//

#ifndef IMPLEMENTATION_MST_H
#define IMPLEMENTATION_MST_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 1e5;

//---------DSU------------
vector<long long> p(MAXN);

int dsu_get(long long v) {
    return (v == p[v]) ? v : (p[v] = dsu_get(p[v]));
}

void dsu_unite (long long a, long long b) {
    a = dsu_get (a);
    b = dsu_get (b);
    if (rand() & 1)
        swap (a, b);
    if (a != b)
        p[a] = b;
}

//-------------------------

vector< pair < long long, pair< long long, long long > > > mst(long long N, vector< pair < long long, pair< long long, long long > > > &g) {

    long long cost = 0;

    long long M = g.size();

    vector< pair < long long, pair< long long, long long > > > res;

    sort(g.begin(), g.end());
    p.resize(N);

    for (long long i = 0; i < N; i++){
        p[i] = i;
    }

    for (long long i = 0; i < M; i++) {
        long long a = g[i].second.first;
        long long b = g[i].second.second;
        long long l = g[i].first;
        if (dsu_get(a) != dsu_get(b)) {
            cost += l;
            res.push_back(g[i]);
            dsu_unite (a, b);
        }
    }

    return res;
}


#endif //IMPLEMENTATION_MST_H
