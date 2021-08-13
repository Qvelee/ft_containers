/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_iterator.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 16:04:34 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/13 11:57:41 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_ITERATOR_HPP
# define VECTOR_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "conditional.hpp"

namespace ft
{

using std::random_access_iterator_tag;

template<typename T, bool IsConst = false>
class VectorIterator
{
	public:
		typedef typename conditional<IsConst, const T, T>::type	conditional_t;
		typedef conditional_t				value_type;
		typedef conditional_t*				pointer;
		typedef conditional_t&				reference;
		typedef random_access_iterator_tag	iterator_category;
		typedef std::ptrdiff_t				difference_type;

		VectorIterator();
		VectorIterator(conditional_t *pointer);
		VectorIterator(const VectorIterator &source);
		~VectorIterator();

		VectorIterator		&operator=(const VectorIterator &source);
		bool				operator==(const VectorIterator &right) const;
		bool				operator!=(const VectorIterator &right) const;
		reference			operator*();
		pointer				operator->();
		VectorIterator		&operator++();
		VectorIterator		operator++(int);
		VectorIterator		&operator--();
		VectorIterator		operator--(int);
		VectorIterator		operator+(int rigth) const;
		VectorIterator		operator-(int rigth) const;
		difference_type		operator-(const VectorIterator &right) const;
		bool				operator<(const VectorIterator &right) const;
		bool				operator>(const VectorIterator &right) const;
		bool				operator<=(const VectorIterator &right) const;
		bool				operator>=(const VectorIterator &right) const;
		VectorIterator		&operator+=(int value);
		VectorIterator		&operator-=(int value);
		reference			operator[](int index);
		operator VectorIterator<T, true>();
	private:
		conditional_t	*_pointer;
};

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
VectorIterator() : _pointer(NULL) { }

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
VectorIterator(VectorIterator<T, IsConst>::conditional_t *pointer) :
	_pointer(pointer) { }

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
VectorIterator(const VectorIterator &source)
{
	*this = source;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
~VectorIterator() { }

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator=(const VectorIterator &source)
{
	if (this == &source)
		return *this;
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
typename VectorIterator<T, IsConst>::reference	VectorIterator<T, IsConst>::
operator*()
{
	return *_pointer;
}

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::pointer	VectorIterator<T, IsConst>::
operator->()
{
	return _pointer;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator++()
{
	++_pointer;
	return *this;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator++(int)
{
	VectorIterator<T, IsConst>	temp_it = *this;

	++_pointer;
	return temp_it;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	&VectorIterator<T, IsConst>::
operator--()
{
	--_pointer;
	return *this;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator--(int)
{
	VectorIterator<T, IsConst>	temp_it = *this;

	--_pointer;
	return temp_it;
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator+(int rigth) const
{
	return _pointer + rigth;
} // here default constructor VectorIterator(T* pointer) will be called)

template<typename T, bool IsConst>
VectorIterator<T, IsConst>	VectorIterator<T, IsConst>::
operator-(int rigth) const
{
	return _pointer - rigth;
} // here default constructor VectorIterator(T* pointer) will be called)

template<typename T, bool IsConst>
typename VectorIterator<T, IsConst>::difference_type VectorIterator<T, IsConst>::
operator-(const VectorIterator &rigth) const
{
	return _pointer - rigth._pointer;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
operator<(const VectorIterator &rigth) const
{
	return _pointer < rigth._pointer;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
operator>(const VectorIterator &rigth) const
{
	return _pointer > rigth._pointer;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
operator<=(const VectorIterator &rigth) const
{
	return _pointer <= rigth._pointer;
}

template<typename T, bool IsConst>
bool	VectorIterator<T, IsConst>::
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
typename VectorIterator<T, IsConst>::reference	VectorIterator<T, IsConst>::
operator[](int index)
{
	return _pointer[index];
}

template<typename T, bool IsConst>
VectorIterator<T, IsConst>::
operator VectorIterator<T, true>()
{
	return VectorIterator<T, true>(_pointer);
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
