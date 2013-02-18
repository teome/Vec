/* 
 * Implementation of a simple vector class.
 * From accelerated c++ book
 * 18/02/13		Dominic Kelly
 */
#include <memory>

template <class T>
class Vec {
public:
	typedef T* iterator;
	typedef const T* const_iterator;
	typedef size_t size_type;
	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;

	// implement ctors via a create method since the same function
	// can be used in ctors, copy and assignment...
	Vec() { create(); }
  	explicit Vec(size_type n, const T& t = T()) { create(n, t); }
	Vec(const Vec& v) { create(v.begin(), v.end()); }
	Vec& operator=(const Vec&);
	~Vec() { uncreate(); } 	

	T& operator[](size_type i) { return data[i]; }
	const T& operator[](size_type i) { return data[i]; }

	void push_back(const T& t) {
		if (avail == limit)
			grow();
		unchecked_append(t);
	}
	
	size_type size() const { return avail - data; }

	iterator begin() { return data; }
	const_iterator begin() { return data; }
	
	iterator end() const { return avail; }
	const_iterator end() const { return avail; }
	
private:
	iterator data; // first element in the Vec
	iterator avail; // one past last element in the Vec
	iterator limit; // one past allocated array

	// fascilitators for memory allocation
	allocator<T> alloc;

	// allocate and initialise the underlying array
	void create();
	void create(size_type, const T&);
	void create(const_iterator, const_iterator);

	// destroy the elements in the array and free memory
	void uncreate();

	// support functions for push_back
	void grow();
	void unchecked_append(const T&);
};

