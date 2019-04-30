#include "../inc/HelperFunc.hh"


using namespace std;

int main()
{
    std::srand (unsigned ( std::time(0) ) );

    int NODES_AMOUNT[] = {10, 50, 100, 250, 500};
    for (int V: NODES_AMOUNT)
    {
        float DENSITY[] = {0.25};//, 0.5, 0.75, 1};
        for (float D: DENSITY)
        {
            int EDGES_AMOUNT = V*(V-1) * D;
            //  From equation
            // DENSITY = EDGES / (NODES * (NODES - 1))

            startPathFindingArray(V, EDGES_AMOUNT);
            //startPathFindingList(/**/V, EDGES_AMOUNT);
        }
    }


    return 0;
}