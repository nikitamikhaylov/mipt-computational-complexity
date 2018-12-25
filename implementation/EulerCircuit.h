//
// Created by nikita on 25/12/2018.
//

#ifndef IMPLEMENTATION_EULERCIRCUIT_H
#define IMPLEMENTATION_EULERCIRCUIT_H

#include <stack>

using std::vector;

void dfs(long long v, vector<vector<long long> >& g, vector <long long>& cycle, vector <long long>& ref) {
    long long i;
    for(; ref[v] < g.size(); ++ref[v]) {
        i = ref[v];
        assert(g[v][i] >= 0);
        if(g[v][i] > 0) {
            --g[v][i];
            --g[i][v];
            dfs(i, g, cycle, ref);
            cycle.push_back(v);
        }
    }

}

vector <long long> euler_cycle(vector<vector<long long> > g) {
    vector <long long> cycle;
    vector <long long> ref(g.size(), 0);
    dfs(0, g, cycle, ref);

    return cycle;
}

vector<long long> HamiltonCircuitFromEuler(vector<long long> tour) {

    vector<long long> HamiltonTour;

    for (auto v : tour) {

        bool flag = true;

        for (auto t : HamiltonTour) {
            if (t == v) {
                flag = false;
            }
        }

        if (flag) {
            HamiltonTour.push_back(v);
        }
    }

    HamiltonTour.push_back(HamiltonTour[0]);

    return HamiltonTour;
}

#endif //IMPLEMENTATION_EULERCIRCUIT_H
