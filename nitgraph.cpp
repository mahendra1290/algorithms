#include <bits/stdc++.h>

using namespace std;

typedef struct node
{
    int index;
    node *next;
} node;

typedef struct linkedList
{
    node *head;
} linkedList;

typedef struct graph
{
    int n;
    linkedList *array;
} graph;

graph *createGraph(int n)
{
    graph *Graph = (graph *)malloc(sizeof(graph));
    Graph->n = n;
    Graph->array = (linkedList *)malloc(n * sizeof(linkedList));
    for (int i = 0; i < n; i++)
        Graph->array[i].head = NULL;
}
void addedge(graph *Graph, int src, int dest)
{
    node *newnode = (node *)malloc(sizeof(node));
    newnode->index = dest;
    newnode->next = Graph->array[src].head;
    Graph->array[src].head = newnode;
    newnode->index = src;
    newnode->next = Graph->array[dest].head;
    Graph->array[dest].head = newnode;
}
void printGraph(graph *Graph)
{
    node *temp;
    for (int i = 0; i < Graph->n; i++)
    {
        temp = Graph->array[i].head;
        while (temp != NULL)
        {
            cout << temp->index << " ";
            temp = temp->next;
        }
        cout << endl;
    }
}
int main()
{
    int n;
    cin >> n;
    graph *Graph = createGraph(n);
    int number_of_paths;
    cin >> number_of_paths;
    int src, dest;
    for (int i = 0; i < number_of_paths; i++)
    {
        cin >> src >> dest;
        addedge(Graph, src, dest);
    }
    printGraph(Graph);
    return 0;
}