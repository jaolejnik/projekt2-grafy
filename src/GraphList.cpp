#include "../inc/GraphList.hh"

Node * GraphList::getAdjListNode(int val, int weight, Node * head)
{
  Node * new_node = new Node;
  new_node->value = val;
  new_node->cost = weight;
  new_node->next = head;

  return new_node;
}

GraphList::GraphList(Edge *edges, int edges_amount, int nodes_amount)
{
  head = new Node*[nodes_amount];
  this->nodes_amount = nodes_amount;

  for (int i = 0; i < nodes_amount; i++)
    head[i] = nullptr;

  for (int i = 0; i < edges_amount; i++)
  {
    int source = edges[i].source;
    int destination = edges[i].destination;
    int weight = edges[i].weight;

    Node * new_node = getAdjListNode(destination, weight, head[source]);

    head[source] = new_node;
  }
}


GraphList::~GraphList()
{
  for (int i = 0; i < nodes_amount; i++)
    delete [] head[i];

  delete[] head;
}


void GraphList::showAdjNodes(int i)
{
  Node * head_ptr = this->head[i];
  while (head_ptr != nullptr)
  {
      std::cout << "(" << i << " -> " << head_ptr->value << " | " << head_ptr->cost << ") ";
      head_ptr = head_ptr->next;
  }
  std::cout << std::endl;
}


void GraphList::showGraph()
{
  std::cout << "LIST:" << std::endl;
  for (int i = 0; i < this->nodes_amount; i++)
    this->showAdjNodes(i);
}
