
#include <iostream>
#include <queue>
#include "heap.h" 
#include <limits>
#include <algorithm>

using namespace std;

// 定义无限大的距离
const int INF = numeric_limits<int>::max();

// 边的结构体
struct Edge {
    int to;
    int weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// 图的类
class Graph {
private:
    int numVertices;
    bool directed;
    Vector<Vector<Edge>> adjList;

public:
    // 构造函数
    Graph(int vertices, bool isDirected = false) : numVertices(vertices), directed(isDirected), adjList(vertices) {}

    // 添加边
    void addEdge(int from, int to, int weight = 1) {
        adjList[from].emplace_back(to, weight);
        if (!directed) {
            adjList[to].emplace_back(from, weight);
        }
    }

    // 获取邻接表
    const Vector<Vector<Edge>>& getAdjList() const {
        return adjList;
    }

    int getNumVertices() const {
        return numVertices;
    }

    // BFS
    void BFS(int start) const {
        Vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        cout << "BFS Traversal starting from vertex " << start << ": ";
        while (!q.empty()) {
            int current = q.front();
            q.pop();
            cout << current << " ";
            for (const auto& edge : adjList[current]) {
                if (!visited[edge.to]) {
                    visited[edge.to] = true;
                    q.push(edge.to);
                }
            }
        }
        cout << endl;
    }

    // DFS
    void DFS(int start) const {
        Vector<bool> visited(numVertices, false);
        // 使用自定义栈替换std::stack
        Stack<int> s;  
        s.push(start);
        cout << "DFS Traversal starting from vertex " << start << ": ";
        while (!s.empty()) {
            int current = s.top();
            s.pop();
            if (!visited[current]) {
                visited[current] = true;
                cout << current << " ";
                // 为了保持与递归DFS相同的顺序，这里需要逆序添加邻接点
                for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                    if (!visited[it->to]) {
                        s.push(it->to);
                    }
                }
            }
        }
        cout << endl;
    }

    // Dijkstra 最短路径算法
    void Dijkstra(int start) const {
        Vector<int> dist(numVertices, INF);
        dist[start] = 0;
        // 优先级队列，按距离从小到大排列
        priority_queue<pair<int, int>, Vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (currentDist > dist[u]) continue;

            for (const auto& edge : adjList[u]) {
                int v = edge.to;
                int weight = edge.weight;
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        // 输出结果
        cout << "Shortest distances from vertex " << start << ":" << endl;
        for (int i = 0; i < numVertices; ++i) {
            if (dist[i] == INF)
                cout << "Vertex " << i << ": INF" << endl;
            else
                cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }

    void PrimMST() const ｛
        Vector<bool> inMST(numVertices, false);
        // 用于存储结果的边
        Vector<pair<int, int>> mstEdges;
        // 优先级队列，存储 (权重, 目标顶点, 来自哪个顶点)
        Vector<int> parent(numVertices, -1);
        // 优先级队列
        priority_queue<pair<int, int>, Vector<pair<int, int>>, std::greater<pair<int, int>>> pq;
        // 从顶点0开始
        pq.emplace(0, 0);

        while (!pq.empty()) {
            int weight = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (inMST[u]) continue;
            inMST[u] = true;
            if (parent[u] != -1) {
                mstEdges.emplace_back(parent[u], u);
            }
            for (const auto& edge : adjList[u]) {
                int v = edge.to;
                if (!inMST[v]) {
                    pq.emplace(edge.weight, v);
                    if (parent[v] == -1 || edge.weight < adjList[parent[v]][v].weight) {
                        parent[v] = u;
                    }
                }
            }
        }

        // 输出结果
        cout << "Minimum Spanning Tree edges:" << endl;
        for (const auto& edge : mstEdges) {
            cout << edge.first << " - " << edge.second << endl;
        }
    }
};

int main() {
    Graph g(6, false);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 3, 4);
    g.addEdge(3, 4, 2);
    g.addEdge(4, 5, 6);
    g.addEdge(2, 5, 5);
    g.BFS(0);
    g.DFS(0);
    g.Dijkstra(0);
    g.PrimMST();

    return 0;
}
