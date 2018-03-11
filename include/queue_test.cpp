#include "Queue.h"
#include "doubly_list.h"
#include <vector>
#include <iostream>
#include <deque>
#include <cassert>

int main()
{
    Queue<int, DList<int> > testQueue;

    for ( int i = 1; i < 10 ; i++ )
    {
        testQueue.push(i);
    }


    for ( int i = 1; i < 10 ; i++ )
    {
        int value = testQueue.front() ;
        int value1 = testQueue.back() ;
        std::cout<< "front: "<<value<<", back: "<<value1<<std::endl;
        testQueue.pop(); 
    }

    return 0;
}

