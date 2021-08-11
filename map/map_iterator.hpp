/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:10:59 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/11 14:57:42 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

#include "iterator_traits.hpp"

namespace ft
{

using std::bidirectional_iterator_tag;

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
class MapIterator
{
	public:
		typedef typename conditional<IsConst, const T, T>::type	conditional_t;
		typedef conditional_t						value_type;
		typedef typename conditional_t::data_type	data_type;
		typedef conditional_t*						pointer;
		typedef conditional_t&						reference;
		typedef bidirectional_iterator_tag			iterator_category;
		typedef std::ptrdiff_t						difference_type;

		MapIterator();
		MapIterator(conditional_t *node);
		MapIterator(const MapIterator &source);
		~MapIterator();

		MapIterator	&operator=(const MapIterator &source);
		bool		operator==(const MapIterator &right) const;
		bool		operator!=(const MapIterator &right) const;
		data_type	&operator*();
		data_type	*operator->();
		MapIterator	&operator++();
		MapIterator	operator++(int);
		MapIterator	&operator--();
		MapIterator	operator--(int);
		operator MapIterator<T, true>();
	private:
		conditional_t	*_node;
};

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
MapIterator() { _node = NULL; }

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
MapIterator(MapIterator<T, IsConst>::conditional_t *node)
{
	_node = node;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
MapIterator(const MapIterator &source)
{
	*this = source;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
~MapIterator() { }

template<typename T, bool IsConst>
MapIterator<T, IsConst>	&MapIterator<T, IsConst>::
operator=(const MapIterator &source)
{
	_node = source._node;
	return *this;
}

template<typename T, bool IsConst>
bool	MapIterator<T, IsConst>::
operator==(const MapIterator &right) const
{
	return _node == right._node;
}

template<typename T, bool IsConst>
bool	MapIterator<T, IsConst>::
operator!=(const MapIterator &rigth) const
{
	return _node != rigth._node;
}

template<typename T, bool IsConst>
typename MapIterator<T, IsConst>::data_type	&MapIterator<T, IsConst>::
operator*()
{
	return _node->data;
}

template<typename T, bool IsConst>
typename MapIterator<T, IsConst>::data_type	*MapIterator<T, IsConst>::
operator->()
{
	return _node->data;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>	&MapIterator<T, IsConst>::
operator++()
{
	// ++_node; TODO
	return *this;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>	MapIterator<T, IsConst>::
operator++(int)
{
	MapIterator<T, IsConst>	temp_it = *this;

	// ++_node; TODO
	return temp_it;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>	&MapIterator<T, IsConst>::
operator--()
{
	// --_node; TODO
	return *this;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>	MapIterator<T, IsConst>::
operator--(int)
{
	MapIterator<T, IsConst>	temp_it = *this;

	// --_node; TODO
	return temp_it;
}

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
operator MapIterator<T, true>()
{
	return MapIterator<T, true>(_node);
}

} // namespace ft

#endif
