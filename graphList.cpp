#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

class VertexOutOfRange : public runtime_error {
    public:
        VertexOutOfRange(int vertices): runtime_error(
            "vertex not present in graph ") {}
};                                                                             


class DisJointSet {
    int *arr;
    int size;

    public:
        DisJointSet(int size) {
            arr = new int[size + 1];
            for (int i = 0; i <= size; i++) {
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
    while (parent > 0) {
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
}


class Edge {
    int desti;
    int source;
    int weight;

    public:
        Edge();
        
        Edge(int source, int desti, int weight) {
            this->source = source;
            this->desti = desti;
            this->weight = weight;
        }

        Edge(int source, int desti) {
            this->source = source;
            this->desti = desti;
            this->weight = 0;
        }

        int getWeight() {
            return weight;
        }

        int getSource() {
            return source;
        }

        int getDestination(){
            return desti;
        }
}; 

bool compare(Edge u, Edge v) {
    if (u.getWeight() < v.getWeight()) {
        return true;
    }
    return false;
}


class Graph {
    vector<int> *adjancyList;
    int vertices;
    int noOfEdges;
    vector<Edge> edges;

    public:
        Graph(int vertices);
        void addEdge(int u, int v);
        void addEdge(int u, int v, int weight);
        void removeEdge(int u, int v);
        bool hasEdge(int u, int v);
        int getWeight(int u, int v) {
            for (auto it = edges.begin(); it != edges.end(); it++) {
                Edge e = *it;
                if ((e.getSource() == u && e.getDestination() == v) || 
                    (e.getDestination() == u && e.getSource() == v)) {
                    return e.getWeight();
                }
            }
            cout << "edge not present " << endl;
            exit(1);
        } 

        void breadthFirstTraversal(int sourceVertex);
        void depthFirstTraversal(int sourceVertex);
        void printGraph(int vertex);
        
        bool isValidVertex(int vertex);
        bool areValidVertex(int u, int v);
        
        void printGraph();
        void printEdges();

        Graph getMinimumSpanningKuskal();
        Graph getMinimumSpanningPrims();
};

Graph::Graph(int vertices) {
    noOfEdges = 0;
    this->vertices = vertices;
    adjancyList = new vector<int>[vertices];
}

void Graph::addEdge(int u, int v) {
    //Add edge between u and v, where u, v are vertices
    addEdge(u, v, 0);
}

void Graph::addEdge(int u, int v, int weight) {
    if (areValidVertex(u, v)) {
        noOfEdges++;
        if (!hasEdge(u, v)) {
            Edge e = Edge(u, v, weight);
            edges.push_back(e);
            adjancyList[u-1].push_back(v);
            if (u != v) {
                adjancyList[v-1].push_back(u);
            }       
        }
    }
    else {
        throw VertexOutOfRange(vertices);
    }
}

bool Graph::isValidVertex(int vertex) {
    //Checks if given vertex is valid
    if (vertex >= 1 && vertex <= vertices) {
        return true;
    }
    return false;
}

bool Graph::areValidVertex(int u, int v) {
    if (isValidVertex(u) && isValidVertex(v)) {
        return true;
    }
    return false;
}

bool Graph::hasEdge(int u, int v) {
    if (areValidVertex(u, v)) {
        for (int i = 0; i < adjancyList[u-1].size(); i++) {
            if (adjancyList[u-1][i] == v) {
                return true;
            }
        }
        return false;
    }
    /*
    TODO : add error handling block
    */
    return false;
}

void Graph::printGraph() {
    for (int i = 0; i < vertices; i++) {
        cout << i + 1 << " >>> "; 
        for (int j = 0; j < adjancyList[i].size(); j++) {
            cout << adjancyList[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::printEdges() {
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].getSource();
        int v = edges[i].getDestination();
        int w = edges[i].getWeight();
        cout << "u => "<< u << " v => " << v << " w => " << w << endl;
    }
}

Graph Graph::getMinimumSpanningKuskal() {
    sort(edges.begin(), edges.end(), compare);
    Graph minSpanTree(vertices);
    DisJointSet helperSet = DisJointSet(vertices);
    for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].getSource();
        int v = edges[i].getDestination();
        int w = edges[i].getWeight();
        if (helperSet.find(u) != helperSet.find(v)) {
                minSpanTree.addEdge(u, v, w);
                helperSet.doUnion(u, v);
        }
    }
    return minSpanTree;
}

Graph Graph::getMinimumSpanningPrims() {
    int key[vertices + 1];
    int parent[vertices + 1];
    set<int> verticesInQueue;
    for (int i = 1; i <= vertices; i++) {
        key[i] = INT32_MAX;
        parent[i] = -1;
    }
    key[1] = 0;
    priority_queue < int, vector<int>, greater<int> > minQ;
    for (int i = 1; i <= vertices; i++) {
        minQ.push(key[i]);
        verticesInQueue.insert(i);
    }
    while (!minQ.empty()) {
        int u = minQ.top();
        minQ.pop();
        verticesInQueue.erase(u);
        vector<int> *vertexList = &adjancyList[u-1];
        for (auto it = vertexList->begin(); it != vertexList->end(); it++) {
            int v = *it; 
            if (verticesInQueue.find(*it) != verticesInQueue.end() &&
                getWeight(u , v) < key[v]
               ) {
                parent[v] = u;
                key[v] = getWeight(u, v);
            }
        }
    }
    minQ.top();
    Graph g = Graph(vertices);
    for (int i = 1; i <= vertices; i++) {
        int u = i;
        int v = parent[u];
        int w = getWeight(u, v);
        g.addEdge(u, v, w);
    }
    return g;
}

int main() {
    Edge e = Edge(1, 2);
    Edge h = Edge(1, 2, 3);
    int vertices;
    int edges;
    cout << "enter number of vertices ";
    cin >> vertices;
    cout << "enter number of edges ";
    cin >> edges;
    Graph g(vertices);
    g.printGraph();
    int i = 0;
    while (i < edges) {
        int u, v, w;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
        //g.printGraph();
        // g.printEdges();
        i++;
    }
    Graph min = g.getMinimumSpanningPrims();
    min.printGraph();
    min.printEdges();
}