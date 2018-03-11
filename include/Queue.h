#ifndef __MY_QUEUE_H
#define __MY_QUEUE_H

template <class T, class Sequence>
class Queue
{
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::reference  reference;
	typedef typename Sequence::const_reference const_reference;
	typedef int size_type;

protected:
	Sequence c;

public:
	bool empty() const { return c.empty(); }
	reference front() { return c.front(); }
	reference back() { return c.back(); }
	const_reference front() const { return c.front(); }
	const_reference back() const { return c.back(); }

	void push(const value_type& x) { c.push_back(x); }
	void pop() { c.pop_front(); }
};

#endif
