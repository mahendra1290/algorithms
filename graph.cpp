#include <iostream>
#include <queue>

using namespace std;

class GraphByMatrix {

    int **adjancyMatrix;
    int vertices;

    public:
        GraphByMatrix(int noOfVertices);
        void addEdge(int u, int v);
        void removeEdge(int u, int v);
        void breadthFirstTraversal(int sourceVertice);
        void printGraph(int vertex);
        void printGraph();
};

GraphByMatrix::GraphByMatrix(int noOfVertices) {
    vertices = noOfVertices;
    adjancyMatrix = new int*[noOfVertices];
    for (int i = 0; i < noOfVertices; i++) {
        adjancyMatrix[i] = new int[noOfVertices];
    }
}

void GraphByMatrix::addEdge(int u, int v) {
    if ((u >=0 && u < vertices) && (v >= 0 && v < vertices)) {
        adjancyMatrix[u][v] = 1;
        adjancyMatrix[v][u] = 1;
    }
    else {
        cout << "invalid vertices "<< u <<" " << v << " entered " << endl;
    }
}

void GraphByMatrix::removeEdge(int u, int v) {
    if ((u >=0 && u < vertices) && (v >= 0 && v < vertices)) {
        adjancyMatrix[u][v] = 0;
        adjancyMatrix[v][u] = 0;
    }
    else {
        cout << "invalid vertices "<< u <<" " << v << " entered " << endl;
    }
}

void GraphByMatrix::breadthFirstTraversal(int sourceVertex) {
    bool hasVisited[vertices];
    for (int i = 0; i < vertices; i++) {
        hasVisited[i] = false;
    }
    queue<int> toVisit;
    toVisit.push(sourceVertex);
    while (!toVisit.empty()) {
        int vertex = toVisit.front();
        toVisit.pop();
        if (hasVisited[vertex] == false) {
            hasVisited[vertex] = true;
            cout << vertex << " ";
            for (int i = 0; i < vertices; i++) {
                if (adjancyMatrix[vertex][i] == 1 && hasVisited[i] == false) {
                    toVisit.push(i);
                }
            }
        }
    }
    cout << endl;
}

void GraphByMatrix::printGraph(int vertex) {
    if (vertex >=0 && vertex < vertices) {
        cout << vertex << " -> " ;
        for (int j = 0; j < vertices; j++) {
            if (adjancyMatrix[vertex][j] == 1) {
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

void GraphByMatrix::printGraph() {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << adjancyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    GraphByMatrix mini(5);
    while (true) {
        cout << "enter -1 -1 to exit\n";
        cout << "enter edge u, v = ";
        int u, v;
        cin >> u >> v;
        if (u == -1 || v == -1) {
            break;
        }
        mini.addEdge(u, v);
        mini.printGraph();
        for (int i = 0; i < 5; i++) {
            mini.printGraph(i);
        }
    }
    mini.breadthFirstTraversal(0);
    return 0;
}

