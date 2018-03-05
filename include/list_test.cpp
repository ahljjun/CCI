#include "linked_list.h"
#include <algorithm>
#include <numeric>
#include <iostream>

template <class T>
void print(const List<T>& x)
{
	std::copy(x.begin(), x.end(), std::ostream_iterator<T>(std::cout, " "));
        std::cout<<std::endl;
}

void list_sum(const List<int>& list1, const List<int>& list2, List<int>& result)
{
    //suppose in reverse order, the head of list store the least value
    int carry = 0; 
    int sum  = 0;
    int ret = 0;
    List<int>::const_iterator it1 = list1.begin();
    List<int>::const_iterator it2 = list2.begin();

    while( it1 != list1.end() && it2 != list2.end() ) 
    {
        sum =  carry + *it1 + *it2;
        ret = sum % 10;
        carry = sum / 10;
        result.push_front(ret);
        
        it1++;
        it2++;
    }
   
    if ( it1 == list1.end() && it2 == list2.end() && carry )
	    result.push_front(carry);
    else if ( it1 == list1.end() )
    {
        //continue add list2
        while( it2 != list2.end() ) 
        {
           result.push_front(*it2 + carry);
           carry = 0; 
           it2++;
        }
    }
    else if ( it2 == list2.end() )
    {
        //continue add list2
        while( it1 != list1.end() ) 
        {
           result.push_front(*it1 + carry);
           carry = 0; 
           it1++;
        }
    }

    result.reverse();
    return;
}

int main()
{
	List<int> ll;
	for(int i=1; i<=9; i++)
		ll.push_front(i);

	print(ll);

    List<int>::iterator it = std::find(ll.begin(), ll.end(), 9);
    ll.insert_after(it, 11);

    std::cout<<"The List is "<<std::endl;
    print(ll);

    it = std::find(ll.begin(), ll.end(), 1);
    ll.insert_after(it, 20);

    std::cout<<"The List is "<<std::endl;
    print(ll);

    int sum = std::accumulate(ll.begin(), ll.end(), 0);
    std::cout<<"sum "<<sum<<std::endl;

    std::cout<<"Copying ..."<< std::endl;
    List<int> y(ll);

    print(y);
    std::cout<<"Done with copy"<<std::endl;

    List<int>::const_iterator cit;
    std::cout<<"** ";
    for(cit = y.begin(); cit != y.end(); cit++)
        std::cout<< *cit <<" ";

    std::cout<<std::endl;

    it = std::find(y.begin(), y.end(), 9);
    y.insert_after(it, 5);
    y.insert_after(it, 5);
    y.insert_after(it, 6);
    y.insert_after(it, 5);
    y.insert_after(it, 8);
    std::cout<<"Before unique"<<std::endl;
	print(y);
    std::cout<<"after unique"<<std::endl;
    y.unique();
	print(y);

	List<int> sameList;
	for(int i=1; i<=9; i++)
		sameList.push_front(20);

    std::cout<<"unique all the same data"<<std::endl;
    sameList.unique();
    print(sameList);


    std::cout<<"find kth element"<<std::endl;
    it = y.r_nth(5);
    std::cout<< ": "<< *it << std::endl;
    std::cout<<"remove element"<<std::endl;
    y.remove(it);
    print(y);

    std::cout<<"sorted_by value 5"<<std::endl;
    y.sort_by_value(5);
    print(y);
    std::cout<<"sorted_by value 6"<<std::endl;
    y.sort_by_value(6);
    print(y);

    std::cout<<"sorted_by value 50"<<std::endl;
    y.sort_by_value(50);
    print(y);
    std::cout<<"sorted_by value 50 finish"<<std::endl;

    std::cout<<"============= test for sum function =============="<<std::endl;
    List<int> L2 ;
    L2.push_front(7); //9 -> 8 -> 7
    L2.push_front(8);
    L2.push_front(9);
  
    List<int> L4 ;
    L4.push_front(8); //9 -> 9 -> 8
    L4.push_front(9);
    L4.push_front(9);


    List<int> L5; // should be 8 -> 8 -> 6 -> 1
    list_sum(L2, L4, L5);
    print(L5);

    List<int> L6; 
    List<int> L7; 
    list_sum(L2, L6, L7);
    print(L7);
}
