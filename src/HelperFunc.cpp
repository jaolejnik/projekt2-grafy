#include "../inc/HelperFunc.hh"

//  Simple random number generator
int myRandom (int i) {return std::rand()%i;}

//  Creates an array of given size and fills it with values
//  that correspond to it's indexes, then shuffles the array randomly
std::unique_ptr<int[]> getRandNodes(int nodes_amount)
{
    std::unique_ptr<int[]> rand_nodes(new int[nodes_amount]);

    for (int i = 0; i < nodes_amount; i++)
        rand_nodes[i] = i;

    std::random_shuffle(&rand_nodes[0], &rand_nodes[nodes_amount],myRandom);

    return rand_nodes;
}

//  Creates an array of random edges and then returns it
std::unique_ptr<Edge[]> getRandEdges(std::unique_ptr<int[]> & nodes, int edges_amount, int nodes_amount)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(-3, nodes_amount);

    std::unique_ptr<Edge[]> rand_edges(new Edge[edges_amount]);

    for (int i = 0; i < edges_amount; i++)
    {
        rand_edges[i].source = nodes[rand() % nodes_amount];
        do{
            rand_edges[i].destination = nodes[rand() % nodes_amount];
        }while(rand_edges[i].destination == rand_edges[i].source);
        do{
            rand_edges[i].weight = distribution(mt);
        }while(rand_edges[i].weight == 0);
    }

    return rand_edges;
}



double startPathFindingList(int nodes_amount, int edges_amount)
{
    std::unique_ptr<int[]> values_of_nodes = getRandNodes(nodes_amount);
    std::unique_ptr<Edge[]> edges = getRandEdges(values_of_nodes, edges_amount, nodes_amount);

    GraphList graphL(edges, edges_amount, nodes_amount);
    //GraphArray graphA(edges, edges_amount, nodes_amount);

    graphL.showGraph();
    //graphA.showGraph();

    int source = rand() % nodes_amount;
    BellmanFord(&graphL,source);
    //BellmanFord(&graphA,source);
}

double startPathFindingArray(int nodes_amount, int edges_amount)
{
    std::unique_ptr<int[]> values_of_nodes = getRandNodes(nodes_amount);
    std::unique_ptr<Edge[]> edges = getRandEdges(values_of_nodes, edges_amount, nodes_amount);

    GraphArray graphA(edges, edges_amount, nodes_amount);

    graphA.showGraph();

    int source = rand() % nodes_amount;
    BellmanFord(&graphA,source);
}
