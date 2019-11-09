#include <iostream>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int GRAPH_MAX_SIZE = 100;

enum VertexAttributes {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2,
    NIL = -1
};

struct Vertex {
    int id;
    int key;
    int parent;
};

struct VertexBfs {
    int color;
    int distance;
    int predecessor;
};

VertexBfs *getVertexListForBfs(int numberOfVertices);

Vertex createVertex(int id, int key, int parent);

Vertex createVertex(int id, int key);

Vertex createVertex(int id);

struct Edge {
    int u;
    int v;
    int weight;
};

Edge createEdge(int u, int v, int weight);

Edge createEdge(int u, int v);

class Graph {
    private:
        vector<int> *adjancyList;
        int maxVertices;
        vector<Edge> edges;
    public:
        Graph();
        Graph(int maxVertices);
        bool hasEdgeBetween(int u, int v);
        void addEdge(int u, int v);
        void addEdge(int u, int v, int w);
        void printAdjancyList();
        void bfsTraversal(int source);
};


Graph::Graph() {
    adjancyList = new vector<int>[GRAPH_MAX_SIZE];
    maxVertices = GRAPH_MAX_SIZE;
}

Graph::Graph(int maxVertices) {
    this->maxVertices = maxVertices;
    adjancyList = new vector<int>[maxVertices + 1];
}

bool Graph::hasEdgeBetween(int u, int v) {
    for (int i : adjancyList[u]) {
        if (i == v) {
            return true;
        }
    }
    return false;
}

void Graph::addEdge(int u, int v, int weight) {
    if (!hasEdgeBetween(u, v) && u != v) {
        adjancyList[u].push_back(v);
        adjancyList[v].push_back(u);
        Edge e = createEdge(u, v, weight);
        edges.push_back(e);
    }
}

void Graph::printAdjancyList() {
    for (int i = 1; i <= maxVertices; i++) {
        cout << i << " >>>> ";
        for (int j : adjancyList[i]) {
            cout << j << " ";
        }
        cout << "\n";
    }
}

void Graph::bfsTraversal(int source) {
    VertexBfs vertices[maxVertices + 1];
    for (int i = 1; i <= maxVertices; i++) {
        vertices[i].color = WHITE;
        vertices[i].distance = INT32_MAX;
        vertices[i].predecessor = NIL;
    }
    vertices[source].color = GRAY;
    vertices[source].distance = 0;
    vertices[source].predecessor = NIL;
    queue<int> vertexQueue;
    vertexQueue.push(source);
    while (!vertexQueue.empty()) {
        int u = vertexQueue.front();
        vertexQueue.pop();
        for (int v : adjancyList[u]) {
            if (vertices[v].color == WHITE) {
                vertices[v].color = GRAY;
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].predecessor = u;
                vertexQueue.push(v);
            }
        }
        cout << u << " ";
        vertices[u].color = BLACK;
    }
    cout << "\n";
}

int main() {
    int graphSize = 10;
    Graph g = Graph(graphSize);
    for (int i = 0; i < graphSize; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
        g.printAdjancyList();
    }
    g.bfsTraversal(1);
    return 0;
}

VertexBfs *getVertexListForBfs(int numberOfvertices)

Edge createEdge(int u, int v) {
    return createEdge(u, v, 0);
}

Edge createEdge(int u, int v, int weight) {
    Edge e;
    e.u = u;
    e.v = v;
    e.weight = weight;
    return e;
}