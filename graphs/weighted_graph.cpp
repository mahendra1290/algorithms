#include<bits/stdc++.h>

using namespace std;

int NIL = -1;

int INFINITE = INT32_MAX;

struct Edge {
    int src;
    int dest;
    int weight;
};

Edge createEdge(int src, int dest, int weight) {
    Edge edge;
    edge.src = src;
    edge.dest = dest;
    edge.weight = weight;
    return edge;
}

bool compareEgde(Edge &e1, Edge &e2) {
    return e1.weight < e2.weight;
}

struct Vertex {
    int key;
    int distance;
    int predecessor;
    int discoveryTime;
    int finishingTime;
    bool isVisited;
};

Vertex createVertex(int key) {
    Vertex v;
    v.key = key;
    v.distance = INFINITE;
    v.predecessor = NIL;
    v.discoveryTime = NIL;
    v.finishingTime = NIL;
    v.isVisited = false;
    return v;
}

void printVertex(Vertex v) {
    cout << "key -> " << v.key <<"\n";
    if (v.distance != INFINITE) {
        cout << "distance -> " << v.distance << "\n";
    }
    if (v.discoveryTime != NIL) {
        cout << "discoveryTime -> " << v.discoveryTime << "\n";
        cout << "finishingTime -> " << v.finishingTime << "\n";
    }
}

bool compareByDiscoveryTime(Vertex &v1, Vertex &v2) {
    return v1.discoveryTime < v2.discoveryTime;
}

bool compareByFinishingTime(Vertex &v1, Vertex &v2) {
    return v1.finishingTime < v2.finishingTime;
}


class DisJointSet {
    int *arr;
    int size;

    public:
        DisJointSet(int size) {
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = -1;
            }
            this->size = size;
        }
        int find(int a);
        void doUnion(int a, int b);
};

int DisJointSet::find(int a) {
    int parent = arr[a];
    int temp = a;
    if (parent < 0) {
        return a;
    }
    while (parent >= 0) {
        a = parent;
        parent = arr[a];
    }
    arr[temp] = a;
    return a;
}

void DisJointSet::doUnion(int a, int b) {
    int parent1 = find(a);
    int parent2 = find(b);
    if (parent1 != parent2) {
        if (arr[parent1] <= arr[parent2]) {
            arr[parent1] += arr[parent2];
            arr[parent2] = parent1;
        }
        else {
            arr[parent2] += arr[parent1];
            arr[parent1] = parent2;
        }
    }
    cout << endl;
}

class WeightedGraph {
    private:
        int numberOfVertices;
        vector<int> *adjancyList;
        vector<Edge> edges;
        vector<Vertex> createVertexList();
        void dfsUtil(int src, int &time, bool *visited, vector<Vertex> &dfs);

    public:
        WeightedGraph(int numberOfVertices);
        void addEdge(int u, int v, int w = 0);
        void addEdge(Edge edge);
        void checkVertex(int vertex);
        void printAdjancyList();
        vector<Vertex> bfsTraversal(int src);
        vector<Vertex> dfsTraversal();
        vector<Vertex> dfsTraversal(int src);
        void topologicalSort();
        WeightedGraph getMinimumSpanningKruskal();
};

WeightedGraph::WeightedGraph(int numberOfVertices) {
    this->numberOfVertices = numberOfVertices;
    adjancyList = new vector<int>[numberOfVertices];
}

void WeightedGraph::addEdge(int src, int dest, int weight) {
    checkVertex(src);
    checkVertex(dest);
    adjancyList[src].push_back(dest);
    adjancyList[dest].push_back(src);
    edges.push_back(createEdge(src, dest, weight));
}

void WeightedGraph::addEdge(Edge edge) {
    addEdge(edge.src, edge.dest, edge.weight);
}

void WeightedGraph::checkVertex(int vertex) {
    if (vertex < 0 || vertex >= numberOfVertices) {
        cerr << "OUT_OF_BOUND "<< "\'" << vertex << "\'" << " not valid vertex";
        exit(EXIT_FAILURE);
    }
}

void WeightedGraph::printAdjancyList() {
    for (int i = 0; i < numberOfVertices; i++) {
        cout << i << " --> ";
        for (int v : adjancyList[i]) {
            cout << v << " ";
        }
        cout << "\n";
    }
}

vector<Vertex> WeightedGraph::bfsTraversal(int src) {
    vector<Vertex> vertices = createVertexList();
    vector<Vertex> bfs;
    vertices[src].isVisited = true;
    vertices[src].distance = 0;
    queue<int> vertexQueue;
    vertexQueue.push(src);
    while (!vertexQueue.empty()) {
        int u = vertexQueue.front();
        vertexQueue.pop();
        cout << u << " ";
        for (int v : adjancyList[u]) {
            if (!vertices[v].isVisited) {
                vertices[v].isVisited = true;
                vertices[v].distance = vertices[u].distance + 1;
                vertices[v].predecessor = u;
                vertexQueue.push(v);
            }
        }
        bfs.push_back(vertices[u]);
    }
    cout << endl;
    return bfs;
}

vector<Vertex> WeightedGraph::dfsTraversal() {
    int time = 0;
    bool visited[numberOfVertices] = {false};
    vector<Vertex> dfs;
    for (int i = 0; i < numberOfVertices; i++) {
        if (!visited[i]) {
            dfsUtil(i, time, visited, dfs);
        }
    }
    cout << endl;
    return dfs;
}

vector<Vertex> WeightedGraph::dfsTraversal(int src) {
    int time = 0;
    bool visited[numberOfVertices] = {false};
    vector<Vertex> dfs;
    dfsUtil(src, time, visited, dfs);
    cout << endl;
    return dfs;
}

void WeightedGraph::dfsUtil(int src, int &time, bool *visited, vector<Vertex> &dfs) {
    time += 1;
    visited[src] = true;
    Vertex vertex = createVertex(src);
    vertex.discoveryTime = time;
    cout << src << " ";
    int index = dfs.size();
    dfs.push_back(vertex);
    for (int v : adjancyList[src]) {
        if (!visited[v]) {
            dfsUtil(v, time, visited, dfs);
        }
    }
    dfs[index].finishingTime = ++time;
}

vector<Vertex> WeightedGraph::createVertexList() {
    vector<Vertex> vertices;
    for (int i = 0; i < numberOfVertices; i++) {
        Vertex v = createVertex(i);
        vertices.push_back(v);
    }
    return vertices;
}


WeightedGraph WeightedGraph::getMinimumSpanningKruskal() {
    WeightedGraph mst(numberOfVertices);
    sort(edges.begin(), edges.end(), compareEgde);
    DisJointSet disjointSet = DisJointSet(numberOfVertices);
    for (Edge edge : edges) {
        if (disjointSet.find(edge.src) != disjointSet.find(edge.dest)) {
            mst.addEdge(edge);
            disjointSet.doUnion(edge.src, edge.dest);
        }
    }
    return mst;
}

int main() {
    int vertices, edges;
    cout << "enter vertices and edges : ";
    cin >> vertices >> edges; 
    WeightedGraph graph(vertices);
    for (int i = 0; i < edges; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        //u--;
        //v--;
        graph.addEdge(u, v, w);
    }
    graph.printAdjancyList();
    // vector<Vertex> v = graph.dfsTraversal();
    // for (Vertex i : v) {
    //     printVertex(i);
    // }
    WeightedGraph mst = graph.getMinimumSpanningKruskal();
    mst.printAdjancyList();
    //graph.dfsTraversal();
}