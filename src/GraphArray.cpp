#include "../inc/GraphArray.hh"

//  Function that counts repeating paths(multiple paths from A to B),
//  for sake of allocating just enough space in adjacency array and saves
//  it as an matrix and returns it.
int ** GraphArray::countPairs(std::unique_ptr<Edge[]> & edges)
{
    int ** pairs_arr = new int*[nodes_amount];
    for (int i = 0; i < nodes_amount; i++)
    {
        pairs_arr[i] = new int[nodes_amount];
    }

    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            pairs_arr[i][j] = 1;

    int src, dest, counter;

    //  Fill the matrix with the amounts of
    //  the repeating pairs
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

// Consrtuctor
GraphArray::GraphArray(std::unique_ptr<Edge[]> & edges, int edges_amount, int nodes_amount)
{
    this->nodes_amount = nodes_amount;
    this->edges_amount = edges_amount;



    //  Get amount of the repeating pairs
    int ** pairs_amount = countPairs(edges);

    //  Allocate adjacency matrix
    adj_matrix = new int**[nodes_amount];
    for (int i = 0; i < nodes_amount; i++)
        adj_matrix[i] = new int*[nodes_amount];

    //  Create array for the repeating pairs that is
    //  one int bigger, to mark that last element as the end
    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
        {
            //std::cout << "SIZE OF ADJ adj_matrix["<<i<<"]["<<j<<"][k]" << pairs_amount[i][j] + 1 << std::endl;
            adj_matrix[i][j] = new int[pairs_amount[i][j] + 1];
        }


    //  Fill it with 0's
    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            for (int k = 0; k <= pairs_amount[i][j]; k++)
                adj_matrix[i][j][k] = 0;

    //  Fill pairs_amount matrix with 0's to use it as a pair counter
    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            pairs_amount[i][j] = 0;

    //  Fill adjacency matrix with weights of edges.
    for (int i = 0; i < edges_amount; i++)
    {
        int src = edges[i].source;
        int dest = edges[i].destination;
        int j = pairs_amount[src][dest];
        adj_matrix[src][dest][j] = edges[i].weight;
        pairs_amount[src][dest]++;
    }

    for (int i = 0; i < nodes_amount; i++)
        delete [] pairs_amount[i];

    delete [] pairs_amount;

}

// destructor
GraphArray::~GraphArray()
{
    for (int i = 0; i < nodes_amount; i++)
        for (int j = 0; j < nodes_amount; j++)
            delete [] adj_matrix[i][j];

    for (int i = 0; i < nodes_amount; i++)
        delete [] adj_matrix[i];

    delete [] adj_matrix;
}

void GraphArray::showAdjNodes(int i)
{
    for (int j = 0; j < nodes_amount; j++)
    {
        int k = 0;
        while (adj_matrix[i][j][k] != 0)
        {
            std::cout << "(" << i << " -> " << j << " | " << adj_matrix[i][j][k] << ") ";
            k++;
        }
    }

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
