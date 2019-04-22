#ifndef PROJEKT2_GRAFY_HELPER_FUNC_HH
#define PROJEKT2_GRAFY_HELPER_FUNC_HH

#include <random>       //  random_device
#include <algorithm>    //  std::random_shuffle
#include <ctime>        //  std::time
#include <cstdlib>      //  std::rand, std::srand
#include "../inc/noe.hh"

int * getRandNodes(int n);

Edge * getRandEdges(int nodes[], int edges_amount, int nodes_amount);

#endif //PROJEKT2_GRAFY_HELPER_FUNC_HH
