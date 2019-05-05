#ifndef PROJEKT2_GRAFY_HELPERFUNC_HH
#define PROJEKT2_GRAFY_HELPERFUNC_HH

#include <random>       //  random_device
#include <algorithm>    //  std::random_shuffle
#include <ctime>        //  std::time
#include <cstdlib>      //  std::rand, std::srand, exit()
#include <chrono>       //  chrono clock
#include <string>
#include "GraphList.hh"
#include "GraphArray.hh"
#include "BellmanFord.hh"
#include "fileManagment.hh"

std::unique_ptr<int[]> getRandNodes(int n);

//  unique_ptr passed by reference, otherwise passed value would become null
std::unique_ptr<Edge[]> getRandEdges(std::unique_ptr<int[]> & nodes, int edges_amount, int nodes_amount, float density);

template <typename GraphType>
double startPathFinding(int nodes_amount, int edges_amount, float density);

void startTest();
void loadFromFile();

template <typename GraphType>
GraphType createGraphFromFile(std::string name, int * start);

double sum_array(double *arr, int size);

#endif //PROJEKT2_GRAFY_HELPERFUNC_HH
