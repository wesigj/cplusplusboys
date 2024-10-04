#include <iostream>
#include <vector>
#include <list>
#include <stack>

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

    // 深度优先搜索
    void DFS(T vertex, std::stack<T> &stack, std::vector<bool> &visited) {
        // 访问当前节点
        std::cout << vertex << " ";
        visited[vertex] = true;

        // 访问所有未被访问的邻接节点
        for (auto adjVertex : adj[vertex]) {
            if (!visited[adjVertex]) { DFS(adjVertex, stack, visited); }
        }
    }

    // 执行DFS的公共方法
    void performDFS(T startVertex) {
        std::vector<bool> visited(adj.size(), false); // 跟踪访问的节点
        std::stack<T>     stack; // 使用堆栈来保存节点

        // 访问起始节点
        stack.push(startVertex);
        while (!stack.empty()) {
            T currentVertex = stack.top();
            stack.pop();
            if (!visited[currentVertex]) { DFS(currentVertex, stack, visited); }
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

    // 执行深度优先搜索
    graph.performDFS(0);

    return 0;
}