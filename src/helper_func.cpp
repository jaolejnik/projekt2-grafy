#include "../inc/helper_func.hh"

int myRandom (int i) {return std::rand()%i;}

int * getRandNodes(int nodes_amount)
{
    int * arr = new int[nodes_amount];

    for (int i = 0; i < nodes_amount; i++)
      arr[i] = i;

    std::random_shuffle(&arr[0], &arr[nodes_amount],myRandom);

    return arr;
}


Edge * getRandEdges(int nodes[], int edges_amount, int nodes_amount)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(-edges_amount, edges_amount);

    Edge * edges = new Edge[edges_amount];

    for (int i = 0; i < edges_amount; i++)
    {
        edges[i].source = nodes[rand() % nodes_amount];
        edges[i].destination = nodes[rand() % nodes_amount];
        do{
          edges[i].weight = distribution(mt);
        }while(edges[i].weight == 0);

    }

    return edges;
}
