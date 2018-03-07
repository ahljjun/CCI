#include "doubly_list.h"
#include <iostream>
#include <algorithm>
#include <list>

template <class T>
void print(DList<T>& x)
{
	std::copy(x.begin(), x.end(), std::ostream_iterator<T>(std::cout, " "));
        std::cout<<std::endl;
}

void push_test();
void pop_test();
void remove_test();

int main()
{
	push_test();
	pop_test();
	remove_test();

	DList<std::string> stringList;
	std::string a("hello");
	stringList.push_back(a);
	stringList.push_back(std::string("world"));
	stringList.push_back(std::string("STL"));

	DList<std::string>::iterator itString = std::find(stringList.begin(), stringList.end(), std::string("world"));
	stringList.erase(itString);
	print(stringList);
}

void push_test()
{
	DList<int> ll;
    ll.push_front(1);
	ll.push_front(2);
	ll.push_front(3);
	ll.push_back(4);
	ll.push_back(5);
	ll.push_back(6);
	print(ll);	
}

void pop_test()
{
	DList<int> ll;
    ll.push_front(1);
	ll.push_front(2);
	ll.push_front(3);
	ll.push_back(4);
	ll.push_back(5);
	ll.push_back(6);
	std::cout<<"print the list before pop"<<std::endl;
	print(ll);
	ll.pop_front();
	ll.pop_front();
	ll.pop_back();
	std::cout<<"print the list after pop"<<std::endl;
	print(ll);	
}


void remove_test()
{
	DList<int> ll;
    ll.push_front(1);
	ll.push_front(2);
	ll.push_front(3);
	ll.push_back(4);
	ll.push_back(5);
	ll.push_back(6);

	ll.remove(3);
	ll.remove(5);
	std::cout<<"print the list after remove"<<std::endl;
	print(ll);
}
