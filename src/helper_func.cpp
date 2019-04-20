//
// Created by Kuba on 20.04.2019.
//

#include "../inc/helper_func.hh"


int * getRandVertices(int n)
{
    int * arr = new int[n];

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> distribution(0,n);

    for (int i = 0; i < n; i++)
        arr[i] = distribution(mt);

    return arr;
}

Edge * getRandEdges(int const vertices[])
{
    int n = sizeof(vertices)/sizeof(vertices[0]);

    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> distribution(n,n+5);
    // TODO
    // TUTAJ SKONCZYLES
    Edge * edges = new Edge[n];

    for (int i = 0; i < n; i++)
    {
        edges[i].source = distribution(mt);
        edges[i].destination = distribution(mt);
        edges[i].weight = distribution(mt);
    }

    return edges;
}

