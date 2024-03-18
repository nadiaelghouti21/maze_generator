#pragma once
#ifndef STACK_H
#define STACK_H
#include <iostream>
#include <iomanip>
// the following code is taken fro CS 300 lecture slides. 
template <class Object>
class Stack
{
    struct  maze_cell {
        int x;
        int y;
        bool l;
        bool r;
        bool u;
        bool d;
        bool visit;

        maze_cell(int x = 0, int y = 0) :
            x(x), y(y), l(true), r(true), u(true), d(true), visit(false) {};
    };


public:
    Stack();
    Stack(const Stack& rhs);
    ~Stack();

    bool isEmpty() const;
    bool isFull() const;
    void makeEmpty();
    Object pop();
    void push( Object& x);
    Object topAndPop();
    const Object& top() const;


    const Stack& operator=(const Stack& rhs);
private:
    struct ListNode
    {
        Object element;
        ListNode* next;

        ListNode(const Object& theElement, ListNode* n = nullptr)
            : element(theElement), next(n) { }
    };

    ListNode* topOfStack;  // list itself is the stack
};
#endif 


/**
         * Construct the stack.
         */
template <class Object>
Stack<Object>::Stack()
{
    topOfStack = nullptr;
}
/**
         * Test if the stack is logically full.
         * Return false always, in this implementation.
         */
template <class Object>
bool Stack<Object>::isFull() const
{
    return false;
}
/**
       * Test if the stack is logically empty.
       * Return true if empty, false, otherwise.
       */
template <class Object>
bool Stack<Object>::isEmpty() const
{
    return topOfStack == nullptr;
}


/**
         * Get the most recently inserted item in the stack.
         * Return the most recently inserted item in the stack
         * or throw an exception if empty.
         */
template <class Object>
const Object& Stack<Object>::top() const {

    if (isEmpty())
        throw std::runtime_error("Stack underflow"); // You can use a more specific exception type if needed
    return topOfStack->element;
}
/**
       * Get the most recently inserted item in the stack.
       * Return the most recently inserted item in the stack
       * or throw an exception if empty.
       */
template <class Object>
Object Stack<Object>::pop()
{
    if (isEmpty())
        throw std::runtime_error("Stack underflow"); // You can use a more specific exception type if needed
    ListNode* oldTop = topOfStack;
    topOfStack = topOfStack->next;
    return oldTop->element;
}/**
         * Insert x into the stack.
         */
template <class Object>
void Stack<Object>::push(Object& x)
{
    topOfStack = new ListNode(x, topOfStack);
}

/**
       * Return and remove the most recently
       * inserted item from the stack.
       */
template <class Object>
Object Stack<Object>::topAndPop()
{
    Object topItem = top();
    pop();
    return topItem;
}
/**
       * Make the stack logically empty.
       */
template <class Object>
void Stack<Object>::makeEmpty()
{
    while (!isEmpty())
        pop();
}
/**
       * Deep copy.
       */
template <class Object>
const Stack<Object>& Stack<Object>::
operator=(const Stack<Object>& rhs)
{
    if (this != &rhs)
    {
        makeEmpty();
        if (rhs.isEmpty())
            return *this;

        ListNode* rptr = rhs.topOfStack;
        ListNode* ptr = new ListNode(rptr->element);
        topOfStack = ptr;

        for (rptr = rptr->next; rptr != nullptr; rptr = rptr->next)
            ptr = ptr->next = new ListNode(rptr->element);
    }
    return *this;
}
/**
* Copy constructor.
*/
template <class Object>
Stack<Object>::Stack(const Stack<Object>& rhs)
{
    topOfStack = nullptr;
    *this = rhs; // deep copy 
}






/**
       * Destructor.
       */
template <class Object>
Stack<Object>::~Stack()
{
    makeEmpty();
}





