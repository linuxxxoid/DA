#include <iostream>
#include <vector>
#include <limits>

const long INF = std::numeric_limits<long>::max();

struct Edge {
    unsigned long from, to;
    long cost;
};

void BellmanFord(const std::vector<Edge>& , const unsigned long&, const unsigned long&, const unsigned long&, const unsigned long&);


int main(int argc, const char * argv[]) {
    std::ios_base::sync_with_stdio(false);

    unsigned long n, m, start, finish, u, v;
    long weight;
    std::cin >> n >> m >> start >> finish;
    --start; --finish;
    std::vector<Edge> edge(m);

    for (unsigned long i = 0; i < m; ++i) {
        std::cin >> v >> u >> weight;
        --v; --u;
        edge[i].from = v;
        edge[i].to = u;
        edge[i].cost = weight;
    }

    BellmanFord(edge, n, m, start, finish);

    return 0;
}

void BellmanFord(const std::vector<Edge>& edge, const unsigned long& n, const unsigned long& m,const unsigned long& start,const unsigned long& finish) {
    std::vector<long> dist(n, INF);
    dist[start] = 0;
    for (unsigned long i = 0; i < n; ++i) {
        bool relaxation = false;
        for (unsigned long j = 0; j < m; ++j) {
            if (dist[edge[j].from] < INF) {
                if (dist[edge[j].to] > dist[edge[j].from] + edge[j].cost) {
                    dist[edge[j].to] = dist[edge[j].from] + edge[j].cost;
                    relaxation = true;
                }
            }
        }
        if (!relaxation) break;
    }

    if (dist[finish] == INF) std::cout << "No solution" << std::endl;
    else std::cout << dist[finish] << std::endl;
}

