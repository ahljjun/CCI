#include "linked_list.h"
#include <algorithm>
#include <numeric>
#include <iostream>

template <class T>
void print(const List<T>& x)
{
	std::copy(x.begin(), x.end(), std::ostream_iterator<T>(std::cout, "\n"));
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
}
