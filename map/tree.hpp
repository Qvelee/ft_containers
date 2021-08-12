/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:20:00 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/12 12:06:53 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <cstdlib>
# include <functional>
# include <memory>
# include <iostream>
# include "map_iterator.hpp"

namespace ft
{

template<typename T>
struct TreeBounds
{
	TreeBounds() : biggest(NULL), smallest(NULL) { }
	
	T	*biggest;
	T	*smallest;
};

template<typename T>
struct Node
{
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

	private:
		Node() { }
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
		// TODO add reverse

		Tree();
		Tree(const Tree &source);
		~Tree();
	
		Tree	&operator=(const Tree &source);

		iterator		begin();
		const_iterator	begin() const;
		iterator		end();
		const_iterator	end() const;
		// TODO and reverse
		void			Add(const data_type &data);
		void			Delete(const data_type &data);
		node_type		*Find(const data_type &data);
		node_type		*Find(node_type *node, const data_type &data);
		void			Print();
		size_type		Size();

		void	PrintMinMax()
		{
			std::cout << _min_max_nodes.biggest->data << std::endl;
			std::cout << _min_max_nodes.smallest->data << std::endl;
		}
	private:
		void		Print(node_type *node);
		void		PrintWidth(node_type *node);
		node_type	*Add(node_type *node, node_type *parent,
			const data_type &data);
		node_type	*Delete(node_type *node, node_type *parent,
			const data_type &data);
		void		UpdateMinMaxNodes();
		void		Destroy(node_type *node);
		void		FreeNode(node_type *node);

		size_type		_size;
		node_type		*_tree;
		tree_bounds		_min_max_nodes;
		node_type		*_end;
		allocator_type	_allocator;
		compare_keys	_compare;
		get_key			_get_key;
};

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>::
Tree()
{
	_size = 0;
	_tree = NULL;
	_end = NULL;
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
void	Tree<Data, Key_from_data, Compare, Allocator>::
Add(const data_type &data)
{
	_tree = Add(_tree, NULL, data);
	UpdateMinMaxNodes();
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Add(node_type *node, node_type *parent, const data_type &data)
{
	if (node == NULL)
	{
		node = _allocator.allocate(sizeof(node_type));
		_allocator.construct(node, node_type(data, parent));
		++_size;
		return node;
	}
	if (_compare(_get_key(data), _get_key(node->data)))
		node->left = Add(node->left, node, data);
	else if (_compare(_get_key(node->data), _get_key(data)))
		node->rigth = Add(node->rigth, node, data);
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
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Find(const data_type &data)
{
	return Find(_tree, data);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Find(node_type *node, const data_type &data)
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
Size()
{
	return _size;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
FreeNode(node_type *node)
{
	_allocator.destroy(node);
	_allocator.deallocate(node, sizeof(node));
}

} // namespace ft

#endif
