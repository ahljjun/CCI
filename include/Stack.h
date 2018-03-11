#ifndef __MY_STACK_H
#define __MY_STACK_H

template <class T, class Sequence>
class Stack {
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::reference  reference;
	typedef typename Sequence::const_reference const_reference;
	typedef int size_type;

protected:
	Sequence c;
public:
	bool empty() const { return c.empty(); }
	reference top() { return c.back(); }
	const_reference top() const { return c.back(); }
	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_back(); }
};

#endif