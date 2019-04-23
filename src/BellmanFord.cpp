#include "../inc/BellmanFord.hh"


void showResults(int distance[], int source, int n)
{
    std::cout << "Node   Distance from (" << source << ")" << std::endl;
    for (int i = 0; i < n; i++)
        std::cout << i << "\t\t" << distance[i] << std::endl;
}
// TODO
void BellmanFord(GraphList *graph, int source)
{
    int V = graph->getNodesAmount();
    int E = graph->getEdgesAmount();
    int * distance = new int[V];

    for (int i = 0; i < V; i++)
        distance[i] = INT32_MAX; // INF
    distance[source] = 0;

    for (int i = 0; i < V ; i++)
    {
        Node * head_ptr = graph->getHead(i);
        while (head_ptr != nullptr && head_ptr->next != nullptr)
        {
            int src = head_ptr->value;
            int dst = head_ptr->next->value;
            int weight = head_ptr->cost;
            head_ptr = head_ptr->next;

            if (distance[src] != INT32_MAX && distance[src] + weight < distance[dst])
                distance[dst] = distance[src] + weight;
        }
    }

    Node * head_ptr = graph->getHead(0);
    while (head_ptr != nullptr && head_ptr->next != nullptr)
    {
        int src = head_ptr->value;
        int dst = head_ptr->next->value;
        int weight = head_ptr->cost;
        head_ptr = head_ptr->next;

        if (distance[src] != INT32_MAX && distance[src] + weight < distance[dst])
            std::cout << "UJEMNY CYKL ELO" << std::endl;
    }

    showResults(distance, source, V);
    delete [] distance;
}

