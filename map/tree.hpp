/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/09 12:20:00 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/10 14:53:42 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_HPP
# define TREE_HPP

# include <cstdlib>
# include <functional>
# include <memory>
# include <iostream> // DELETE

namespace ft
{

template<typename T>
struct Node
{
	Node(const T &data_, Node *parent_)
	{
		data = data_;
		parent = parent_;
		left = NULL;
		rigth = NULL;
	}
	~Node() { }

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
		typedef Data		data_type;
		typedef size_t		size_type;
		typedef Allocator	allocator_type;

		Tree();
		Tree(const Tree &source);
		~Tree();
	
		Tree	&operator=(const Tree &source);

		void			Add(const data_type &data);
		void			Delete(const data_type &data);
		Node<data_type>	*Find(const data_type &data);
		void			Print();
	private:
		void			_Print(Node<data_type> *node);
		Node<data_type>	*_Add(Node<data_type> *node, Node<data_type> *parent,
			const data_type &data);
		Node<data_type>	*_Delete(Node<data_type> *node, Node<data_type> *parent,
			const data_type &data);
		void			_Destroy(Node<data_type> *node);

		size_type		_size;
		Node<data_type>	*_tree;
		allocator_type	_allocator;
};

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>::
Tree()
{
	_size = 0;
	_tree = NULL;
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
	_Destroy(_tree);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
_Destroy(Node<data_type> *node)
{
	if (node == NULL)
		return;
	_Destroy(node->left);
	_Destroy(node->rigth);
	delete node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Tree<Data, Key_from_data, Compare, Allocator>
&Tree<Data, Key_from_data, Compare, Allocator>::
operator=(const Tree &source)
{
	// TODO
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Add(const data_type &data)
{
	_tree = _Add(_tree, NULL, data);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
_Add(Node<data_type> *node, Node<data_type> *parent, const data_type &data)
{
	if (node == NULL)
	{
		node = new Node<data_type>(data, parent);
		return node;
	}
	if (data < node->data) // TODO add compare function
		node->left = _Add(node->left, node, data); 
	if (data > node->data) // TODO add compare function
		node->rigth = _Add(node->rigth, node, data);
	return node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Delete(const data_type &data)
{
	_tree = _Delete(_tree, NULL, data);
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
_Delete(Node<data_type> *node, Node<data_type> *parent, const data_type &data)
{
	if (node == NULL)
		return node;
	if (data < node->data)
		node->left = _Delete(node->left, node, data);
	else if (data > node->data)
		node->rigth = _Delete(node->rigth, node, data);
	else if (node->left == NULL || node->rigth == NULL)
	{
		Node<data_type>	*temp;
		
		temp = node->left ? node->left : node->rigth;
		temp->parent = parent;
		delete node;
		return temp;
	}
	return node;
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
Node<Data>	*Tree<Data, Key_from_data, Compare, Allocator>::
Find(const data_type &data)
{
	
}

template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
Print()
{
	_Print(_tree);
}
	
template<typename Data, typename Key_from_data,
	typename Compare, typename Allocator>
void	Tree<Data, Key_from_data, Compare, Allocator>::
_Print(Node<data_type> *node)
{
	if (node == NULL)
		return;
	_Print(node->left);
	std::cout << "Data: " << node->data << ' ';
	std::cout << "Parent: ";
	if (node->parent)
		std::cout << node->parent->data << std::endl;
	else
		std::cout << "root" << std::endl;
	_Print(node->rigth);
}

} // namespace ft

#endif
