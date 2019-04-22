#ifndef PROJEKT2_GRAFY_GRAPHARRAY_HH
#define PROJEKT2_GRAFY_GRAPHARRAY_HH

#include <iostream>
#include "../inc/noe.hh"

class GraphArray
{
  int ** adj_matrix;

  int nodes_amount, edges_amount;

public:
  GraphArray(Edge edges[], int edges_amount, int nodes_amount);
  ~GraphArray();

  void showAdjMatrix();
  void showAdjNodes(int i);
  void showGraph();
};

#endif //PROJEKT2_GRAFY_MY_GRAPH_HH
