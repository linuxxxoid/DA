#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

const int WHITE = -1;//вершина не посещена
const int GREY = 0;//вершина обрабатывается
const int BLACK = 1;//вершина обработана
void topologicalSort(std::vector<std::vector<int>>&, std::vector<int>&, std::vector<int>&, int);
bool dfs(int, std::vector<std::vector<int>>&, std::vector<int>&, std::vector<int>&);


int main(int argc, const char * argv[]) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    std::vector<int> color(n, WHITE);
    std::vector<int> result;
    
    for (int i = 0; i < m; ++i) {
        int begin, end;
        std::cin >> begin >> end;
        graph[begin - 1].emplace_back(end - 1);
    }
    
    clock_t time;
    time = clock();
    
    topologicalSort(graph, color, result, n);
    
    time = clock() - time;
    std::cout << "Topological Sort" << std::endl;
    std::cout << (double)time/CLOCKS_PER_SEC << std::endl;
    
    int size = (int) result.size();
    for (int i = 0; i < size; ++i)
        std::cout << result[i] << " ";
    
    return 0;
}
bool dfs(int v, std::vector<std::vector<int>>& graph, std::vector<int>& color, std::vector<int>& result)  {
    color[v] = GREY;
    
    int size = (int) graph[v].size();
    for (int i = 0; i < size; ++i) {
        int to = graph[v][i];
        if (color[to] == WHITE) {
            if (dfs(to, graph, color, result))
                return true;
        }
        else if (color[to] == GREY) return true;
    }
    color[v] = BLACK;
    result.emplace_back(v + 1);
    return false;
}

void topologicalSort(std::vector<std::vector<int>>& graph, std::vector<int>& color, std::vector<int>& result, int size) {
    for (int i = 0; i < size; i++) {
        if (color[i] == WHITE) {
            bool cyclic = dfs(i, graph, color, result);
            if (cyclic) {
                result.clear();
                result.emplace_back(-1);
                return;
            }
        }
    }
    reverse(result.begin(), result.end());
}
