#include "../inc/BellmanFord.hh"


Path BellmanFord(GraphList *graph, int source, bool test)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);
    std::unique_ptr<int[]> predecessor(new int[V]);

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

            if (distance[src] != INT32_MAX && distance[src] != INT32_MIN && distance[src] + weight < distance[dest])
                distance[dest] = INT32_MIN;

            head_ptr = head_ptr->next;
        }
    }

    for(int j = 0; j < V; j++)
    {
        Node * head_ptr = graph->getHead(j);
        while(head_ptr != nullptr)
        {
            int src = j;
            int dest = head_ptr->value;

            if (dest == source)
            {
                head_ptr = head_ptr->next;
                continue;
            }


            if (distance[src] == INT32_MIN)
                distance[dest] = INT32_MIN;

            head_ptr = head_ptr->next;
        }
    }

    Path paths;
    paths.distance = move(distance);
    paths.actual_path = move(predecessor);

    if (!test)
        showResults(&paths, source, V);

    return paths;
}


Path BellmanFord(GraphArray * graph, int source, bool test)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);
    std::unique_ptr<int[]> predecessor(new int[V]);

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
                    {
                        distance[dest] = distance[src] + weight;
                        predecessor[dest] = src;
                    }

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

    for(int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int k = 0;
            while (adj_mat[i][j][k] != 0)
            {
                int src = i;
                int dest = j;
                
                if (distance[src] == INT32_MIN)
                    distance[dest] = INT32_MIN;

                k++;
            }
        }
    }


    Path paths;

    paths.distance = move(distance);
    paths.actual_path = move(predecessor);

    if (!test)
        showResults(&paths, source, V);

    return paths;
}


void showResults(Path * path, int source, int nodes_amount)
{
    std::cout << std::endl;
    std::cout << "Node\t\tDistance from (" << source << ")\t\tPath" << std::endl;
    for (int i = 0; i < nodes_amount; i++)
    {
        std::cout << i << "\t\t\t";
        if (path->distance[i] == INT32_MAX)
            std::cout << "INF (not connected)\t\t\t\t\t\t";
        else if (path->distance[i] == INT32_MIN)
            std::cout << "-INF (negative cycle)\t\t\t\t\t\t";
        else if (i == source)
            std::cout << "SOURCE\t\t\t\t\t\t";
        else
            std::cout << path->distance[i] << "\t\t\t\t\t\t";

        int current = i;
        while (current != source && (path->distance[current] != INT32_MAX && path->distance[current] != INT32_MIN) )
        {
            std::cout << "("<< current << ")<-";
            current = path->actual_path[current];
        }
        if (path->distance[i] != INT32_MAX && path->distance[i] != INT32_MIN)
            std::cout << "(" << source << ")";
        std::cout << std::endl;
    }

    std::cout << std::endl;
}


template <typename GraphType>
void findPathAB(GraphType * graph, int source, int destination)
{
    std::cout << std::endl;

    if (source >= graph->getNodesAmount() || destination >= graph->getNodesAmount())
    {
        std::cerr << "INVALID SOURCE OR DESTINATION!"<< std::endl;
        std::cerr << "These values must be between 0 and " << graph->getNodesAmount() -1 << " for this graph." << std::endl;
        exit(EXIT_FAILURE);
    }
    else if (source == destination )
    {
        std::cerr << "SOURCE AND DESTINATION ARE THE SAME!" << std::endl;
        std::cerr << "Source and destination should have different values." << std::endl;
        exit(EXIT_FAILURE);
    }

    Path path = BellmanFord(graph, source, true);

    if (path.distance[destination] == INT32_MAX)
    {
        std::cout << "It's impossible to get from (" << source << ") to (" << destination << ")." << std::endl;
        std::cout<< "(" << destination << ") is not connected." << std::endl;
    }

    else if (path.distance[destination] == INT32_MIN)
    {
        std::cout << "It's impossible to get from (" << source << ") to (" << destination << ")." << std::endl;
        std::cout << "It will create a negative cycle." << std::endl;
    }

    else
    {
        std::cout << "To get from (" << source << ") to (" << destination << ") you must take this path (READ FROM RIGHT TO LEFT):" << std::endl;
        std::cout << "---------------------------------------------------------------------------" << std::endl;

        int current = destination;
        while (current != source && (path.distance[current] != INT32_MAX && path.distance[current] != INT32_MIN) )
        {
            std::cout << "("<< current << ")<-";
            current = path.actual_path[current];
        }
        std::cout << "(" << source << ") \t COST: " << path.distance[destination] << std::endl;
        std::cout << std::endl;
    }
}


template void findPathAB<GraphArray>(GraphArray * graph, int source, int destination);

template void findPathAB<GraphList>(GraphList * graph, int source, int destination);