#include "../inc/helper_func.hh"
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
    //cout << values_of_nodes[0] << endl;

    std::unique_ptr<Edge[]> edges = getRandEdges(values_of_nodes, EDGES_AMOUNT, NODES_AMOUNT[0]);

    GraphList graphL(edges, EDGES_AMOUNT, NODES_AMOUNT[0]);
    GraphArray graphA(edges, EDGES_AMOUNT, NODES_AMOUNT[0]);

    graphL.showGraph();
    graphA.showGraph();
    //graphA.showAdjMatrix();

    BellmanFord(&graphL,0);
    return 0;
}
