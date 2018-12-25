#include <iostream>
#include <algorithm>
#include <vector>
#include "MST.h"
#include "BestPerfectMatching.h"
#include "blossom5-v2.05.src/PMmain.cpp"
#include "blossom5-v2.05.src/PMinit.cpp"
#include "blossom5-v2.05.src/PMduals.cpp"
#include "blossom5-v2.05.src/PMexpand.cpp"
#include "blossom5-v2.05.src/PMshrink.cpp"
#include "blossom5-v2.05.src/PMrepair.cpp"
#include "blossom5-v2.05.src/PMinterface.cpp"
#include "blossom5-v2.05.src/MinCost/MinCost.cpp"
#include "EulerCircuit.h"
#include "fstream"
#include <map>
#include <string>
#include <set>
#include <cstdio>
#include "test_generation.h"

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;

void run_test(long long test_num) {

    // Число вершин и ребер в изначальном графе
    long long N, M;

    // Хранение нашего графа и его минимального остова в формате <вес, <вершина1, вершина2>>
    vector<pair<long long, pair<long long, long long>>> g, MST;

    // Веса в нашем графе
    vector<vector<long long>> w;

    // Степени вершин в минимальном остове
    vector<long long> degsInMST;

    string filename = "input" + to_string(test_num) + ".txt";
    freopen(filename.c_str(), "r", stdin);

    std::ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    vector<long long> t_w(N);
    w.resize(N, t_w);

    for (long long k = 0; k < M; k++) {
        pair<long long, pair<long long, long long>> tmp;
        cin >> tmp.first >> tmp.second.first >> tmp.second.second;
        g.push_back(tmp);
        w[tmp.second.first - 1][tmp.second.second - 1] = tmp.first;
        w[tmp.second.second - 1][tmp.second.first - 1] = tmp.first;
    }

    MST = mst(N, g);

    degsInMST.resize(N, 0);

    vector<long long> oddVertices;

    for (auto v : MST) {
        degsInMST[v.second.first - 1]++;
        degsInMST[v.second.second - 1]++;
    }

    for (long long k = 0; k < degsInMST.size(); k++) {
        if (degsInMST[k] % 2 == 1) {
            oddVertices.push_back(k + 1);
        }
    }

    vector<vector<long long>> costMatrix;
    vector<long long> tmp;
    tmp.resize(oddVertices.size(), 0);
    costMatrix.resize(oddVertices.size(), tmp);

    for (long long i = 0; i < oddVertices.size(); i++) {
        for (long long j = 0; j < oddVertices.size(); j++) {
            costMatrix[i][j] = w[oddVertices[i] - 1][oddVertices[j] - 1];
        }
    }

    vector<long long> matching = get_min_perfect_matching(costMatrix);

    vector<vector<long long>> eulerGraph;
    vector<long long> eulerTmp;
    eulerTmp.resize(N, 0);
    eulerGraph.resize(N, eulerTmp);

    for (auto edge : MST) {
        int a = edge.second.first - 1;
        int b = edge.second.second - 1;
        eulerGraph[a][b] = 1;
        eulerGraph[b][a] = 1;
    }

    for (long long x = 0; x < matching.size(); x++) {
        int a = oddVertices[x] - 1;
        int b = oddVertices[matching[x]] - 1;

        if (eulerGraph[a][b] < 2) {
            eulerGraph[a][b]++;
        }
    }

    vector<long long> circuit;
    circuit = HamiltonCircuitFromEuler(euler_cycle(eulerGraph));

    int answer = 0;

    for (long long i = 0; i < circuit.size() - 1; i++) {
        answer += w[circuit[i]][circuit[i + 1]];
    }

    cerr << "Ответ на тест (истинный ответ " << N << ") " <<  test_num << " равен " << answer << endl;
}



int main(int argc, const char * argv[]) {

    srand(42);

    for (int i = 0; i < TESTS; i++) {
        gen_test(VERTEX_MIN + i * ((VERTEX_MAX - VERTEX_MIN) / (TESTS - 1)), i);
    }

    for (int i = 0; i < TESTS; i++) {
        run_test(i);
    }

    return 0;
}