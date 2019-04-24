#include "../inc/BellmanFord.hh"


void showResults(int distance[], int source, int n)
{
    std::cout << std::endl;
    std::cout << "Node   Distance from (" << source << ")" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << i << "\t\t";
        if (distance[i] == INT32_MAX)
            std::cout << "INF (not connected)" << std::endl;
        else if (distance[i] == INT32_MIN)
            std::cout << "-INF (negative cycle)" << std::endl;
        else
            std::cout << distance[i] << std::endl;
    }
    std::cout << std::endl;
}

void BellmanFord(GraphList *graph, int source)
{
    int V = graph->getNodesAmount();
    int * distance = new int[V];

    for (int i = 0; i < V; i++)
        distance[i] = INT32_MAX; // INF
    distance[source] = 0;

    for (int i = 1; i <= V-1; i++)
    {
        for(int j = 0; j < V; j++)
        {
            Node * head_ptr = graph->getHead(j);
            while(head_ptr != nullptr)
            {
                int src = j;
                int dest = head_ptr->value;
                int weight = head_ptr->cost;

                if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                    distance[dest] = distance[src] + weight;

                head_ptr = head_ptr->next;
            }
        }
    }

    for(int j = 0; j < V; j++)
    {
        Node * head_ptr = graph->getHead(j);
        while(head_ptr != nullptr)
        {
            int src = j;
            int dest = head_ptr->value;
            int weight = head_ptr->cost;

            if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                distance[dest] = INT32_MIN;



            head_ptr = head_ptr->next;
        }
    }

    showResults(distance, source, V);
    delete [] distance;
}

