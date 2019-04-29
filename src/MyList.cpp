//
// Created by Kuba on 28.04.2019.
//

#include "../inc/MyList.hh"

MyList::MyList()
{
    head = nullptr;
    tail = nullptr;
}

MyList::~MyList()
{
    while (head != nullptr && tail != nullptr)
    {
        Node * temp = new Node;
        temp = head;
        head = head->next;
        delete temp;
    }
}

void MyList::addNode(int val) {
    Node * tmp = new Node;
    tmp->value = val;
    tmp->next = nullptr;

    if (head == nullptr)
    {
        head = tmp;
        tail = tmp;
        tmp = nullptr;
    }
    else
    {
        tail->next = tmp;
        tail = tmp;
    }
}


void MyList::deleteNode()
{
    Node * current = new Node;
    Node * previous = new Node;
    current = head;

    while (current->next != nullptr)
    {
        previous = current;
        current = current->next;
    }

    tail = previous;
    previous->next = nullptr;
    delete current;
}

void MyList::display()
{
    Node * tmp = new Node;
    tmp = head;

    while (tmp != nullptr)
    {
        std::cout << "("<< tmp->value <<") <- ";
        tmp = tmp->next;
    }
}
