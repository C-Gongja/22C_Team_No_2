// Written by: Remy Dinh
//
// Stack class created to implement an undo-delete stack
// for records erased from the country database.
//
// The stack will hold the history of the session's
// deleted records, but will be wiped by using the function
// clear() if the state of the database is written to a file.
//

#ifndef STACK_H
#define STACK_H

#include "ListNode.h"

template <typename ItemType>
class Stack
{
private:
    ListNode<ItemType> *top;
    unsigned            count;

public:
    Stack();
    ~Stack();

    // Accessors
    bool       isEmpty  () const { return count == 0; }
    ItemType   peek     () const { return top->getItem(); }
    unsigned   getCount () const { return count; }

    ListNode<ItemType> *pop      ();
    void                push     (ListNode<ItemType> *inputDataPtr);
    bool                clear    ();
};

template <typename ItemType>
Stack<ItemType>::Stack()
{
    top   = nullptr;
    count = 0u;
}

// Dynamic memory needs to be cleaned up when all is said and done.
// Continually pops nodes off of the stack and deletes them unti
// it's empty.
template <typename ItemType>
Stack<ItemType>::~Stack()
{
    ListNode<ItemType> *durak;
    while (top != nullptr)
    {
        durak = pop();
        delete durak;
    }

}

template <typename ItemType>
bool Stack<ItemType>::clear()
{
    if (isEmpty())
        return false;

    ListNode<ItemType> *durak;
    while (top != nullptr)
    {
        durak = pop();
        delete durak;
        count--;
    }
    return true;
}

template <typename ItemType>
ListNode<ItemType> *Stack<ItemType>::pop()
{
    if (isEmpty())
        return nullptr;

    ListNode<ItemType> *holder = top;
    top = top->getNext();
    count--;

    return holder;
}

template <typename ItemType>
void Stack<ItemType>::push(ListNode<ItemType> *input)
{
    ListNode<ItemType> *newNode = input;
    newNode->setNext(top);
    top = newNode;
    count++;
}

#endif
