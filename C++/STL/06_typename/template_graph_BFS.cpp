#include <iostream>
#include <vector>
#include <list>
#include <queue>

// 模板类，表示图
template <typename T>
class Graph {
private:
    std::vector<std::list<T>> adj; // 邻接表

public:
    // 构造函数
    Graph(int numVertices) : adj(numVertices) {
    }

    // 添加边
    void addEdge(T src, T dest) {
        adj[src].push_back(dest); // 为无向图添加双向边
        adj[dest].push_back(src);
    }

    // 广度优先搜索
    void BFS(T startVertex) {
        std::vector<bool> visited(adj.size(), false); // 跟踪访问的节点
        std::queue<T>     queue;                      // 用于BFS的队列

        // 标记起始节点为已访问并入队
        visited[startVertex] = true;
        queue.push(startVertex);

        while (!queue.empty()) {
            T currentVertex = queue.front();
            queue.pop();
            std::cout << currentVertex << " ";

            // 访问所有未被访问的邻接节点
            for (auto adjVertex : adj[currentVertex]) {
                if (!visited[adjVertex]) {
                    visited[adjVertex] = true;
                    queue.push(adjVertex);
                }
            }
        }
    }
};

int main() {
    // 创建一个图实例，假设有5个顶点
    Graph<int> graph(5);
    graph.addEdge(0, 1);
    graph.addEdge(0, 2);
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);

    // 执行广度优先搜索
    std::cout << "Starting BFS from vertex 0:" << std::endl;
    graph.BFS(0);

    return 0;
}