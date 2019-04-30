#ifndef PROJEKT2_GRAFY_NOE_HH
#define PROJEKT2_GRAFY_NOE_HH

#include <iostream>
#include <memory>       // std::unique_ptr

struct Node
{
    int value, cost;
    Node * next;
};


struct Edge
{
    int source, destination, weight;
};

struct Path
{
  std::unique_ptr<int[]> distance;
  std::unique_ptr<int[]> actual_path;
};

#endif //PROJEKT2_GRAFY_NOE_HH
