#ifndef PROJEKT2_GRAFY_MYLIST_HH
#define PROJEKT2_GRAFY_MYLIST_HH

#include "noe.hh"

class MyList
{
    Node *head, *tail;

public:

    MyList();

    ~MyList();

    void addNode(int val);
    void deleteNode();
    void display();
};


#endif //PROJEKT2_GRAFY_MYLIST_HH
