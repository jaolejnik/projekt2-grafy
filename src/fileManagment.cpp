#include <iomanip>
#include "../inc/fileManagment.hh"

// Checks whether the file exists.
bool fileExist(std::string name)
{
    std::ifstream myFile;
    myFile.open(name);
    return myFile.is_open();
}


// Changes the name of the file if file with that name already exists.
void changeFileName(std::string *name)
{
    *name = "new_" + *name;
    if(fileExist(*name))   // If the file with that name still exists
        changeFileName(name);     // call the function again
}


// Saves time of sorting to the  file.
bool timeToFile(std::string name, double *time, int nodes_amount, float density)
{
    std::ofstream myFile(name, std::ios_base::out| std::ios_base::app);    // Open file with option to only add text
    // at the end
    if(isFull(name))       // If it's full
        std::ofstream myFile(name);  // reduce the size and rewrite it

    if(!myFile.is_open())   // If it won't open
    {                       // give the error
        std::cerr << " Error: Opening file to save have failed!" << std::endl;
        return false;
    }

    myFile << std::endl;

    myFile << "Graph with " << nodes_amount << " nodes and density " << density << std::endl;
    myFile << "Average time: ; ";
    myFile << sum_array(time, 100)/100 << ';' << std::endl;     // Saves average time of path-finding.


    myFile.close();

    return true;
}

// Marks the file as full.
bool markAsFull(std::string name)
{
    std::ofstream myFile(name, std::ios_base::out| std::ios_base::app);    // Open file in mode to only add text
                                                                           // at the end
    if(!myFile.is_open())
    {
        std::cerr << " Error: Opening file to mark as full have failed!" << std::endl;
        return false;
    }

    myFile << std::endl;
    myFile << "End of results";

    myFile.close();

    return true;
}

// Checks if the file is full, by checking if the last line of the file is
// std::string "End of results"
bool isFull(std::string name)
{
    std::string temp;
    std::ifstream myFile(name);  // Open file to read only.
    if(!myFile.is_open())   // If it won't open display the error.
    {
        std::cerr << " Error: Opening file to read have failed!" << std::endl;
        return false;
    }

    myFile.seekg(-1,std::ios_base::end);                // go to one spot before the EOF

    bool keepLooping = true;
    while(keepLooping)
    {
        char ch;
        myFile.get(ch);                            // Get current byte's data

        if((int)myFile.tellg() <= 1)
        {             // If the data was at or before the 0th byte
            myFile.seekg(0);                       // The first line is the last line
            keepLooping = false;                // So stop there
        }
        else if(ch == '\n')
        {                   // If the data was a newline
            keepLooping = false;                // Stop at the current position.
        }
        else
        {                                  // If the data was neither a newline nor at the 0 byte
            myFile.seekg(-2,std::ios_base::cur);        // Move to the front of that data, then to the front of the data before it
        }
    }

    getline(myFile, temp);

    return temp == "End of results";
}


//  Creates a graph form the data in the given file and returns it.
template <typename GraphType>
GraphType createGraphFromFile(std::string name, int *source)
{
    std::ifstream myFile(name);
    if( !myFile.is_open() )    // If it won't open display the error.
    {
        std::cerr << "Failed to open " << name << "to create a graph from file."<< std::endl;
        exit(EXIT_FAILURE);
    }

    int nodes_amount, edges_amount, starting_node;

    // Get amounts of edges and nodes and starting node.
    myFile >> edges_amount >> nodes_amount >> starting_node;

    *source = starting_node;

    std::unique_ptr<Edge[]> edges(new Edge[edges_amount]);

    // Initialize edges from the file.
    for (int i = 0; i < edges_amount; i++)
    {
        myFile >> edges[i].source;
        myFile >> edges[i].destination;
        myFile >> edges[i].weight;
    }

    GraphType graph(edges,edges_amount, nodes_amount);

    myFile.close();
    return graph;
}

// Saves path to a file of  "results_"+ given name
bool pathToFile(Path * path, std::string name, int source, int nodes_amount)
{
    std::ofstream myFile("results_"+name);

    if(!myFile.is_open())
    {
        std::cerr << " Error: Opening a file to save the path have failed." << std::endl;
        return false;
    }

    myFile << std::endl;
    myFile << "Node\t\tDistance from (" << source << ")\t\tPath \n";
    myFile << std::endl;

    for (int i = 0; i < nodes_amount; i++)
    {
         myFile << i << "\t\t";
        if (path->distance[i] == INT32_MAX)
             myFile << "INF (not connected)\t\t\t\t";
        else if (path->distance[i] == INT32_MIN)
             myFile << "-INF (negative cycle)\t\t\t\t";
        else if (i == source)
             myFile << "SOURCE\t\t\t\t";
        else
             myFile << path->distance[i] << "\t\t\t\t";

        int current = i;
        while (current != source && (path->distance[current] != INT32_MAX && path->distance[current] != INT32_MIN) )
        {
             myFile << "("<< current << ")<-";
            current = path->actual_path[current];
        }
        if (path->distance[i] != INT32_MAX && path->distance[i] != INT32_MIN)
             myFile << "(" << source << ")";
         myFile << "\n";
    }

    myFile << std::endl;

    myFile.close();

    return true;
}

template GraphList createGraphFromFile<GraphList>(std::string name, int * source);

template GraphMatrix createGraphFromFile<GraphMatrix>(std::string name, int * source);