#ifndef PROJEKT2_GRAFY_GRAPHARRAY_HH
#define PROJEKT2_GRAFY_GRAPHARRAY_HH

#include "noe.hh"

class GraphArray
{
    int countPairs(std::unique_ptr<Edge[]> & edges);
    int *** adj_matrix;
    int nodes_amount, edges_amount;

public:
    GraphArray(std::unique_ptr<Edge[]> & edges, int edges_amount, int nodes_amount);
    ~GraphArray();

    void showAdjMatrix();
    void showAdjNodes(int i);
    void showGraph();
    int getNodesAmount() {return nodes_amount;}
    int getEdgesAmount() {return edges_amount;}
};

#endif //PROJEKT2_GRAFY_GRAPHARRAY_HH
