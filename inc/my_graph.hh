#ifndef PROJEKT2_GRAFY_MY_GRAPH_HH
#define PROJEKT2_GRAFY_MY_GRAPH_HH

#include <iostream>

using namespace std;

struct Node
{
    int value, cost;
    Node * next;
};

struct Edge
{
    int source, destination, weight;
};

class Graph
{
    Node * getAdjListNode(int val, int weight, Node * head)
    {
        Node * new_node = new Node;
        new_node->value = val;
        new_node->cost = weight;
        new_node->next = head;

        return new_node;
    }

    int nodes_amount;

public:

    Node **head;

    // constructor
    Graph(Edge edges[], int n, int N);

    // destructor
    ~Graph();


};

void show_list(Node * ptr, int i);


#endif //PROJEKT2_GRAFY_MY_GRAPH_HH
