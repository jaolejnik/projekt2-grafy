#ifndef PROJEKT2_GRAFY_FILEMANAGMENT_HH
#define PROJEKT2_GRAFY_FILEMANAGMENT_HH

#include <iostream>
#include <fstream>
#include <string>
#include "HelperFunc.hh"

bool fileExist(std::string name);
void changeFileName(std::string *name);
bool timeToFile(std::string name, double *time, int nodes_amount, float density);
bool markAsFull(std::string name);
bool isFull(std::string name);

template <typename GraphType>
GraphType createGraphFromFile(std::string name, int * start);

bool pathToFile(Path * path, std::string name, int source, int nodes_amount);
#endif //PROJEKT2_GRAFY_FILEMANAGMENT_HH
