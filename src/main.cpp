#include "../inc/helper_func.hh"
#include "../inc/GraphList.hh"
#include "../inc/GraphArray.hh"


int main()
{
  int NODES_AMOUNT = 7;
  float DENSITY = 0.25;
  int EDGES_AMOUNT = NODES_AMOUNT*(NODES_AMOUNT-1) * DENSITY;
  //  From equation
  // DENSITY = EDGES / (NODES * (NODES - 1))

  std::srand ( unsigned ( std::time(0) ) );

  int * values_of_nodes = getRandNodes(NODES_AMOUNT);
  Edge * edges = getRandEdges(values_of_nodes, EDGES_AMOUNT, NODES_AMOUNT);

  GraphList graphL(edges, EDGES_AMOUNT, NODES_AMOUNT);
  GraphArray graphA(edges, EDGES_AMOUNT, NODES_AMOUNT);

  graphL.showGraph();
  graphA.showGraph();
  graphA.showAdjMatrix();

  return 0;
}
