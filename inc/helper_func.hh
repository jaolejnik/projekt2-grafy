#ifndef PROJEKT2_GRAFY_HELPER_FUNC_HH
#define PROJEKT2_GRAFY_HELPER_FUNC_HH

#include <random>       //  random_device
#include <algorithm>    //  std::random_shuffle
#include <ctime>        //  std::time
#include <cstdlib>      //  std::rand, std::srand
#include "noe.hh"

std::unique_ptr<int[]> getRandNodes(int n);

//  unique_ptr passed by reference, otherwise that passed value would become null
std::unique_ptr<Edge[]> getRandEdges(std::unique_ptr<int[]> & nodes, int edges_amount, int nodes_amount);

#endif //PROJEKT2_GRAFY_HELPER_FUNC_HH
