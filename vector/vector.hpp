/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:37:15 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/01 18:07:11 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdlib>
# include <memory>
# include <limits>
# include "vector_iterator.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"

namespace ft
{

template<typename T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef T										value_type;
		typedef Allocator								allocator_type;
		typedef T&										reference;
		typedef T*										pointer;
		typedef const T&								const_reference;
		typedef const T*								const_pointer;
		typedef ft::VectorIterator<value_type>			iterator;
		typedef ft::VectorIterator<value_type, true>	const_iterator;
		typedef ft::ReverseIterator<iterator>			reverse_iterator;
		typedef ft::ReverseIterator<const_iterator>		const_reverse_iterator;
		typedef	std::ptrdiff_t							difference_type;
		typedef size_t									size_type;

		explicit vector(const allocator_type &alloc = allocator_type()); // default
		explicit vector(size_t quantity, const value_type &value = value_type(),
			const allocator_type &alloc = allocator_type()); // fill
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last,
			const allocator_type &alloc = allocator_type()); // range
		vector(const vector &source); // copy
		~vector();
		
		vector			&operator=(const vector &source);
		reference		operator[](size_type position);
		const_reference	operator[](size_type position) const;

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;
		size_type				size() const;
		size_type				max_size() const;
		void					resize(size_type size, value_type value = value_type());
		size_type				capacity() const;
		bool					empty() const;
		void					reserve(size_type size);
		reference				at(size_type position);
		const_reference			at(size_type position) const;
		reference				front();
		const_reference			front() const;
		reference				back();
		const_reference			back() const;
		template <typename InputIterator>
		void					assign(InputIterator first, InputIterator last);
		void					assign(size_type quantity, const value_type &value);
		void					push_back(const value_type &value);
		void					pop_back();
		iterator				insert(iterator position, const value_type &value);
		void					insert(iterator position, size_type n, const value_type &value);
		template<typename InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last);
		iterator				erase(iterator position);
		iterator				erase(iterator first, iterator last);
		void					swap(vector &source);
		void					clear();
		allocator_type			get_allocator() const;
	private:
		void			init(const allocator_type &alloc);

		pointer			_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
};

template<typename T, typename Allocator>
vector<T, Allocator>::
vector(const allocator_type &alloc)
{
	init(alloc);
}

template<typename T, typename Allocator>
vector<T, Allocator>::
vector(size_type quantity, const value_type &value, const allocator_type &alloc)
{
	init(alloc);
	assign(quantity, value);
}

template<typename T, typename Allocator>
template<typename InputIterator>
vector<T, Allocator>::
vector(InputIterator first, InputIterator last, const allocator_type &alloc)
{
	init(alloc);
	assign(first, last);
}

template<typename T, typename Allocator>
vector<T, Allocator>::
vector(const vector &source)
{
	*this = source;
}

template<typename T, typename Allocator>
vector<T, Allocator>::
~vector()
{
	clear();
	_allocator.deallocate(_array, _capacity);
}

template<typename T, typename Allocator>
vector<T, Allocator>	&vector<T, Allocator>::
operator=(const vector &source)
{
	for (difference_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_size = 0;
	if (!source._size)
		return *this;
	if (source._size > _capacity)
		reserve(source._size);
	for (difference_type i = 0; i < source._size; ++i)
		push_back(source[i]);
	return *this;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference	vector<T, Allocator>::
operator[](size_type position)
{
	return _array[position];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::
operator[](size_type position) const
{
	return _array[position];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
begin()
{
	return _array;
} // here default constructor iterator(T *_pointer) will be called

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::
begin() const
{
	return _array;
} // here default constructor iterator(const T *_pointer) will be called

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
end()
{
	return _array + _size;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_iterator	vector<T, Allocator>::
end() const
{
	return _array + _size;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator	vector<T, Allocator>::
rbegin()
{
	return reverse_iterator(end());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator	vector<T, Allocator>::
rbegin() const
{
	return const_reverse_iterator(end());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reverse_iterator	vector<T, Allocator>::
rend()
{
	return reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reverse_iterator	vector<T, Allocator>::
rend() const
{
	return const_reverse_iterator(begin());
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::
size() const
{
	return _size;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::
max_size() const
{
	return std::numeric_limits<difference_type>::max();
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
resize(size_type size, value_type value)
{
	if (size == _size)
		return;
	if (size > _capacity)
		reserve(size);
	if (size < _size)
		while (_size != size)
		{
			--_size;
			_allocator.destroy(_array + _size);
		}
	else
		while (_size < size)
		{
			_allocator.construct(_array + _size, value);
			++_size;
		}
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::size_type	vector<T, Allocator>::
capacity() const
{
	return _capacity;
}

template<typename T, typename Allocator>
bool	vector<T, Allocator>::
empty() const
{
	return _size;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
reserve(size_type capacity)
{
	if (capacity <= _capacity)
		return;
	pointer	new_array;

	// allocate empty memory 
	// here don't need to capacity * sizeof(T) because allocator<T>
	new_array = _allocator.allocate(capacity);
	// construct (copy) objects in allocated memory == new(new_array + i) T(_array[i])
	difference_type i = 0;
	try
	{
		for (; i < _size; ++i)
			_allocator.construct(new_array + i, _array[i]);
	} catch(...)
	{
		for (difference_type j = 0; j < i; ++j)
			_allocator.destroy(new_array + j);
		_allocator.deallocate(new_array, capacity);
		throw;
	}
	// destoying objects == (_array + i)->~T();
	for (difference_type j = 0; j < _size; ++j)
		_allocator.destroy(_array + j);
	_allocator.deallocate(_array, _capacity);
	_array = new_array;
	_capacity = capacity;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference	vector<T, Allocator>::
at(size_type position)
{
	if (position > _size)
		throw std::out_of_range("index is out of range");
	return _array[position];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::
at(size_type position) const
{
	if (position > _size)
		throw std::out_of_range("index is out of range");
	return _array[position];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference	vector<T, Allocator>::
front()
{
	return _array[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::
front() const
{
	return _array[0];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::reference	vector<T, Allocator>::
back()
{
	return _array[_size - 1];
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::const_reference	vector<T, Allocator>::
back() const
{
	return _array[_size - 1];
}

template<typename T, typename Allocator>
template <typename InputIterator>
void	vector<T, Allocator>::
assign(InputIterator first, InputIterator last)
{
	clear();
	if (first != last)
		reserve(last - first);
	while (first != last)
		push_back(*first++);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
assign(size_type quantity, const value_type &value)
{
	clear();
	if (!quantity)
		return;
	reserve(quantity);
	for (difference_type i = 0; i < quantity; ++i)
		push_back(value);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
push_back(const value_type &value)
{
	if (_size == _capacity)
		reserve(_capacity ? _capacity * 2 : 1);
	_allocator.construct(_array + _size, value);
	++_size;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
pop_back()
{
	_allocator.destroy(_array + --_size);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
insert(iterator position, const value_type &value)
{
	difference_type	pos_index = position - begin();
	reserve(_size + 1);
	++_size;
	position = iterator(begin() + pos_index);
	iterator it = end() - 1;
	for (; it > position; --it)
	{
		// *it = *(it - 1);
		// because can work with some kind of objects, we can't just
		//	= them. rith way is call their copy constructors and destroy
		//	old objects.
		//	like: new(&(*it)) T(*(it - 1));
		//	(it - 1)->~T();
		_allocator.construct(&(*it), *(it - 1));
		_allocator.destroy(&(*(it - 1)));
	}
	*position = value;
	return position;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
insert(iterator position, size_type n, const value_type &value)
{
	// TODO
}

template<typename T, typename Allocator>
template<typename InputIterator>
void	vector<T, Allocator>::
insert(iterator position, InputIterator first, InputIterator last)
{
	// TODO
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
erase(iterator position)
{
	// TODO
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
erase(iterator first, iterator last)
{
	// TODO
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
swap(vector &source)
{
	// TODO
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
clear()
{
	for (difference_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_size = 0;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::allocator_type	vector<T, Allocator>::
get_allocator() const
{
	return _allocator;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
init(const allocator_type &alloc)
{
	_allocator = alloc;
	_size = 0;
	_capacity = 0;
	_array = NULL;
}

template<typename T, typename Allocator>
void swap(vector<T, Allocator> &first, vector<T, Allocator> &second)
{
	// TODO
}

template<typename T, class Allocator>
bool operator==(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	if (left.size() != right.size())
		return false;
	typename vector<T, Allocator>::const_iterator it_left = left.begin();
	typename vector<T, Allocator>::const_iterator it_rigth = right.begin();
	typename vector<T, Allocator>::const_iterator it_left_end = left.end();
	while (it_left != it_left_end)
		if (*it_left++ != *it_rigth++)
			return false;
	return true;
}

template<typename T, class Allocator>
bool operator!=(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	return !operator==(left, right);
}

template<typename InputIterator1, typename InputIterator2>
bool	lexicographical_compare(InputIterator1 first_1, InputIterator1 last_1,
	InputIterator2 first_2, InputIterator2 last_2)
{
	while (first_1 != last_1)
	{
		if (first_2 == last_2 || *first_1 > *first_2)
			return false;
		else if (*first_1 < *first_2)
			return true;
		++first_1;
		++first_2;
	}
	return first_2 != last_2;
}

template<typename T, class Allocator>
bool operator<(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	return lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template<typename T, class Allocator>
bool operator<=(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	if (operator==(left, right))
		return true;
	return lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template<typename T, class Allocator>
bool operator>(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	return !lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

template<typename T, class Allocator>
bool operator>=(const vector<T, Allocator> &left, const vector<T, Allocator> &right)
{
	if (operator==(left, right))
		return true;
	return !lexicographical_compare(left.begin(), left.end(), right.begin(), right.end());
}

} // namespace ft

#endif
