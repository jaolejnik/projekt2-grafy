#include "../inc/my_graph.hh"
#include "../inc/helper_func.hh"

int main() {
    // array of graph edges as per above diagram.
    Edge * edges = getRandEdges(7);
           /* {
                    // (x, y, w) -> edge from x to y having weight w
                    { 0, 1, 6 }, { 1, 2, 7 }, { 2, 0, 5 }, { 2, 1, 4 },
                    { 3, 2, 10 }, { 4, 5, 1 }, { 5, 4, 3 }
            }; */

    // Number of vertices in the graph
    int N = 6;

    // calculate number of edges
    int n = sizeof(edges)/sizeof(edges[0]);

    // construct graph
    Graph graph(edges, n, N);

    // print adjacency list representation of graph
    for (int i = 0; i < N; i++)
    {
        // print all neighboring vertices of vertex i
        show_list(graph.head[i], i);
    }

    return 0;
}