#ifndef PROJEKT2_GRAFY_BELLMANFORD_HH
#define PROJEKT2_GRAFY_BELLMANFORD_HH

#include "GraphList.hh"
#include "GraphArray.hh"

Path BellmanFord(GraphList * graph, int source, bool test);
Path BellmanFord(GraphArray * graph, int source, bool test);
void showResults(Path * path, int source, int nodes_amount);

template <typename GraphType>
void findPathAB(GraphType * graph, int source, int destination);

#endif //PROJEKT2_GRAFY_BELLMANFORD_HH
