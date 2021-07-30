/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 16:04:34 by nelisabe          #+#    #+#             */
/*   Updated: 2021/07/30 20:10:11 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

using std::random_access_iterator_tag;

template<bool B, typename T1, typename T2>
struct conditional
{ // if flag is false
	typedef T2 type;
};

template<typename T1, typename T2>
struct conditional<true, T1, T2>
{ // if flag is true specialization
	typedef T1 type;
};

template<typename T, bool IsConst = false>
class VectorIterator
{
	public:
		typedef T							value_type;
		typedef T*							pointer;
		typedef T&							reference;
		typedef random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t				differrence_type;
		typedef typename conditional<IsConst, T*, const T*>::type	conditional_t;

		VectorIterator(T *pointer);
		VectorIterator(const VectorIterator &source);

		VectorIterator		&operator=(const VectorIterator &source);
		bool				operator==(const VectorIterator &right) const;
		bool				operator!=(const VectorIterator &right) const;
		conditional_t		&operator*();
		conditional_t		*operator->();
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
		conditional_t		&operator[](int index);
	private:
		conditional_t	_pointer;
};

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
VectorIterator(T* pointer)
{
	_pointer = pointer;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
VectorIterator(const VectorIterator &source)
{
	*this = source;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator=(const VectorIterator &source)
{
	_pointer = source._pointer;
	return *this;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
operator==(const VectorIterator &right) const
{
	return _pointer == right._pointer;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
operator!=(const VectorIterator &rigth) const
{
	return _pointer != rigth._pointer;
}

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::conditional_t	&VectorIterator<T, IsConst>::
operator*()
{
	return *_pointer;
}

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::conditional_t	*VectorIterator<T, IsConst>::
operator->()
{
	return _pointer;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator++()
{
	_pointer++;
	return *this;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator++(int)
{
	VectorIterator<T, IsConst>	temp_it = *this;

	_pointer++;
	return temp_it;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator--()
{
	_pointer--;
	return *this;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator--(int)
{
	VectorIterator<T, IsConst>	temp_it = *this;

	_pointer--;
	return temp_it;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator+(int rigth) const
{
	return _pointer + rigth;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator-(int rigth) const
{
	return _pointer - rigth;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::differrence_type VectorIterator<T, IsConst>::
operator-(const VectorIterator &rigth) const
{
	return _pointer - rigth._pointer;
}

template<typename T, bool IsConst>
bool				VectorIterator<T, IsConst>::
operator<(const VectorIterator &rigth) const
{
	return _pointer < rigth._pointer;
}

template<typename T, bool IsConst>
bool				VectorIterator<T, IsConst>::
operator>(const VectorIterator &rigth) const
{
	return _pointer > rigth._pointer;
}

template<typename T, bool IsConst>
bool				VectorIterator<T, IsConst>::
operator<=(const VectorIterator &rigth) const
{
	return _pointer <= rigth._pointer;
}

template<typename T, bool IsConst>
bool				VectorIterator<T, IsConst>::
operator>=(const VectorIterator &rigth) const
{
	return _pointer >= rigth._pointer;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator+=(int value)
{
	_pointer += value;
	return *this;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator-=(int value)
{
	_pointer -= value;
	return *this;
}

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::conditional_t	&VectorIterator<T, IsConst>::
operator[](int index)
{
	return _pointer[index];
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>
operator+(int n, const VectorIterator<T, IsConst> &right) // non-memer operator+
{
	return right + n;
	// here default constructor (VectorIterator(T* pointer) will be called)
}

} // namespace ft

#endif
