#include "Stack.h"
#include "doubly_list.h"
#include <vector>
#include <iostream>
#include <deque>
#include <cassert>

int main()
{
    Stack<int, DList<int> > testStack;
    Stack<int, std::deque<int> > cmpStack;

    for ( int i = 1; i < 10 ; i++ )
    {
        testStack.push(i);
        cmpStack.push(i);
    }


    for ( int i = 1; i < 10 ; i++ )
    {
        int value = testStack.top() ;
        assert(value == cmpStack.top());
        std::cout<< "value: "<<value<<std::endl;
        testStack.pop(); 
        cmpStack.pop(); 
    }

    return 0;
}

