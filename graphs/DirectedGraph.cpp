#include<bits/stdc++.h>

using namespace std;

int GRAPH_MAX_SIZE = 100;

enum VertexAttributes {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2,
    NIL = -1
};

class Vertex {
    public:
        
        int id;
        int color;
        int distance;
        int predecessor;
        int discoveryTime;
        int finishingTime;
    
        Vertex(){
            color = WHITE;
            distance = INT32_MAX;
            predecessor = NIL;
            discoveryTime = -1;
            finishingTime = -1;
        }

        bool isDiscovered() {
            return color != WHITE;
        }

        void setDiscovered() {
            color = GRAY;
        }

        void setExplored() {
            color = BLACK;
        }

        static Vertex *createVertexListFor(int numberOfVertices);
        
        static bool compareByDiscoveryTime(Vertex &v, Vertex &u);

        static bool compareByFinishingTime(Vertex &v, Vertex &u);
};

Vertex *Vertex::createVertexListFor(int numberOfVertices) {
    Vertex *vertices = new Vertex[numberOfVertices + 1];
    for (int i = 1; i <= numberOfVertices; i++) {
        vertices[i].id = i; 
    }
    return vertices;
}


bool Vertex::compareByDiscoveryTime(Vertex &v, Vertex &u) {
    return (v.discoveryTime < u.discoveryTime);
}

bool Vertex::compareByFinishingTime(Vertex &v, Vertex &u) {
    return (v.finishingTime < u.finishingTime);
}


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
        void dfsVisit(int u, int &time, Vertex *vertices);
    public:
        void dfsVisit(int u, bool visited[]);
        Graph();
        Graph(int maxVertices);
        bool hasEdgeBetween(int u, int v);
        void addEdge(int u, int v);
        void addEdge(int u, int v, int w);
        void printAdjancyList();
        vector<Vertex> bfsTraversal(int source);
        vector<Vertex> dfsTraversal();
        int *dfsTraversalFrom(int source);
        int *dfsTraversalInOrder(int vertices[]);
        int *topologicalSort(); 
        Graph getTranspose();
        void printStronglyConnectedComponent();
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

void Graph::addEdge(int u, int v) {
    if (!hasEdgeBetween(u, v)) {
        adjancyList[u].push_back(v);
        Edge e = createEdge(u, v, 0);
        edges.push_back(e);
    }
}

void Graph::addEdge(int u, int v, int weight) {
    if (!hasEdgeBetween(u, v) && u != v) {
        adjancyList[u].push_back(v);
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

vector<Vertex> Graph::bfsTraversal(int source) {
    Vertex *vertices = Vertex::createVertexListFor(maxVertices);
    vector<Vertex> bfs;
    Vertex &sourceVertex = vertices[source]; 
    sourceVertex.distance = 0;
    sourceVertex.setDiscovered();
    queue<int> vertexQueue;
    vertexQueue.push(source);
    while (!vertexQueue.empty()) {
        int u = vertexQueue.front();
        vertexQueue.pop();
        for (int v : adjancyList[u]) {
            Vertex &vertex = vertices[v];
            if (!vertex.isDiscovered()) {
                vertex.setDiscovered();
                vertex.distance = vertices[u].distance + 1;
                vertex.predecessor = u;
                vertexQueue.push(v);
            }
        }
        cout << u << " ";
        bfs.push_back(vertices[u]);
        vertices[u].setExplored();
    }
    cout << endl;
    delete [] vertices;
    return bfs;
}

int *

vector<Vertex> Graph::dfsTraversal() {
    Vertex *vertices = Vertex::createVertexListFor(maxVertices);
    vector<Vertex> dfs;
    int time = 0;
    for (int i = 1; i <= maxVertices; i++) {
        if (!vertices[i].isDiscovered()) {
            dfsVisit(i, time, vertices);   
        }
    }
    sort(vertices + 1, vertices + maxVertices + 1, Vertex::compareByDiscoveryTime);
    for (int i = 1; i <= maxVertices; i++) {
        dfs.push_back(vertices[i]);
    }
    delete [] vertices;
    cout << endl;
    return dfs;
}

void Graph::dfsVisit(int u, int &time, Vertex *vertices) {
    time += 1;
    vertices[u].discoveryTime = time;
    vertices[u].setDiscovered();
    cout << u << " ";
    for (int v : adjancyList[u]) {
        if (!vertices[v].isDiscovered()) {
            vertices[v].predecessor = u;
            dfsVisit(v, time, vertices);
        }
    }
    vertices[u].setExplored();
    time += 1;
    vertices[u].finishingTime = time;
}

int *Graph::dfsTraversalFrom(int source) {
    bool visited[maxVertices];
    for (int i = 1; i <= maxVertices; i++) {
        visited[i] = false;
    }
    dfsVisit(source, visited);
    cout << endl;
}

void Graph::dfsVisit(int u, bool visited[]) {
    visited[u] = true;
    cout << u << " ";
    for (int v : adjancyList[u]) {
        if (!visited[v]) {
            dfsVisit(v, visited);
        }
    }
}

int *Graph::topologicalSort() {
    vector<Vertex> dfsOrder = dfsTraversal();
    sort(dfsOrder.begin(), dfsOrder.end(), Vertex::compareByFinishingTime);
    int *vertices = new int[maxVertices];
    int j = maxVertices - 1;
    for (Vertex v : dfsOrder) {
        vertices[j--] = v.id;
    }
    return vertices;
}

Graph Graph::getTranspose() {
    Graph transposeGraph = Graph(maxVertices);
    for (int i = 1; i <= maxVertices; i++) {
        for (int u : adjancyList[i]) {
            transposeGraph.addEdge(u, i);
        }
    }
    return transposeGraph;
}

void Graph::printStronglyConnectedComponent() {
    vector<Vertex> dfs = dfsTraversal();
    sort(dfs.begin(), dfs.end(), Vertex::compareByFinishingTime);
    Graph transpose = getTranspose();
    bool visited[maxVertices + 1];
    for (int i = 1; i <= maxVertices; i++) {
        visited[i] = false;
    }
    for (int i = maxVertices - 1; i >= 0; i--) {
        if (!visited[dfs[i].id]) {
            transpose.dfsVisit(dfs[i].id, visited);
            cout << endl;
        }
    }
}

int main() {
    int graphSize = 6;
    int edges = 7;
    Graph g = Graph(graphSize);
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        g.addEdge(u, v);
    }
    g.printAdjancyList();
    g.printStronglyConnectedComponent();
    return 0;
}

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