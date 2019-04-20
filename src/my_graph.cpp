#include "../inc/my_graph.hh"

Graph::Graph(Edge *edges, int n, int N) {
    head = new Node*[N];
    this->nodes_amount = N;

    for (int i = 0; i < N; i++)
        head[i] = nullptr;

    for (int i = 0; i < n; i++)
    {
        int source = edges[i].source;
        int destination = edges[i].destination;
        int weight = edges[i].weight;

        Node * new_node = getAdjListNode(destination, weight, head[source]);

        head[source] = new_node;
    }
}

Graph::~Graph() {
    for (int i = 0; i < nodes_amount; i++)
        delete [] head[i];

    delete[] head;
}

void show_list(Node *ptr, int i)
{
    while (ptr != nullptr)
    {
        cout << "(" << i << "," << ptr->value << ", " << ptr->cost << ") ";
        ptr = ptr->next;
    }
    cout << endl;
}
