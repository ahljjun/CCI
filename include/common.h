#ifndef __COMMON_H
#define __COMMON_H

/*
 * referenced from http://collaboration.cmc.ec.gc.ca/science/rpn/biblio/ddj/Website/articles/CUJ/2001/0101/austern/austern.htm
*/
template <bool flag, class ConstType, class Type>
struct choose;

template <class ConstType, class Type>
struct choose<true, ConstType, Type>
{
	typedef ConstType type;
};

template <class ConstType, class Type>
struct choose<false, ConstType, Type>
{
	typedef Type type;
};

#endif