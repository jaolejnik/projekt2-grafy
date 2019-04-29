#ifndef PROJEKT2_GRAFY_BELLMANFORD_HH
#define PROJEKT2_GRAFY_BELLMANFORD_HH

#include "GraphList.hh"
#include "GraphArray.hh"
#include "MyList.hh"

struct Path
{
    int cost;
    MyList visited_nodes;
};

void showResults(std::unique_ptr<int[]> &distance, int source, int n);
std::unique_ptr<int[]> BellmanFord(GraphList * graph, int source);
std::unique_ptr<int[]> BellmanFord(GraphArray * graph, int source);

#endif //PROJEKT2_GRAFY_BELLMANFORD_HH
