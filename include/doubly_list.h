#ifndef __D__LIST_H
#define __D__LIST_H

#include "common.h"
#include <iterator>

template<class T>
class DList{

	struct list_node{
		list_node(const T& data, list_node* n, list_node* p)
			: m_data(data), m_next(n), m_prev(p) {}
		T m_data;
		list_node* m_next;
		list_node* m_prev;
	};

public: 

    template <bool isconst = false>
	struct list_iterator
	{
		typedef T value_type;
		typedef std::ptrdiff_t difference_type;
		typedef typename choose<isconst, const T&, T&>::type reference;
		typedef typename choose<isconst, const T*, T*>::type pointer;
		typedef std::bidirectional_iterator_tag iterator_category;

		typedef typename choose<isconst, const list_node*, list_node*>::type nodeptr;
		
		list_iterator(nodeptr x = 0) : p(x) {}
		list_iterator(const list_iterator<false>& x) : p(x.p) {}
		reference operator*() const { return p->m_data; }
		pointer   operator->() const { return p; }

		list_iterator& operator++() {
			p = p->m_next;
			return *this;
		}

		list_iterator operator++(int) {
			list_iterator tmp(*this);
			++*this;
			return tmp;
		}

		list_iterator& operator--() {
			p = p->m_prev;
			return *this;
		}

		list_iterator operator--(int) {
			list_iterator tmp(*this);
			--*this;
			return tmp;
		}

		friend bool operator==(const list_iterator& x, 
							  const list_iterator& y)
		{
			return x.p == y.p;
		}

		friend bool operator!=(const list_iterator& x, 
							  const list_iterator& y)
		{
			return x.p != y.p;
		}

		nodeptr p; 
	};

	typedef list_iterator<false> iterator;
	typedef list_iterator<true> const_iterator;
	typedef typename list_iterator<false>::reference reference;
	typedef typename list_iterator<true>::reference const_reference;
	typedef T value_type;

	DList()
	{
		dummyNodePtr = new list_node(T(), 0, 0);
		dummyNodePtr->m_next = dummyNodePtr;
		dummyNodePtr->m_prev = dummyNodePtr;
	}

	~DList() 
	{
		clear();
		if (dummyNodePtr)
			delete dummyNodePtr;
	}

	void clear()
	{
		list_node* cur = dummyNodePtr->m_next;
		while(cur != dummyNodePtr)
		{
			list_node* tmp = cur;
			cur = tmp->m_next;
			delete tmp;
		}

		dummyNodePtr->m_next = dummyNodePtr;
		dummyNodePtr->m_prev = dummyNodePtr;
	}

	iterator begin() {
		return iterator(dummyNodePtr->m_next);
	}

	iterator end() {
		return iterator(dummyNodePtr);
	}

	reference front() {
		return *begin();
	}
	reference back() {
		return *(--end());
	}

	bool empty() const 
	{
		return dummyNodePtr->m_next == dummyNodePtr;
	}

	iterator insert(iterator pos, const T& x)
	{
		list_node* node = new list_node(x, 0, 0);
		node->m_next = pos.p;
		node->m_prev = pos.p->m_prev;
		pos.p->m_prev->m_next = node;
		pos.p->m_prev = node;

		return node;
	}

	void push_front(const T& x)
	{
		insert(begin(), x);
	}

	void push_back(const T& x)
	{
		insert(end(), x);
	}

	iterator erase(iterator pos)
	{
		list_node* prev = pos.p->m_prev;
		list_node* next = pos.p->m_next;

		prev->m_next = next;
		next->m_prev = prev;
		delete pos.p;
		return iterator(next);
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		// follow the std::list behaviour,
		// do not support for empty pop
		iterator tmp = end();
		erase(--tmp);
	}

	void remove(const T& value)
	{
		iterator first = begin();
		iterator last  = end();
		while(first != last)
		{
			iterator next = first;
			++next;
			if (*first == value)
				erase(first);
			
			first = next;
		}
	}

    // remove \consecutive duplicate\ elements 	
	void unique() 
	{
		iterator first = begin();
		iterator last  = end();

        //empty list, do nothing
		if (first == last)
			return;

		iterator next = first;
		while(++next != last)
		{
			if (*next == *first)
				erase(next);
			else
				first = next;

            // 1. original next has been erased, set next = first to iterator new next when ++next
            // 2. orignal next has been kept and first updated, so update the next to first as well.
			next = first; 
		}
	}


	void splice(iterator pos, DList<T>& x)
	{
		//assert( this != &x )
		if (!x.empty())
			transfer(pos, x.begin(), x.end());
	}

	void splice(iterator pos, DList<T>& x, iterator i)
	{
		iterator j = i;
		j++;
		
		// pos already just before i . or pos == i
		if (pos == i || pos == j) return;

		transfer(pos, i, j);
	}

	void splice(iterator pos, DList<T>& x, iterator first, iterator last)
	{
		if (first != last)
			transfer(pos, first, last);
	}


	void sort()
	{
		//TODO
	}


protected:
// refer to stl implementaion for moving [first, last) elements before pos.
// pos, [fir, last) might be two different list
//   
//      [pos->m_prev]   < - >         pos         < - > [pos->m_next]
//      [first->m_prev] < - >    [first, last-1]  < - > last
//       
//       [pos->m_prev] ->(3) [first, last->m_prev] ->(1) pos
//                                                 <-(4)
//       [first->m_prev] ->(2) last
//                       <-(5) 
// 
	void transfer(iterator pos, iterator first, iterator last)
	{
		// need to update pos.p->m_next/ pos.p->m_prev /...
		if (pos != last) {
			last.p->m_prev->m_next = pos.p;
			first.p->m_prev->m_next = last;
			pos.p->m_prev->m_next = first;

			list_node* tmp = pos.p->m_prev;
			pos.p->m_prev = last.p->m_prev;
			last.p->m_prev = first.p->m_prev;
			first.p->m_prev = tmp;
		}

	}


private:
	list_node* dummyNodePtr;
};




#endif