#include "../inc/GraphArray.hh"

int ** GraphArray::countPairs(std::unique_ptr<Edge[]> & edges)
{
    int ** pairs_arr = new int*[nodes_amount];
    for (int i = 0; i < nodes_amount; i++)
      pairs_arr[i] = new int[nodes_amount];

    for (int i = 0; i < nodes_amount; i++)
      for (int j = 0; j < nodes_amount; j++)
        pairs_arr[i][j] = 1;

    int src, dest, counter;

    for (int i = 0; i < edges_amount; i++)
    {
        src = edges[i].source;
        dest = edges[i].destination;
        counter = 0;

        for (int j = 0; j < edges_amount; j++)
            if ( src == edges[j].source && dest == edges[j].destination)
              counter++;

      pairs_arr[src][dest] = counter;
    }

    return pairs_arr;
}

GraphArray::GraphArray(std::unique_ptr<Edge[]> & edges, int edges_amount, int nodes_amount)
{
    this->nodes_amount = nodes_amount;
    this->edges_amount = edges_amount;

    int ** pairs_amount = countPairs(edges);

    adj_matrix = new int**[nodes_amount];
    for (int i = 0; i < nodes_amount; i++)
        adj_matrix[i] = new int*[nodes_amount];

    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            adj_matrix[i][j] = new int[pairs_amount[i][j]]


    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            adj_matrix[i][j] = 0;

    for (int i = 0; i < edges_amount; i++)
        adj_matrix[edges[i].source][edges[i].destination] = edges[i].weight;

    delete [] pairs_amount;
}


GraphArray::~GraphArray()
{
    for (int i = 0; i < nodes_amount; i++)
        delete [] adj_matrix[i];

    delete [] adj_matrix;
}

void GraphArray::showAdjMatrix()
{
    std::cout << std::endl;
    std::cout << "ADJACENCY ARRAY:" << std::endl;
    for (int i = 0; i < nodes_amount; i++)
    {
        std::cout << "  ";
        for (int j = 0; j < nodes_amount; j++)
        {
            std::cout << adj_matrix[j][i];
            std::cout << ", ";
        }
        std::cout << std::endl;
    }
}

void GraphArray::showAdjNodes(int i)
{
    for (int j = 0; j < nodes_amount; j++)
        if (adj_matrix[i][j] != 0)
            std::cout << "(" << i << " -> " << j << " | " << adj_matrix[i][j] << ") ";
    std::cout << std::endl;
}


void GraphArray::showGraph()
{
    std::cout << std::endl;
    std::cout << "ARRAY:" << std::endl;
    for (int i = 0; i < nodes_amount; i++)
        this->showAdjNodes(i);
    std::cout << std::endl;
}
