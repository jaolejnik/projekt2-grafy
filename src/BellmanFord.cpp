#include "../inc/BellmanFord.hh"


void showResults(std::unique_ptr<int[]> &distance, int * predecessor, int source, int n)
{
    std::cout << std::endl;
    std::cout << "Node\t\tDistance from (" << source << ")\t\tPath" << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << i << "\t\t\t";
        if (distance[i] == INT32_MAX)
            std::cout << "INF (not connected)\t\t\t\t\t\t";
        else if (distance[i] == INT32_MIN)
            std::cout << "-INF (negative cycle)\t\t\t\t\t\t";
        else if (i == source)
            std::cout << "SOURCE\t\t\t\t\t\t";
        else
            std::cout << distance[i] << "\t\t\t\t\t\t";

        int current = i;
        while (current != source && (distance[current] != INT32_MAX && distance[current] != INT32_MIN) )
        {
            std::cout << "("<< current << ")<-";
            current = predecessor[current];
        }
        if (distance[i] != INT32_MAX && distance[i] != INT32_MIN)
            std::cout << "(" << source << ")";
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

std::unique_ptr<int[]> BellmanFord(GraphList *graph, int source)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);
    int predecessor[V];

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
                {
                    distance[dest] = distance[src] + weight;
                    predecessor[dest] = src;
                }


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
    showResults(distance, predecessor, source, V);

    return distance;
}


std::unique_ptr<int[]> BellmanFord(GraphArray *graph, int source)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);

    for (int i = 0; i < V; i++)
        distance[i] = INT32_MAX; // INF
    distance[source] = 0;

    int *** adj_mat = graph->getAdjMatrix();

    for (int a = 1; a <= V-1; a++)
    {
        for(int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                int k = 0;
                while (adj_mat[i][j][k] != 0)
                {
                    int src = i;
                    int dest = j;
                    int weight = adj_mat[i][j][k];

                    if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                        distance[dest] = distance[src] + weight;

                    k++;
                }
            }
        }
    }

    for(int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int k = 0;
            while (adj_mat[i][j][k] != 0)
            {
                int src = i;
                int dest = j;
                int weight = adj_mat[i][j][k];

                if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                    distance[dest] = INT32_MIN;

                k++;
            }
        }
    }

    //showResults(distance, source, V);

    return distance;

}
