class Graph {

    int **adjancyMatrix;
    int vertices;

    public:
        Graph(int noOfVertices);
        void addEdge(int u, int v);
        void removeEdge(int u, int v);
        void breadthFirstTraversal(int sourceVertice);
        void printGraph(int vertex);
        void printGraph();
};

Graph::Graph(int noOfVertices) {
    vertices = noOfVertices;
    adjancyMatrix = new int*[noOfVertices];
    for (int i = 0; i < noOfVertices; i++) {
        adjancyMatrix[i] = new int[noOfVertices];
    }
}

void Graph::addEdge(int u, int v) {
    if ((u >=0 && u < vertices) && (v >= 0 && v < vertices)) {
        adjancyMatrix[u][v] = 1;
        adjancyMatrix[v][u] = 1;
    }
    else {
        cout << "invalid vertices "<< u <<" " << v << " entered " << endl;
    }
}

void Graph::removeEdge(int u, int v) {
    if ((u >=0 && u < vertices) && (v >= 0 && v < vertices)) {
        adjancyMatrix[u][v] = 0;
        adjancyMatrix[v][u] = 0;
    }
    else {
        cout << "invalid vertices "<< u <<" " << v << " entered " << endl;
    }
}

void Graph::breadthFirstTraversal(int sourceVertex) {
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

void Graph::printGraph(int vertex) {
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

void Graph::printGraph() {
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            cout << adjancyMatrix[i][j] << " ";
        }
        cout << endl;
    }
}
