#include<bits/stdc++.h>

using namespace std;

class Graph {
    int **adjancyMatrix;
    int no_of_vertices;
    public:
       Graph(int no_of_vertices);
       void addEdge(int source, int destination);
};

Graph::Graph(int no_of_vertices)
{
    this->no_of_vertices = no_of_vertices;
    adjancyMatrix = new int*[no_of_vertices];
    for (int i = 0; i < no_of_vertices; i++) {
        adjancyMatrix[i] = new int[no_of_vertices];
    }
    for (int i = 0; i < no_of_vertices; i++)
    {
        for (int j = 0; j < no_of_vertices; j++)
        {
            adjancyMatrix[i][j] = 0;
        }
    }
}
 void Graph::addEdge(int source, int destination)
{
    if(source > no_of_vertices && destination > no_of_vertices)
    {
        cout << "wrong input"<<endl;
    }

    else
    {
        adjancyMatrix[u][v] = 1;
        
    }
    
}

int main() {
    return 0;
}