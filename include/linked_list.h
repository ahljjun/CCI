/*
** copied from https://www.panix.com/~elflord/cpp/list_howto/
** Copyright Donovan Rebbechi 2001. This tutorial may be distributed freely if this copyright notice is preserved. Changes require authors permission. 
** The code is no-strings attached free software, it may be redistributed, modified, and used.
*/
#include <iterator>

template <class T>
class List
{
	struct Node
	{
		Node(const T& data, Node* y=0) : m_data(data), m_next(y){}
		T m_data;
		Node* m_next;
	};
	Node* m_head;

public:

	class iterator
		:public std::iterator<std::forward_iterator_tag, T>
	{
		Node* m_rep;
	public:
		friend class const_iterator;
		friend class List;
		typedef T value_type;
		typedef T& reference;
		typedef T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;

		inline iterator(Node* x=0): m_rep(x){}
		inline iterator(const iterator& x): m_rep(x.m_rep){}
		inline iterator& operator=(const iterator& x)
		{
			m_rep = x.m_rep;
			return *this;
		}

		inline iterator& operator++()
		{
			m_rep = m_rep->m_next;
			return *this;
		}

		inline iterator operator++(int)
		{
			iterator tmp(*this);
			m_rep = m_rep->m_next;
			return tmp;
		}

		inline reference operator*() const
		{
			return m_rep->m_data;
		}

		inline pointer operator->() const
		{
			return m_rep;
		}

		inline bool operator==(const iterator& x) const
		{
			return m_rep == x.m_rep;
		}

		inline bool operator!=(const iterator& x) const
		{
			return m_rep != x.m_rep;
		}
	};

	class const_iterator
		: public std::iterator<std::forward_iterator_tag, T>
	{
		const Node* m_rep;
	public:
		friend class iterator;
		friend class List;
		typedef T  value_type;
		typedef const T& reference;
		typedef	const T* pointer;
		typedef int difference_type;
		typedef std::forward_iterator_tag iterator_category;

		inline const_iterator(const Node* x=0): m_rep(x) {}
		inline const_iterator(const const_iterator &x): m_rep(x.m_rep){}
		inline const_iterator(const iterator& x): m_rep(x.m_rep){}
		inline const_iterator& operator=(const const_iterator &x)
		{
			m_rep = x.m_rep	;
			return *this;
		}

		inline const_iterator& operator=(const iterator& x)
		{
			m_rep = x.m_rep;
			return *this;
		}

		inline const_iterator& operator++()
		{
			m_rep = m_rep->m_next;
			return *this;
		}

		inline const_iterator operator++(int)
		{
			const_iterator tmp(*this);
			m_rep = m_rep->m_next;
			return tmp;
		}

		inline reference operator*() const
		{
			return m_rep->m_data;
		}

		inline pointer operator->() const
		{
			return m_rep;
		}

		inline bool operator==(const const_iterator& x)const
		{
			return m_rep == x.m_rep;
		}

		inline bool operator != (const const_iterator& x) const
		{
			return m_rep != x.m_rep	;
		}

	};

	List() : m_head(0) {}
	List(const List& L) : m_head(0)
	{
		for(const_iterator i = L.begin(); i != L.end(); i++)
		{
			push_front(*i);
		}

		reverse();
	}

	void reverse()
	{
		Node* prev = 0;
		Node* cur = m_head;
		Node* next;
		while(cur)
		{
			next = cur->m_next;
			cur->m_next = prev;
			prev = cur;
			cur = next;
		}

		m_head = prev;
	}

	void swap(List& x)
	{
		Node* temp = m_head;
		m_head = x.m_head;
		x.m_head = temp;
	}

	List& operator=(const List& x)
	{
		List tmp(x);
		swap(tmp);
		return *this;
	}

	~List() { clear(); }

	void clear()
	{
		while(!empty())
			pop_front();
	}

	inline void push_front(const T& x)
	{
			Node* newhead = new Node(x, m_head);
			m_head = newhead;
	}

	inline void pop_front()
	{
		if (m_head)
		{
			Node* newhead = m_head->m_next;
			delete m_head;
			m_head = newhead;
		}
	}

	inline bool empty()
	{
		return m_head;
	}

	inline T& front() { return *begin(); }
	inline const T& front() const { return *begin(); }
	inline iterator begin() { return iterator(m_head); }
	inline iterator end() { return iterator(); }
	inline const_iterator begin() const { return const_iterator(m_head);}
	inline const_iterator end() const { return const_iterator(); }

	void erase_after(iterator& x)
	{
		Node* tmp =x.m_rep->m_next;
		if (tmp){
			x.m_rep->m_next = tmp->m_next;
			delete tmp;
		}
	}

	void insert_after(iterator& x, const T& y)
	{
		Node *node = new Node(y, x.m_rep->m_next);
		x.m_rep->m_next = node;
	}
};
