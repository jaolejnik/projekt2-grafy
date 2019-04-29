#include "../inc/HelperFunc.hh"
#include "../inc/GraphList.hh"
#include "../inc/GraphArray.hh"
#include "../inc/BellmanFord.hh"

using namespace std;

int main()
{
    int NODES_AMOUNT[] = {10, 50, 100, 500, 1000};
    float DENSITY[] = {0.25, 0.5, 0.75, 1};
    int EDGES_AMOUNT = NODES_AMOUNT[0]*(NODES_AMOUNT[0]-1) * DENSITY[0];
    //  From equation
    // DENSITY = EDGES / (NODES * (NODES - 1))

    std::srand (unsigned ( std::time(0) ) );

    std::unique_ptr<int[]> values_of_nodes = getRandNodes(NODES_AMOUNT[0]);

    std::unique_ptr<Edge[]> edges = getRandEdges(values_of_nodes, EDGES_AMOUNT, NODES_AMOUNT[0]);

    GraphList graphL(edges, EDGES_AMOUNT, NODES_AMOUNT[0]);
    GraphArray graphA(edges, EDGES_AMOUNT, NODES_AMOUNT[0]);

    graphL.showGraph();
    graphA.showGraph();

    BellmanFord(&graphL,0);
    BellmanFord(&graphA,0);
    return 0;
}
/*
   // add edge 0-1 (or A-B in above figure)
   edge[0].source = 0;
   edge[0].destination = 1;
   edge[0].weight = -1;

   // add edge 0-2 (or A-C in above figure)
   edge[1].source = 0;
   edge[1].destination = 2;
   edge[1].weight = 4;

   // add edge 1-2 (or B-C in above figure)
   edge[2].source = 1;
   edge[2].destination = 2;
   edge[2].weight = 3;

   // add edge 1-3 (or B-D in above figure)
   edge[3].source = 1;
   edge[3].destination = 3;
   edge[3].weight = 2;

   // add edge 1-4 (or A-E in above figure)
   edge[4].source = 1;
   edge[4].destination = 4;
   edge[4].weight = 2;

   // add edge 3-2 (or D-C in above figure)
   edge[5].source = 3;
   edge[5].destination = 2;
   edge[5].weight = 5;

   // add edge 3-1 (or D-B in above figure)
   edge[6].source = 3;
   edge[6].destination = 1;
   edge[6].weight = 1;

   // add edge 4-3 (or E-D in above figure)
   edge[7].source = 4;
   edge[7].destination = 3;
   edge[7].weight = -3;


   GraphList graphL(edge, 8, 5);
    */
