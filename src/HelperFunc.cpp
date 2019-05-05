#include "../inc/HelperFunc.hh"

//  Simple random number generator
int myRandom (int i) {return std::rand()%i;}


//  Creates an array of given size and fills it with values
//  that correspond to it's indexes, then shuffles the array randomly
std::unique_ptr<int[]> getRandNodes(int nodes_amount)
{
    std::unique_ptr<int[]> rand_nodes(new int[nodes_amount]);

    for (int i = 0; i < nodes_amount; i++)
        rand_nodes[i] = i;

    std::random_shuffle(&rand_nodes[0], &rand_nodes[nodes_amount],myRandom);

    return rand_nodes;
}


//  Creates an array of random edges and then returns it.
std::unique_ptr<Edge[]> getRandEdges(std::unique_ptr<int[]> & nodes, int edges_amount, int nodes_amount, float density)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> distribution(-3, nodes_amount);

    std::unique_ptr<Edge[]> rand_edges(new Edge[edges_amount]);

    if (density == 1)   // If the density is 1, this means the graph is complete,
    {                   // so we have to generate edges properly.
        int counter = 0;
        while (counter < edges_amount)
        {
            for (int i = 0; i < nodes_amount; i++)
            {
                for (int j = 0; j < nodes_amount; j++)
                {
                    if ( i == j)
                        continue;

                    rand_edges[counter].source = i;         //  For node (i) create a connection
                    rand_edges[counter].destination = j;    //  to the every other node (j).
                    do{
                        rand_edges[counter].weight = distribution(mt);  //  Generate a random weight until it's not 0.
                    }while(rand_edges[counter].weight == 0);

                    counter++;
                }
            }
        }
    }
    else
    {
        for (int i = 0; i < edges_amount; i++)
        {
            rand_edges[i].source = nodes[rand() % nodes_amount];    //  Get random source
            do{                                                             //  Generate random destination, until
                rand_edges[i].destination = nodes[rand() % nodes_amount];   //  it's not the same as source
            }while(rand_edges[i].destination == rand_edges[i].source);      // to avoid creating loops.
            do{
                rand_edges[i].weight = distribution(mt);    //  Generate a random weight until it's not 0.
            }while(rand_edges[i].weight == 0);
        }
    }

    return rand_edges;
}


//  Utility function to generate a random graph and then finds the shortest path using BellmanFord algorithm.
//  It's main purpose is to measure the time it takes to find that path (efficiency test).
template <typename GraphType>
double startPathFinding(int nodes_amount, int edges_amount, float density)
{
    std::unique_ptr<int[]> values_of_nodes = getRandNodes(nodes_amount);
    std::unique_ptr<Edge[]> edges = getRandEdges(values_of_nodes, edges_amount, nodes_amount, density);

    GraphType graph(edges, edges_amount, nodes_amount); // Initialize graph with random edges.

    //graph.showGraph();

    int source = rand() % nodes_amount; //  Generate random starting node.

    auto clock_start = std::chrono::high_resolution_clock::now();   // Start clock
    BellmanFord(&graph,source, true);
    auto clock_stop = std::chrono::high_resolution_clock::now();    // Stop clock

    return std::chrono::duration<double, std::milli>(clock_stop - clock_start).count(); // return time
}

//  Utility function to perform efficiency test for different amounts of nodes and density,
//  for two different graph representation.
void startTest()
{
    std::srand (unsigned ( std::time(0) ) );
    double time[100];
    std::string name = "results.csv";

    //  Array storing pointers to functions performing efficiency test
    double (*pf[2])(int, int, float) = { startPathFinding<GraphList>, startPathFinding<GraphArray>};
    for (auto & find_path : pf)     // For each function
    {
        if ( find_path == &startPathFinding<GraphList>)
        {
            name = "list_results.csv";
            std::cout << std::endl;
            std::cout << "ADJACENCY LIST" << std::endl;
        }
        else if ( find_path == &startPathFinding<GraphArray>)
        {
            name = "matrix_results.csv";
            std::cout << std::endl;
            std::cout << "ADJACENCY MATRIX" << std::endl;

        }

        int NODES_AMOUNT[] = {10, 25, 50, 100, 250};
        for (int V: NODES_AMOUNT)   //  For each amount of nodes
        {
            std::cout << std::endl;
            std:: cout << "Testing for graph with" << V << " nodes" << std::endl;
            float DENSITY[] = {0.25, 0.5, 0.75, 1};
            for (float D: DENSITY)  //  For each density
            {
                //  From equation
                // DENSITY = EDGES / (NODES * (NODES - 1))
                int EDGES_AMOUNT = V*(V-1) * D;

                std::cout << std::endl;
                std:: cout <<  D << " density" << std::endl;

                for (int i = 0; i < 100; i++)   // perform efficiency test 100 times.
                {
                    time[i] = (*find_path)(V, EDGES_AMOUNT, D);

                    std::cout << "\b\b\b\b";
                    std::cout << i+1 << "%" << std::flush;  //  Progress visualization.
                }

                std::cout << std::endl;
                timeToFile(name, time, V, D);   // Save time to the file.
            }
        }
        markAsFull(name);     //  Mark the file as full.
    }
}


void loadFromFile()
{
    std::string name;
    int source = 0;

    std::cout << std::endl;
    std::cout << "Type in the name of the file containing graph data (file must be in this directory):" << std::endl;
    std::cout << "Name:";
    std::cin >> name;

    std::size_t found = name.find(".txt");
    if (found == std::string::npos)
    {
        std::cerr << "Files must be of .txt extension" << std::endl;
        return;
    }

    GraphList graph = createGraphFromFile<GraphList>(name, &source);
    Path path = BellmanFord(&graph, source, false);

    pathToFile(&path, name, source, graph.getNodesAmount());

    std::cout << "Saved results to " << "results_"+name << std::endl;
    std::cout << std::endl;
}


// Function that sums all of the arrays elements.
double sum_array(double arr[], int size)
{
    double sum = 0;

    for (int i = 0; i < size; i++)
        sum += arr[i];

    return sum;
}



template double startPathFinding<GraphList>(int nodes_amount, int edges_amount, float density);

template double startPathFinding<GraphArray>(int nodes_amount, int edges_amount, float density);

