/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 16:04:34 by nelisabe          #+#    #+#             */
/*   Updated: 2021/07/30 17:28:30 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

using std::random_access_iterator_tag;

template<typename T>
VectorIterator<T>	operator+(int n, const VectorIterator<T> &right);

template<typename T>
class VectorIterator
{
	public:
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t				differrence_type;

		VectorIterator(T *pointer);
		VectorIterator(const VectorIterator &source);

		VectorIterator		&operator=(const VectorIterator &source);
		bool				operator==(const VectorIterator &right) const;
		bool				operator!=(const VectorIterator &right) const;
		T					&operator*();
		T					*operator->();
		VectorIterator		&operator++();
		VectorIterator		operator++(int);
		VectorIterator		&operator--();
		VectorIterator		operator--(int);
		VectorIterator		operator+(int rigth) const;
		VectorIterator		operator-(int rigth) const;
		differrence_type	operator-(const VectorIterator &right) const;
		bool				operator<(const VectorIterator &right) const;
		bool				operator>(const VectorIterator &right) const;
		bool				operator<=(const VectorIterator &right) const;
		bool				operator>=(const VectorIterator &right) const;
		VectorIterator		&operator+=(int value);
		VectorIterator		&operator-=(int value);
		T					&operator[](int index);
	private:
		T	*_pointer;
};

template<typename T>
VectorIterator<T>::VectorIterator(T* pointer) 
{
	_pointer = pointer;
}

template<typename T>
VectorIterator<T>::VectorIterator(const VectorIterator &source)
{
	*this = source;
}

template<typename T>
VectorIterator<T>	&VectorIterator<T>::operator=(const VectorIterator &source)
{
	_pointer = source._pointer;
	return *this;
}

template<typename T>
bool	VectorIterator<T>::operator==(const VectorIterator &right) const
{
	return _pointer == right._pointer;
}

template<typename T>
bool	VectorIterator<T>::operator!=(const VectorIterator &rigth) const
{
	return _pointer != rigth._pointer;
}

template<typename T>
T		&VectorIterator<T>::operator*()
{
	return *_pointer;
}

template<typename T>
T		*VectorIterator<T>::operator->()
{
	return _pointer;
}

template<typename T>
VectorIterator<T>	&VectorIterator<T>::operator++()
{
	_pointer++;
	return *this;
}

template<typename T>
VectorIterator<T>	VectorIterator<T>::operator++(int)
{
	VectorIterator<T>	temp_it = *this;

	_pointer++;
	return temp_it;
}

template<typename T>
VectorIterator<T>	&VectorIterator<T>::operator--()
{
	_pointer--;
	return *this;
}

template<typename T>
VectorIterator<T>	VectorIterator<T>::operator--(int)
{
	VectorIterator<T>	temp_it = *this;

	_pointer--;
	return temp_it;
}

template<typename T>
VectorIterator<T>	VectorIterator<T>::operator+(int rigth) const
{
	return _pointer + rigth;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

template<typename T>
VectorIterator<T>	VectorIterator<T>::operator-(int rigth) const
{
	return _pointer - rigth;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

template<typename T>
VectorIterator<T>::differrence_type
					VectorIterator<T>::operator-(const VectorIterator &rigth) const
{
	return _pointer - rigth._pointer;
}

template<typename T>
bool				VectorIterator<T>::operator<(const VectorIterator &rigth) const
{
	return _pointer < rigth._pointer;
}

template<typename T>
bool				VectorIterator<T>::operator>(const VectorIterator &rigth) const
{
	return _pointer > rigth._pointer;
}

template<typename T>
bool				VectorIterator<T>::operator<=(const VectorIterator &rigth) const
{
	return _pointer <= rigth._pointer;
}

template<typename T>
bool				VectorIterator<T>::operator>=(const VectorIterator &rigth) const
{
	return _pointer >= rigth._pointer;
}

template<typename T>
VectorIterator<T>	&VectorIterator<T>::operator+=(int value)
{
	_pointer += value;
	return *this;
}

template<typename T>
VectorIterator<T>	&VectorIterator<T>::operator-=(int value)
{
	_pointer -= value;
	return *this;
}

template<typename T>
T					&VectorIterator<T>::operator[](int index)
{
	return _pointer[index];
}

template<typename T>
VectorIterator<T>	operator+(int n, const VectorIterator<T> &right) // non-memer operator+
{
	return right + n;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

} // namespace ft

#endif
