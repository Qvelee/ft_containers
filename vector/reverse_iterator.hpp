/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ReverseIterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 12:51:14 by nelisabe          #+#    #+#             */
/*   Updated: 2021/07/31 14:05:12 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REVERSE_ITARATOR_HPP
# define REVERSE_ITARATOR_HPP

# include "vector_iterator.hpp"

namespace ft
{

template<typename Iterator>
class ReverseIterator
{
	public:
		typedef Iterator 												iterator_type;
		typedef typename iterator_traits<Iterator>::iterator_category	iterator_category;
		typedef typename iterator_traits<Iterator>::value_type			value_type;
		typedef typename iterator_traits<Iterator>::difference_type		difference_type;
		typedef typename iterator_traits<Iterator>::pointer				pointer;
		typedef typename iterator_traits<Iterator>::reference			reference;

		ReverseIterator(); // default
		explicit ReverseIterator(iterator_type it); // initialization
		ReverseIterator(const ReverseIterator<Iterator> &source); // copy
		~ReverseIterator();

		iterator_type	base() const;
		reference		operator*() const;
		ReverseIterator	operator+(difference_type value) const;
		ReverseIterator	&operator++();
		ReverseIterator	operator++(int);
		ReverseIterator	&operator+=(difference_type value);
		ReverseIterator	operator-(difference_type value) const;
		ReverseIterator	&operator--();
		ReverseIterator	operator--(int);
		ReverseIterator	&operator-=(difference_type value);
		pointer			operator->() const;
		reference		operator[](difference_type value) const;
		template<typename T>
		operator ReverseIterator<VectorIterator<T, true> >();
	private:
		iterator_type	_iterator;
};

template<typename I>
ReverseIterator<I>::
ReverseIterator() { }

template<typename I>
ReverseIterator<I>::
ReverseIterator(iterator_type it)
{
	_iterator = it;
}

template<typename I>
ReverseIterator<I>::
ReverseIterator(const ReverseIterator &source)
{
	_iterator = source._iterator;
}

template<typename I>
ReverseIterator<I>::
~ReverseIterator() { }

template<typename I>
typename ReverseIterator<I>::iterator_type ReverseIterator<I>::
base() const
{
	return _iterator;
}

template<typename I>
typename ReverseIterator<I>::reference ReverseIterator<I>::
operator*() const
{
	iterator_type	temp_it = _iterator;

	--temp_it;
	return *temp_it;
}

template<typename I>
ReverseIterator<I> ReverseIterator<I>::
operator+(ReverseIterator<I>::difference_type value) const
{
	return _iterator - value;
}

template<typename I>
ReverseIterator<I> &ReverseIterator<I>::
operator++()
{
	--_iterator;
	return *this;
}

template<typename I>
ReverseIterator<I> ReverseIterator<I>::
operator++(int)
{
	ReverseIterator<I>	temp_it = *this;
	
	--_iterator;
	return temp_it;
}

template<typename I>
ReverseIterator<I> &ReverseIterator<I>::
operator+=(ReverseIterator<I>::difference_type value)
{
	_iterator -= value;
	return *this;
}

template<typename I>
ReverseIterator<I> ReverseIterator<I>::
operator-(ReverseIterator<I>::difference_type value) const
{
	return _iterator + value;
}

template<typename I>
ReverseIterator<I> &ReverseIterator<I>::
operator--()
{
	++_iterator;
	return *this;
}

template<typename I>
ReverseIterator<I> ReverseIterator<I>::
operator--(int)
{
	ReverseIterator<I>	temp_it = *this;
	
	++_iterator;
	return temp_it;
}

template<typename I>
ReverseIterator<I> &ReverseIterator<I>::
operator-=(ReverseIterator<I>::difference_type value)
{
	_iterator += value;
	return *this;
}

template<typename I>
typename ReverseIterator<I>::pointer ReverseIterator<I>::
operator->() const
{
	return &(*_iterator);
}

template<typename I>
typename ReverseIterator<I>::reference ReverseIterator<I>::
operator[](ReverseIterator<I>::difference_type value) const
{
	return _iterator[value];
}

template<typename I, typename T>
ReverseIterator<I>::
operator ReverseIterator<VectorIterator<T, true> >()
{
	// TODO
}


// NON-MEMBER FUNCTIONS

template<typename Iterator>
bool	operator==(const ReverseIterator<Iterator> &left,\
	const ReverseIterator<Iterator> &right)
{
	return left.base() == right.base();
}

template<typename Iterator>
bool	operator!=(const ReverseIterator<Iterator> &left,
    const ReverseIterator<Iterator> &right)
{
	return left.base() != right.base();
}

template<typename Iterator>
bool	operator<(const ReverseIterator<Iterator> &left,
    const ReverseIterator<Iterator> &right)
{
	return left.base() > right.base();
}

template<typename Iterator>
bool	operator<=(const ReverseIterator<Iterator> &left,
    const ReverseIterator<Iterator> &right)
{
	return left.base() >= right.base();
}

template<typename Iterator>
bool	operator>(const ReverseIterator<Iterator> &left,
    const ReverseIterator<Iterator> &right)
{
	return left.base() < right.base();
}

template<typename Iterator>
bool	operator>=(const ReverseIterator<Iterator> &left,
    const ReverseIterator<Iterator> &right)
{
	return left.base() <= right.base();
}

template <class Iterator>
ReverseIterator<Iterator>
operator+(typename ReverseIterator<Iterator>::difference_type value,
	const ReverseIterator<Iterator> &reverse_iterator)
{
	return reverse_iterator.base() - value;
}

template <class Iterator>
typename ReverseIterator<Iterator>::difference_type
operator-(const ReverseIterator<Iterator> &left,
	const ReverseIterator<Iterator> &right)
{
	return left.base() - right.base();
}

} //namespace ft

#endif
