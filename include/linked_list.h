/*
** copied from https://www.panix.com/~elflord/cpp/list_howto/
** Copyright Donovan Rebbechi 2001. This tutorial may be distributed freely if this copyright notice is preserved. Changes require authors permission. 
** The code is no-strings attached free software, it may be redistributed, modified, and used.
*/
#include <iterator>
#include <set>
#include <iostream>

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
		return m_head == 0;
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

	void unique()
	{
		Node *prev = nullptr;
		Node *cur  = m_head;

		std::set<T> uniqueSet;
		while(cur)
		{
			if ( uniqueSet.find(cur->m_data) == uniqueSet.end() ) 
			{
				// not find
				uniqueSet.insert(cur->m_data);
				prev = cur;
				cur  = cur->m_next;
			}
			else
			{
				// find duplicate
				if ( cur->m_next )
					cur = cur->m_next->m_next;
				else
					cur = nullptr;

                prev->m_next = cur;
			}
		}	

        /*
		Node* cur = m_head;
		if (!cur)
			return;

		std::set<T> uniqueSet;
		uniqueSet.insert(cur->m_data);

		Node* next = cur->m_next;
		while(next)
		{
			if ( uniqueSet.find(next->m_data) == uniqueSet.end() )
			{
				uniqueSet.insert(next->m_data);
				cur = next;
				next = next->m_next;
			}
			else
			{
				cur->m_next = next->m_next;
				if ( next->m_next )
				{			
					next = next->m_next->m_next;
				}
				else
				{
					next = 0;
				}
			}
		}
        */
	}

	inline iterator r_nth(int n) 
	{ 
           Node *p=m_head;
           while( n > 0 ){
               p = p->m_next;
               n--;
           }
           if ( !p )
              return end();


           Node *p1 = m_head;
           while( p ){
               p = p->m_next;
               p1 = p1->m_next;
           }
          
           return iterator(p1);
	}
        
        inline void remove(iterator it)
        {
           if ( it.m_rep == m_head ) // remove head itself
 	   {
              m_head = m_head->m_next;
              return;
	   }
              
           Node *p=m_head;
           while( p && p->m_next != it.m_rep ){
               p = p->m_next;
           }
           
           if ( !p || !p->m_next )
               return ;
           
           p->m_next = p->m_next->m_next;
           return;
        }
   
        void sort_by_value(T value)
        {
            Node* lessThanValueNode = 0;
            Node* largerThanValueNode = 0;
            
            Node* node = m_head;
            Node* prev = 0;
            Node* tmp = 0;
            while( node ) {
                if ( node->m_data == value )
                {
                    // just leave it in the origin list
                    prev = node;
                    node = node->m_next;
                    continue;
                }
                
                tmp = node;
                //remove the elemnt first
                if ( node == m_head ) {
                   m_head = node->m_next;
                   node = node->m_next;
                }
                else {
                   if ( prev != nullptr )
		      prev->m_next = node->m_next; 
                   node = node->m_next;
                }

                if ( tmp->m_data < value )
                {
                      tmp->m_next = lessThanValueNode ;
	              lessThanValueNode  = tmp;
                }
                else
                   // insert to larger list
                {
                      tmp->m_next = largerThanValueNode;
	              largerThanValueNode  = tmp;
                }
            }
             
            Node* equalList = m_head; 
            // merge three list
            if ( lessThanValueNode ){
               m_head = lessThanValueNode;
               node = lessThanValueNode;
               while(node && node->m_next){
                   node = node->m_next;
               }  
            }

            if (equalList) {
               if ( node ) {
                  node->m_next = equalList;
                  node = equalList;
               } 
               else {
                  node = equalList;
               }
               while(node && node->m_next){
                   node = node->m_next;
               }  
            }
            
            if ( largerThanValueNode )
            {
               if ( node ) {
                  node->m_next = largerThanValueNode;
                  node = largerThanValueNode;
               } 
               else {
                  //just set the head 
                  m_head = largerThanValueNode;
               }
            }
             
            return;
        }


        bool isPalindromic()
        {
            Node* p1 = m_head;
            int len = 0;
            while( p1 ){
              len++;
              p1 = p1->m_next; 
            }
           
            p1 = m_head;
            List tempL;
            int i = len/2;
            while( i && p1 ){
                tempL.push_front(p1->m_data);        
                i--;
                p1 = p1->m_next;
            } 
          
            if ( (len - 2 * (len/2)) ) {
                 p1 = p1->m_next;
            }
            
            Node* p2 = tempL.m_head;
            for(; p1 != 0 && p2 != 0; p1=p1->m_next, p2 = p2->m_next)
            {
                if( p1->m_data != p2->m_data )
                   return false;
            }
            
            return true;
	}
};

