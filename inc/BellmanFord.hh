#ifndef PROJEKT2_GRAFY_BELLMANFORD_HH
#define PROJEKT2_GRAFY_BELLMANFORD_HH

#include "GraphList.hh"
#include "GraphArray.hh"

void showResults(int distance[], int source, int n);
void BellmanFord(GraphList * graph, int source);
void BellmanFord(GraphArray * graph, int source);

#endif //PROJEKT2_GRAFY_BELLMANFORD_HH
