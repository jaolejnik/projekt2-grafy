#ifndef PROJEKT2_GRAFY_GRAPHMATRIX_HH
#define PROJEKT2_GRAFY_GRAPHMATRIX_HH

#include "noe.hh"

// Class to represent weighted digraph using adjacency matrix.
class GraphMatrix
{
    int ** countPairs(std::unique_ptr<Edge[]> & edges); // matrix that store amount of repeating edges
    int *** adj_matrix; // 3D array, to store adjacency matrix of arrays
    int nodes_amount, edges_amount;

public:

    // constructor
    GraphMatrix(std::unique_ptr<Edge[]> & edges, int edges_amount, int nodes_amount);
    //  destructor
    ~GraphMatrix();

    void showAdjNodes(int i);
    void showGraph();
    int getNodesAmount() {return nodes_amount;}
    int getEdgesAmount() {return edges_amount;}
    int *** getAdjMatrix() { return adj_matrix;}
};

#endif //PROJEKT2_GRAFY_GRAPHMATRIX_HH
