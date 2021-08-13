/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:20:00 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/13 15:32:31 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <cstdlib>
# include <functional>
# include <memory>
# include <iostream>
# include "map_iterator.hpp"
# include "reverse_iterator.hpp"
# include "pair.hpp"

namespace ft
{

template<typename T, bool IsConst = false>
class MapIterator;

template<typename Iterator>
class ReverseIterator;

template<typename T>
struct TreeBounds
{
	TreeBounds() : biggest(NULL), smallest(NULL) { }
	TreeBounds(const TreeBounds &source) { *this = source; }
	
	TreeBounds	&operator=(const TreeBounds &source)
	{
		if (this == &source)
			return *this;
		biggest = source.biggest;
		smallest = source.smallest;
		return *this;
	}
	
	T	*biggest;
	T	*smallest;
};

template<typename T>
struct Node
{
	Node() : data(T()), parent(NULL), left(NULL), rigth(NULL) { }
	Node(const T &data_, Node *parent_) : data(data_), parent(parent_),
		left(NULL), rigth(NULL) { }
	Node(const Node &source) : data(source.data), parent(source.parent),
		left(source.left), rigth(source.rigth) { }
	~Node() { }

	typedef T data_type;

	T		data;
	Node	*parent;
	Node	*left;
	Node	*rigth;
};

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator = std::allocator<Data> >
class Tree
{
	public:
		typedef Data							data_type;
		typedef size_t							size_type;
		typedef Key_from_data					get_key;
		typedef Compare							compare_keys;
		typedef Node<data_type>					node_type;
		typedef	TreeBounds<node_type>			tree_bounds;
		typedef const TreeBounds<node_type>		const_tree_bounds;
		typedef typename Allocator::template rebind<node_type>::other
												allocator_type;
		typedef MapIterator<node_type>			iterator;
		typedef MapIterator<node_type, true>	const_iterator;
		typedef ReverseIterator<iterator>		reverse_iterator;
		typedef ReverseIterator<const_iterator>	const_reverse_iterator;

		Tree(const compare_keys &compare = compare_keys(),
			const allocator_type &allocator = allocator_type());
		Tree(const Tree &source);
		~Tree();
	
		Tree	&operator=(const Tree &source);

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;
		pair<iterator, bool>	Add(const data_type &data);
		void					Delete(const data_type &data);
		iterator				Find(const data_type &data);
		const_iterator			Find(const data_type &data) const;
		void					Print();
		size_type				Size() const;
		void					swap(Tree &source);
		void					clear();
		iterator				lower_bound(const data_type &data);
		const_iterator			lower_bound(const data_type &data) const;
		iterator				upper_bound(const data_type &data);
		const_iterator			upper_bound(const data_type &data) const;
		pair<iterator, iterator>
								equal_range(const data_type &data);
		pair<const_iterator, const_iterator>
								equal_range(const data_type &data) const;
		allocator_type			get_allocator() const;
	private:
		void		Print(node_type *node);
		void		PrintWidth(node_type *node);
		node_type	*Add(node_type *node, node_type *parent,
			const data_type &data, pair<iterator, bool>	&inserted_element);
		node_type	*Delete(node_type *node, node_type *parent,
			const data_type &data);
		node_type	*Find(node_type *node, const data_type &data) const;
		void		UpdateMinMaxNodes();
		void		Destroy(node_type *node);
		void		FreeNode(node_type *node);

		size_type		_size;
		node_type		*_tree;
		tree_bounds		_min_max_nodes;
		node_type		*_end;
		node_type		_empty_node;
		allocator_type	_allocator;
		compare_keys	_compare;
		get_key			_get_key;
};

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>::
Tree(const compare_keys &compare,const allocator_type &allocator) :
	_size(0), _tree(NULL), _end(NULL)
{
	_compare = compare;
	_allocator = allocator;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>::
Tree(const Tree &source)
{
	*this = source;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>::
~Tree()
{
	Destroy(_tree);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Destroy(node_type *node)
{
	if (node == NULL)
		return;
	Destroy(node->left);
	Destroy(node->rigth);
	FreeNode(node);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>
&Tree<Data, Key_from_data, Compare, Allocator>::
operator=(const Tree &source)
{
	if (this == &source)
		return *this;
	Destroy(_tree);
	_size = 0;
	_tree = NULL;
	for (Tree<Data, Key_from_data, Compare, Allocator>::const_iterator it = source.begin();
		it != source.end(); ++it)
		Add(*it);
	return *this;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
begin()
{
	if (_tree != NULL)
		return iterator(_min_max_nodes.smallest, _end, &_min_max_nodes);
	return iterator(_end, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
begin() const
{
	if (_tree != NULL)
		return const_iterator(_min_max_nodes.smallest, _end, &_min_max_nodes);
	return const_iterator(_end, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
end()
{
	return iterator(_end, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
end() const
{
	return const_iterator(_end, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::reverse_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
rbegin()
{
	return reverse_iterator(end());
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_reverse_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
rbegin() const
{
	return const_reverse_iterator(end());
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::reverse_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
rend()
{
	return reverse_iterator(begin());
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_reverse_iterator
	Tree<Data, Key_from_data, Compare, Allocator>::
rend() const
{
	return const_reverse_iterator(begin());
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
pair<typename Tree<Data, Key_from_data, Compare, Allocator>::iterator, bool>
Tree<Data, Key_from_data, Compare, Allocator>::
Add(const data_type &data)
{
	pair<iterator, bool>	inserted_element;
	
	_tree = Add(_tree, NULL, data, inserted_element);
	UpdateMinMaxNodes();
	return inserted_element;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Add(node_type *node, node_type *parent, const data_type &data,
	pair<iterator, bool> &inserted_element)
{
	if (node == NULL)
	{
		node = _allocator.allocate(sizeof(node_type));
		_allocator.construct(node, node_type(data, parent));
		++_size;
		inserted_element.first = iterator(node, _end, &_min_max_nodes);
		inserted_element.second = true;
		return node;
	}
	if (_compare(_get_key(data), _get_key(node->data)))
		node->left = Add(node->left, node, data, inserted_element);
	else if (_compare(_get_key(node->data), _get_key(data)))
		node->rigth = Add(node->rigth, node, data, inserted_element);
	else // element equal
	{
		inserted_element.first = iterator(node, _end, &_min_max_nodes);
		inserted_element.second = false;
	}
	return node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Delete(const data_type &data)
{
	_tree = Delete(_tree, NULL, data);
	UpdateMinMaxNodes();
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Delete(node_type *node, node_type *parent, const data_type &data)
{
	if (node == NULL)
		return node;
	if (_compare(_get_key(data), _get_key(node->data)))
		node->left = Delete(node->left, node, data);
	else if (_compare(_get_key(node->data), _get_key(data)))
		node->rigth = Delete(node->rigth, node, data);
	else if (node->left == NULL || node->rigth == NULL) // if del. element has 0 or 1 child
	{
		node_type	*temp;
		
		temp = node->left ? node->left : node->rigth;
		if (temp != NULL)
			temp->parent = parent;
		--_size;
		FreeNode(node);
		return temp;
	}
	else // if del. element has 2 childs
	{
		node_type	*child = node->rigth;

		for (; child->left != NULL; child = child->left);
		if (child->parent != node)
		{
			child->parent->left = child->rigth;
			child->rigth = node->rigth;
		}
		child->left = node->left;
		child->parent = node->parent;
		if (child->left != NULL)
			child->left->parent = child;
		if (child->rigth != NULL)
			child->rigth->parent = child;
		if (node->parent != NULL && node->parent->rigth == node)
			node->parent->rigth = child;
		else if (node->parent != NULL)
			node->parent->left = child;
		--_size;
		FreeNode(node);
		return child;
	}
	return node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
UpdateMinMaxNodes()
{
	if (_tree == NULL)
	{
		_min_max_nodes.biggest = NULL;
		_min_max_nodes.smallest = NULL;
		return;
	}
	node_type	*temp;
	for (temp = _tree; temp->rigth != NULL; temp = temp->rigth);
	_min_max_nodes.biggest = temp;
	for (temp = _tree; temp->left != NULL; temp = temp->left);
	_min_max_nodes.smallest = temp;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::iterator
Tree<Data, Key_from_data, Compare, Allocator>::
Find(const data_type &data)
{
	node_type	*finded_node = Find(_tree, data);

	if (finded_node == NULL)
		return end();
	return iterator(finded_node, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator
Tree<Data, Key_from_data, Compare, Allocator>::
Find(const data_type &data) const
{
	node_type	*finded_node = Find(_tree, data);

	if (finded_node == NULL)
		return end();
	return const_iterator(finded_node, _end, &_min_max_nodes);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Find(node_type *node, const data_type &data) const
{
	if (node == NULL)
		return NULL;
	if (_compare(_get_key(data), _get_key(node->data)))
		node = Find(node->left, data);
	else if (_compare(_get_key(node->data), _get_key(data)))
		node = Find(node->rigth, data);
	return node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Print()
{
	Print(_tree);
}
	
template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Print(node_type *node)
{
	if (node == NULL)
		return;
	Print(node->left);
	std::cout << "Data: " << node->data << ' ';
	std::cout << "Parent: ";
	if (node->parent)
		std::cout << node->parent->data << std::endl;
	else
		std::cout << "root" << std::endl;
	Print(node->rigth);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::size_type
Tree<Data, Key_from_data, Compare, Allocator>::
Size() const
{
	return _size;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
swap(Tree &source)
{
	node_type	*temp_node_pointer;
	tree_bounds	temp_bounds;

	temp_node_pointer = _tree;
	_tree = source._tree;
	source._tree = temp_node_pointer;
	_size ^= source._size; // XOR swap
	source._size ^= _size;
	_size ^= source._size;
	temp_bounds = _min_max_nodes;
	_min_max_nodes = source._min_max_nodes;
	source._min_max_nodes = temp_bounds;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
clear()
{
	Destroy(_tree);
	_tree = NULL;
	_size = 0;	
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::iterator
Tree<Data, Key_from_data, Compare, Allocator>::
lower_bound(const data_type &data)
{
	iterator it;

	for (it = begin(); it != end(); ++it)
		if (!_compare(_get_key(*it), _get_key(data)))
			break ;
	return it;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator
Tree<Data, Key_from_data, Compare, Allocator>::
lower_bound(const data_type &data) const
{
	const_iterator it;

	for (it = begin(); it != end(); ++it)
		if (!_compare(_get_key(*it), _get_key(data)))
			break ;
	return it;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::iterator
Tree<Data, Key_from_data, Compare, Allocator>::
upper_bound(const data_type &data)
{
	iterator it;

	for (it = begin(); it != end(); ++it)
		if (_compare(_get_key(data), _get_key(*it)))
			break ;
	return it;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator
Tree<Data, Key_from_data, Compare, Allocator>::
upper_bound(const data_type &data) const
{
	const_iterator it;

	for (it = begin(); it != end(); ++it)
		if (!_compare(_get_key(data), _get_key(*it)))
			break ;
	return it;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
pair<typename Tree<Data, Key_from_data, Compare, Allocator>::iterator,
	typename Tree<Data, Key_from_data, Compare, Allocator>::iterator>
Tree<Data, Key_from_data, Compare, Allocator>::
equal_range(const data_type &data)
{
	iterator	it_upper = upper_bound(data);
	iterator	it_lower = lower_bound(data);

	if (it_upper == end())
		it_upper = it_lower;
	if (it_lower == end())
	{		
		it_lower = iterator(&_empty_node, _end, &_min_max_nodes);
		it_upper = it_lower;
	}
	return make_pair(it_lower, it_upper);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
pair<typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator,
	typename Tree<Data, Key_from_data, Compare, Allocator>::const_iterator>
Tree<Data, Key_from_data, Compare, Allocator>::
equal_range(const data_type &data) const
{
	const_iterator	it_upper = upper_bound(data);
	const_iterator	it_lower = lower_bound(data);

	if (it_upper == end())
		it_upper = it_lower;
	if (it_lower == end())
	{		
		it_lower = const_iterator(&_empty_node, _end, &_min_max_nodes);
		it_upper = it_lower;
	}
	return make_pair(it_lower, it_upper);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
FreeNode(node_type *node)
{
	_allocator.destroy(node);
	_allocator.deallocate(node, sizeof(node));
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
typename Tree<Data, Key_from_data, Compare, Allocator>::allocator_type
Tree<Data, Key_from_data, Compare, Allocator>::
get_allocator() const
{
	return _allocator;
}

} // namespace ft

#endif
