/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:37:15 by nelisabe          #+#    #+#             */
/*   Updated: 2021/07/30 16:11:05 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <cstdlib>
# include <memory>

# include "vector_iterator.hpp"
# include "iterator_traits.hpp"

namespace ft
{
	
template <typename T, typename Allocator>
void swap (vector<T, Allocator> &first, vector<T, Allocator> &second);

template <typename T, class Allocator>
bool operator==(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template <typename T, class Allocator>
bool operator!=(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template <typename T, class Allocator>
bool operator<(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template <typename T, class Allocator>
bool operator<=(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template <typename T, class Allocator>
bool operator>(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template <typename T, class Allocator>
bool operator>=(const vector<T, Allocator> &left, const vector<T, Allocator> &right);

template<typename T, class Allocator = std::allocator<T> >
class vector
{
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef T& reference;
		typedef T* pointer;
		typedef const T& const_reference;
		typedef const T* const_pointer;
		typedef ft::VectorIterator<value_type> iterator;
		typedef iterator const_iterator; // TODO change!!!!!
		typedef iterator reverse_iterator;
		typedef iterator const_reverse_iterator;
		typedef	difference_type;
		typedef size_t size_type;

		explicit vector(const allocator_type &alloc = allocator_type()); // default
		explicit vector(size_t size, const value_type &value = value_type(),\
			const allocator_type &alloc = allocator_type()); // fill
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last,\
			const allocator_type &alloc = allocator_type()); // range
		vector(const vector &source); // copy
		~vector();
		
		vector			&operator=(const vector &source);
		reference		operator[](size_type position);
		const_reference	operator[](size_type size) const;

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
		void					assign(size_type n, const value_type& value);
		void					push_back(const value_type& value);
		void					pop_back();
		iterator				insert(iterator position, const value_type& value);
		void					insert(iterator position, size_type n, const value_type& value);
		template<typename InputIterator>
		void					insert(iterator position, InputIterator first, InputIterator last);
		iterator				erase(iterator position);
		iterator				erase(iterator first, iterator last);
		void					swap(vector &source);
		void					clear();
		allocator_type			get_allocator() const;
	private:
		pointer			_array;
		size_type		_size;
		size_type		_capacity;
		allocator_type	_allocator;
};

}

#endif
