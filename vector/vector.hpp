/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:37:15 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/03 16:29:36 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdlib>
# include <memory>
# include <limits>
# include <iostream>
# include "vector_iterator.hpp"
# include "iterator_traits.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"

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
		void					insert(iterator position, size_type quantity,
			const value_type &value);
		template<typename InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last);
		iterator				erase(iterator position);
		iterator				erase(iterator first, iterator last);
		void					swap(vector &source);
		void					clear();
		allocator_type			get_allocator() const;
	private:
		void	init(const allocator_type &alloc);
		void	init();
		template<typename InputIterator>
		void	_assign(InputIterator first, InputIterator last, true_type);
		template<typename InputIterator>
		void	_assign(InputIterator first, InputIterator last, false_type);
		template<typename InputIterator>
		void	_insert(iterator position, InputIterator first,
			InputIterator last, true_type);
		template<typename InputIterator>
		void	_insert(iterator position, InputIterator first,
			InputIterator last, false_type);
		template<typename InputIterator>
		void	_insert(iterator position, InputIterator first,
			InputIterator last);

		size_type		_size;
		size_type		_capacity;
		pointer			_array;
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
	_assign(first, last, typename is_integral<InputIterator>::value());
}

template<typename T, typename Allocator>
vector<T, Allocator>::
vector(const vector &source)
{
	init();
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
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(_array + i);
	_size = 0;
	if (!source._size)
		return *this;
	if (source._size > _capacity)
		reserve(source._size);
	for (size_type i = 0; i < source._size; ++i)
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
	size_type	max_size = std::numeric_limits<size_type>::max() / sizeof(T);
	size_type	max_alloc = _allocator.max_size();
	
	return std::min(max_size, max_alloc);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
resize(size_type new_size, value_type value)
{
	if (new_size == _size)
		return;
	if (new_size > _capacity)
		reserve(_size + std::max(_size, new_size - _size));
	if (new_size < _size)
		while (_size != new_size)
		{
			--_size;
			_allocator.destroy(_array + _size);
		}
	else
		while (_size < new_size)
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
	if (capacity == 0)
		capacity = 1;
	if (capacity <= _capacity)
		return;
	pointer		new_array;
	size_type	i = 0;

	// allocate empty memory 
	// here don't need to capacity * sizeof(T) because allocator<T>
	new_array = _allocator.allocate(capacity);
	// construct (copy) objects in allocated memory == new(new_array + i) T(_array[i])
	try
	{
		for (; i < _size; ++i)
			_allocator.construct(new_array + i, _array[i]);
	} catch(...)
	{
		for (size_type j = 0; j < i; ++j)
			_allocator.destroy(new_array + j);
		_allocator.deallocate(new_array, capacity);
		throw;
	}
	// destoying objects == (_array + i)->~T();
	for (size_type j = 0; j < _size; ++j)
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
_assign(InputIterator first, InputIterator last, true_type)
{
	assign(static_cast<size_type>(first), last);
}

template<typename T, typename Allocator>
template <typename InputIterator>
void	vector<T, Allocator>::
_assign(InputIterator first, InputIterator last, false_type)
{
	assign(first, last);
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
	for (size_type i = 0; i < quantity; ++i)
		push_back(value);
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
push_back(const value_type &value)
{
	if (_size == _capacity)
		reserve(_capacity << 1);
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

	if (_size + 1 > _capacity)
		reserve(_size + std::max(_size, static_cast<size_type>(1)));
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
	_allocator.construct(&(*position), value);
	return position;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
insert(iterator position, size_type quantity, const value_type &value)
{
	if (!quantity)
		return;
	difference_type	pos_index = position - begin();

	if (_size + quantity > _capacity)
		reserve(_size + std::max(_size, quantity));
	_size += quantity;
	position = iterator(begin() + pos_index);
	iterator it = end() - 1;
	for (; it >= position + quantity; --it)
	{
		_allocator.construct(&(*it), *(it - quantity));
		_allocator.destroy(&(*(it - quantity)));
	}
	for (; it >= position; --it)
		_allocator.construct(&(*it), value);
}

template<typename T, typename Allocator>
template<typename InputIterator>
void	vector<T, Allocator>::
insert(iterator position, InputIterator first, InputIterator last)
{
	_insert(position, first, last, typename is_integral<InputIterator>::value());
}

template<typename T, typename Allocator>
template <typename InputIterator>
void	vector<T, Allocator>::
_insert(iterator position, InputIterator first, InputIterator last, true_type)
{
	insert(position, static_cast<size_type>(first), last);
}

template<typename T, typename Allocator>
template <typename InputIterator>
void	vector<T, Allocator>::
_insert(iterator position, InputIterator first, InputIterator last, false_type)
{
	_insert(position, first, last);
}

template<typename T, typename Allocator>
template<typename InputIterator>
void	vector<T, Allocator>::
_insert(iterator position, InputIterator first, InputIterator last)
{
	size_type		quantity;

	if (!(quantity = last - first))
		return;
	difference_type	pos_index = position - begin();

	if (_size + quantity > _capacity)
		reserve(_size + std::max(_size, quantity));
	_size += quantity;
	position = iterator(begin() + pos_index);
	iterator it = end() - 1;
	for (; it >= position + quantity; --it)
	{
		_allocator.construct(&(*it), *(it - quantity));
		_allocator.destroy(&(*(it - quantity)));
	}
	--last;
	for (; it >= position; --it, --last)
		_allocator.construct(&(*it), *last);
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
erase(iterator position)
{
	iterator	it_end = end() - 1;
	iterator	it = position;
	
	for (; it < it_end; ++it)
	{
		_allocator.destroy(&(*it));
		_allocator.construct(&(*it), *(it + 1));
	}
	--_size;
	return position;
}

template<typename T, typename Allocator>
typename vector<T, Allocator>::iterator	vector<T, Allocator>::
erase(iterator first, iterator last)
{
	iterator	it_end = end() - 1;
	size_type	quantity = last - first;
	
	for (; first < last && first < end() - quantity; ++first)
	{
		_allocator.destroy(&(*first));
		_allocator.construct(&(*first), *(first + quantity));
	}
	for (; first < last; ++first)
		_allocator.destroy(&(*first));
	_size -= quantity;
	return last;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
swap(vector &source)
{
	pointer		temp_pointer;

	_size ^= source._size; // XOR swap
	source._size ^= _size;
	_size ^= source._size;
	_capacity ^= source._capacity;
	source._capacity ^= _capacity;
	_capacity ^= source._capacity;
	temp_pointer = _array;
	_array = source._array;
	source._array = temp_pointer;
}

template<typename T, typename Allocator>
void	vector<T, Allocator>::
clear()
{
	for (size_type i = 0; i < _size; ++i)
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
void	vector<T, Allocator>::
init()
{
	_size = 0;
	_capacity = 0;
	_array = NULL;
}

template<typename T, typename Allocator>
void swap(vector<T, Allocator> &first, vector<T, Allocator> &second)
{
	first.swap(second);
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
