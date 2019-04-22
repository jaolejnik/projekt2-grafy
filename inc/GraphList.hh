#ifndef PROJEKT2_GRAFY_MY_GRAPH_HH
#define PROJEKT2_GRAFY_MY_GRAPH_HH

#include <iostream>
#include "../inc/noe.hh"

class GraphList
{
    Node * getAdjListNode(int val, int weight, Node * head);

    bool is_list;
    int nodes_amount, edges_amount;

public:

    Node **head;

    // constructor
    GraphList(Edge edges[], int edges_amount, int nodes_amount);

    // destructor
    ~GraphList();

    void showAdjNodes(int i);
    void showGraph();
};

#endif //PROJEKT2_GRAFY_MY_GRAPH_HH
