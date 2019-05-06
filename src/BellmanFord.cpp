#include "../inc/BellmanFord.hh"

//  Finds shortest path in given graph, detects and marks negative cycles.
//  Returns Path, structure that stores distance and path for every node.
Path BellmanFord(GraphList *graph, int source, bool test)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);
    std::unique_ptr<int[]> predecessor(new int[V]);

    for (int i = 0; i < V; i++)     // Set every distance to INF
        distance[i] = INT32_MAX;
    distance[source] = 0;

    // Relax all edges |V| - 1 times. A simple shortest path from
    // src to any other node can have at-most |V| - 1 edges
    for (int i = 1; i <= V-1; i++)
    {
        for(int j = 0; j < V; j++)  //  For every node
        {
            Node * head_ptr = graph->getHead(j);
            while(head_ptr != nullptr)  // Loop until the head is not null
            {
                int src = j;
                int dest = head_ptr->value;
                int weight = head_ptr->cost;

                //  If distance to the source and this weight is smaller that the one stored in the array
                //  and is not equal to INF
                if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                {
                    distance[dest] = distance[src] + weight;    //  save it as the distance to the destination
                    predecessor[dest] = src;                    // and mark the source as the predecessor node
                }                                               // to the destination.

                head_ptr = head_ptr->next;  // Go to the next node adjacent to source(j);
            }
        }
    }

    // Loop responsible for checking whether there are any negative cycles.
    for(int j = 0; j < V; j++)
    {
        Node * head_ptr = graph->getHead(j);
        while(head_ptr != nullptr)
        {
            int src = j;
            int dest = head_ptr->value;
            int weight = head_ptr->cost;

            //  If any distance can be even smaller, then it's negative cycle.
            if (distance[src] != INT32_MAX && distance[src] != INT32_MIN && distance[src] + weight < distance[dest])
                distance[dest] = INT32_MIN; // set the distance to -INF

            head_ptr = head_ptr->next;
        }
    }

    //  Loop responsible for checking if there's a node whose predecessor distance is set to -INF
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

            if (distance[src] == INT32_MIN) //  If yes, then
                distance[dest] = INT32_MIN; //  set the current value to -INF too.

            head_ptr = head_ptr->next;
        }
    }
    //  Above loop is used as protection, when there is a graph, where path to one node (A)
    //  is marked as a negative cycle, but the adjacent nodes to (A) still have normal values.
    //  We have to set them to -INF too, because of the negative cycle we can't get to them.

    Path paths;
    paths.distance = move(distance);
    paths.actual_path = move(predecessor);

    if (!test)  // If it isn't an efficiency test, than display the results.
        showResults(&paths, source, V);

    return paths;
}

//  Finds shortest path in given graph, detects and marks negative cycles.
//  Returns Path, structure that stores distance and path for every node.
Path BellmanFord(GraphMatrix * graph, int source, bool test)
{
    int V = graph->getNodesAmount();
    std::unique_ptr<int[]> distance(new int[V]);
    std::unique_ptr<int[]> predecessor(new int[V]);

    for (int i = 0; i < V; i++)
        distance[i] = INT32_MAX; // Set every distance to INF
    distance[source] = 0;

    int *** adj_mat = graph->getAdjMatrix();

    // Relax all edges |V| - 1 times. A simple shortest path from
    // src to any other node can have at-most |V| - 1 edges
    for (int a = 1; a <= V-1; a++)
    {
        for(int i = 0; i < V; i++)  // For every possible source
        {
            for (int j = 0; j < V; j++) //  and destination pair.
            {
                int k = 0;
                while (adj_mat[i][j][k] != 0)   //  Loop until there's no pair of i and j.
                {
                    int src = i;
                    int dest = j;
                    int weight = adj_mat[i][j][k];

                    //  If distance to the source and this weight is smaller that the one stored in the array
                    //  and is not equal to INF
                    if (distance[src] != INT32_MAX && distance[src] + weight < distance[dest])
                    {
                        distance[dest] = distance[src] + weight;    //  save it as the distance to the destination
                        predecessor[dest] = src;                    // and mark the source as the predecessor node
                    }                                               // to the destination.

                    k++;    // Get to the next pair of i and j;
                }
            }
        }
    }

    // Loop responsible for checking whether there are any negative cycles.
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

                //  If any distance can be even smaller, then it's negative cycle.
                if (distance[src] != INT32_MAX && distance[src] != INT32_MIN && distance[src] + weight < distance[dest])
                    distance[dest] = INT32_MIN; // set the distance to -INF

                k++;
            }
        }
    }

    //  Loop responsible for checking if there's a node whose predecessor distance is set to -INF
    for(int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            int k = 0;
            while (adj_mat[i][j][k] != 0)
            {
                int src = i;
                int dest = j;

                if (dest == source)
                {
                    k++;
                    continue;
                }

                if (distance[src] == INT32_MIN) //  If yes, then
                    distance[dest] = INT32_MIN; //  set the current value to -INF too.

                k++;
            }
        }
    }

    Path paths;
    paths.distance = move(distance);
    paths.actual_path = move(predecessor);

    if (!test)  // If it isn't an efficiency test, than display the results.
        showResults(&paths, source, V);

    return paths;
}

//  Display path and it's cost form source to every other node.
void showResults(Path * path, int source, int nodes_amount)
{
    std::cout << std::endl;
    std::cout << "Node\t\tDistance from (" << source << ")\t\tPath" << std::endl;
    for (int i = 0; i < nodes_amount; i++)
    {
        std::cout << i << "\t\t";
        if (path->distance[i] == INT32_MAX)
            std::cout << "INF (not connected)\t\t\t\t";
        else if (path->distance[i] == INT32_MIN)
            std::cout << "-INF (negative cycle)\t\t\t\t";
        else if (i == source)
            std::cout << "SOURCE\t\t\t\t";
        else
            std::cout << path->distance[i] << "\t\t\t\t";

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


template void findPathAB<GraphMatrix>(GraphMatrix * graph, int source, int destination);

template void findPathAB<GraphList>(GraphList * graph, int source, int destination);