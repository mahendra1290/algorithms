#include<bits/stdc++.h>

using namespace std;

class Graph{
    int no_of_vertices;
    vector<int> *adjancy_list = NULL;
    public:
        Graph(int no_of_vertices);
        void addEdge(int source, int destination);
        void checkVertex(int vertex);
        void printAdjancyList();
        void bfs(int source);
        void dfsUtil(int source, bool *visited);
        void dfsTraversal();

};

Graph::Graph(int no_of_vertices)
{
    this->no_of_vertices = no_of_vertices;
    adjancy_list = new vector<int>[no_of_vertices];
}

void Graph::addEdge(int source, int destination)
{
    checkVertex(source);
    checkVertex(destination);
    adjancy_list[source].push_back(destination);
}

void Graph::checkVertex(int vertex)
{
    if (vertex < 0 || vertex >= no_of_vertices)
    {
        cout << " mere ko bass daanta rehta hai maahi g ekdum chutiyaa insan hai maahi g" <<endl;
        exit(EXIT_FAILURE);
    }
}

void Graph::printAdjancyList()
{
    for (int i = 0;i < no_of_vertices; i++)
    {
        cout << i << " --> ";
        for (int j = 0; j < adjancy_list[i].size(); j++) {
            cout << adjancy_list[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::bfs(int source)
{
    bool visited[no_of_vertices] = {false};
    visited[source] = true;
    queue<int> vertex_queue;
    vertex_queue.push(source);
    while(!vertex_queue.empty())
    {
        int u = vertex_queue.front();
        vertex_queue.pop();
        cout << u << " ";
        for(int v : adjancy_list[u]) {
            if( visited[v] == false)
            {
                visited[v] = true;
                vertex_queue.push(v);
            }
        }
    }
    cout << endl;
    
}

void Graph::dfsTraversal() {
    bool visited[no_of_vertices] = {false};
    for (int i = 0; i < no_of_vertices; i++) {
        if (!visited[i]) {
            dfsUtil(i, visited);
        }
    }
}

void Graph::dfsUtil(int source, bool visited[])
{
    visited[source] = true;
    cout << source << " "; 
    for(int v : adjancy_list[source])
    {
        if(visited[v] == false)
        {
            dfsUtil(v, visited);
        }        
    }
}

int main()
{
    int n,edges,source,destination;
    cout << "enter the number of vertices" << endl;
    cin >> n;
    cout << "enter the number of edges" << endl;
    cin >> edges;
    Graph g(n);
    cout << "enter the source and destination"<<endl;
    for( int i = 0; i < edges; i++)
    {
        cin >> source;
        cin >> destination;
        g.addEdge(source,destination);
        g.printAdjancyList();
    }
    g.bfs(0);
    g.dfsTraversal();
}