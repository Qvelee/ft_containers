/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_iterator.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/11 14:10:59 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/11 19:06:10 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_ITERATOR_HPP
# define MAP_ITERATOR_HPP

# include "iterator_traits.hpp"
# include "tree.hpp"

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

template<typename T>
struct TreeBounds;

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
		typedef TreeBounds<conditional_t>			tree_bounds;

		MapIterator();
		MapIterator(conditional_t *node,  conditional_t *end, tree_bounds *min_max_nodes);
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
		conditional_t	*_end;
		tree_bounds		*_min_max_nodes;
};

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
MapIterator() : _node(NULL), _end(NULL), _min_max_nodes(NULL) { }

template<typename T, bool IsConst>
MapIterator<T, IsConst>::
MapIterator(conditional_t *node, conditional_t *end, tree_bounds *min_max_nodes) :
	_node(node), _end(end), _min_max_nodes(min_max_nodes) { }

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
	_min_max_nodes = source._min_max_nodes;
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
	// if current node basn't any bigger (rigth) child
	//	then, if it is biggest tree element, we reached end.
	//	else we need to go back from this node to it's parents.
	//	but we must skip already passed and returned nodes, so:
	//	while going back we need to check from where we came, if
	//	previous node was rigth child we need to go to next parent,
	//	because we already returned this parent later. if prev. node
	//	was left child, we need to stop here, because we was here, but
	//	didn't return this parent.
	if (_node->rigth == NULL)
	{
		if (_node == _min_max_nodes->biggest)	
		{
			_node = _end;
			return *this;
		}
		for (; _node != _node->parent->left; _node = _node->parent);
		_node = _node->parent;
	}
	else
	{
		// otherwise, if curent node has rigth child, we need to go
		//	to it and them find smalles (most left) node in this 
		//	child tree.
		_node = _node->rigth;
		for (; _node->left != NULL; _node = _node->left);
	}
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
	// --_node; 
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
