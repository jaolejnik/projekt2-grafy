#ifndef PROJEKT2_GRAFY_NOE_HH
#define PROJEKT2_GRAFY_NOE_HH

#include <iostream>
#include <memory>       // std::unique_ptr

//  Structure to represent the node in a list.
struct Node
{
    int value, cost;
    Node * next;
};

//  Structure to represent edges in a graph.
struct Edge
{
    int source, destination, weight;
};

//  Structure to store information about path found by Bellman-Ford Algorithm
struct Path
{
  std::unique_ptr<int[]> distance;
  std::unique_ptr<int[]> actual_path;
};

#endif //PROJEKT2_GRAFY_NOE_HH
