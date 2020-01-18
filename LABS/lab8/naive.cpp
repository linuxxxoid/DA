#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <unordered_set>

void topologicalSort(std::vector<std::vector<int>>&, std::unordered_set<int>&, std::unordered_set<int>&, int, std::vector<int>&);


int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::unordered_set<int> vertex(n);
    std::unordered_set<int> result;
    std::vector<int> sum(n, 0);
    for (int i = 0; i < m; ++i) {
        int begin, end;
        std::cin >> begin >> end;
        graph[end - 1].emplace_back(begin - 1);
        sum[end-1]++;
        if (vertex.find(begin - 1) == vertex.end())
            vertex.emplace(begin - 1);
        if (vertex.find(end - 1) == vertex.end())
            vertex.emplace(end - 1);
    }
    
    clock_t time;
    time = clock();
    
    topologicalSort(graph, vertex, result, n, sum);
    
    time = clock() - time;
    std::cout << "Naive Topological Sort" << std::endl;
    std::cout << (double)time/CLOCKS_PER_SEC << std::endl;
    
    for (auto i = result.begin(); i != result.end(); ++i)
        std::cout << *i + 1 << " ";
    
    return 0;
}

void topologicalSort(std::vector<std::vector<int>>& graph, std::unordered_set<int>& vertex, std::unordered_set<int>& result, int size, std::vector<int>& sum) {
    while (result.size() < size) {
        for (auto g = vertex.begin(); g != vertex.end() ; ++g) {
            if (sum[*g] != 0 || result.find(*g) == result.end()) {
                result.emplace(*g);
                for (int j = 0; j < size; ++j) {
                    for (int k = 0; k < sum[j]; ++k) {
                        if (graph[j][k] == *g) {
                            sum[j]--;
                        }
                    }
                }
            }
        }
    }
}