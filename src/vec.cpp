/*
 * vec.cpp
 * Simple implementation of the vector class.
 * Based on notes from the Accelerated C++ book.
 * 18/02/13		Dominic Kelly.
 */
#include <memory> // provides the allocator class for dynamic memory
#include "vec.h"

template <class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
	// check for self assignment
	if (this != &rhs) {
		
		// free old array
		uncreate();

		// create new Vec as copy of rhs
		create(rhs.begin(), rhs.end());
	}
	return *this;
}

// memory management functions for creation and deletion using the
// allocator class of memory.h.
// This is used instead of new/delete since these initialise each element
// when there is no need to introduce this overhead here, particularly when
// a Vec is grown to twice the size and may never use all the elements
template <class T> void Vec<t>::create();
{
	data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val)
{
	data = alloc.allocate(n);
	limit = avail = data + n;
	uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j) 
{
	data = alloc.allocate(j - i);
	limit = avail = uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate()
{
	if (data) {
		// destroy elements that were constructed (in reverse order)
		iterator it = avail;
		while (it != data)
			alloc.destroy(--it);

		// return all the allocated space
		alloc.deallocate(data, limit - data);
	}
	// reset to empty vector
	data = avail = limit = 0;
}

// grow the vector based on doubling principle for efficiency
templete <class T> void Vec<T>::grow()
{
	// Twice as much.
	// Use max so that the function still works if called on an empty
	// vector.  So minimum of one element is allocated.
	size_type kNewSize = max(2 * (limit - data), ptrdiff_t(1));

	// allocate new space and copy current vals in
	iterator new_data = alloc.allocate(kNewSize);
	iterator new_avail = uninitialized_copy(data, avail, new_data);

	// return the old allocated space
	uncreate();

	// set pointers to the new space
	data = new_data;
	avail = new_avail;
	limit = data + kNewSize;
}

// NB this assumes that the space is allocated but uninitialized.
// This is fine since is it only used after allocation
template <class T> void Vec<T>::unchecked_append(const T& val)
{
	// this function initialises on element in already allocated
	// memory location.
	alloc.construct(avail++, val);
}

