#ifndef PROJEKT2_GRAFY_GRAPHLIST_HH
#define PROJEKT2_GRAFY_GRAPHLIST_HH

#include "noe.hh"

// Class to represent weighted digraph using adjacency list.
class GraphList
{
    int nodes_amount, edges_amount;
    Node **head;    // An array of pointers to Node to represent
                    // adjacency list

    Node * getAdjListNode(int val, int weight, Node * head); // Function to allocate new node of Adjacency List

public:

    // constructor
    GraphList(std::unique_ptr<Edge[]> & edges, int edges_amount, int nodes_amount);
    // destructor
    ~GraphList();

    void showAdjNodes(int i);
    void showGraph();
    int getNodesAmount() {return nodes_amount;}
    int getEdgesAmount() {return edges_amount;}
    Node * getHead(int i) {return head[i];}

};

#endif //PROJEKT2_GRAFY_GRAPHLIST_HH
