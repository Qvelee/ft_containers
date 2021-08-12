/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:43:56 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/12 16:57:58 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <cstddef>
# include <cstdlib>
# include <limits>
# include "pair.hpp"
# include "tree.hpp"

namespace ft
{

template<typename Pair>
struct SelectFirst
{
	typename Pair::first_type &operator()(Pair &pair) const
	{
		return pair.first;
	}
	const typename Pair::first_type &operator()(const Pair &pair) const
	{
		return pair.first;
	}
};

template<typename key, typename T, typename Compare = std::less<key>,
	typename Allocator = std::allocator<pair<const key, T>>>
class map
{
	public:
		typedef key											key_type;
		typedef T											mapped_type;
		typedef	pair<const key_type, mapped_type>			value_type;
		typedef Compare										key_compare;
		typedef	Compare										value_compare; // ????
		typedef Allocator									allocator_type;
		typedef value_type&									reference;
		typedef const value_type&							const_reference;
		typedef value_type*									pointer;
		typedef const value_type*							const_pointer;
		typedef Tree<value_type, SelectFirst<value_type>, Compare, Allocator>
															base_tree;
		typedef typename base_tree::iterator				iterator;
		typedef typename base_tree::const_iterator			const_iterator;
		typedef typename base_tree::reverse_iterator		reverse_iterator;
		typedef typename base_tree::const_reverse_iterator	const_reverse_iterator;
		typedef std::ptrdiff_t								difference_type;
		typedef	size_t										size_type;

		explicit map(const key_compare &compare = key_compare(),
			const allocator_type &allocator = allocator_type()); // empty
		template<typename InputIterator>
		map(InputIterator first, InputIterator last,
			const key_compare &compare = key_compare(),
			const allocator_type &allocator = allocator_type()); // range
		map(const map &source); // copy
		~map();

		map			&operator=(const map &source);
		mapped_type &operator[](const key_type &key_);

		iterator				begin();
		const_iterator			begin() const;
		iterator				end();
		const_iterator			end() const;
		reverse_iterator		rbegin();
		const_reverse_iterator	rbegin() const;
		reverse_iterator		rend();
		const_reverse_iterator	rend() const;
		bool					empty() const;
		size_type				size() const;
		size_type				max_size() const;
		pair<iterator, bool>	insert(const value_type &value);
		iterator				insert(iterator position, const value_type &value);
		template<typename InputIterator>
		void					insert(InputIterator first, InputIterator last);
		void					erase(iterator position);
		size_type				erase(const key_type &key_);
		void					erase(iterator first, iterator last);
		void					swap(map &source);
		void					clear();
		key_compare				key_comp() const;
		value_compare			value_comp() const;
		iterator				find(const key_type &key_);
		const_iterator			find(const key_type &key_) const;
		size_type				count(const key_type &key_) const;
		iterator				lower_bound(const key_type &key_);
		const_iterator			lower_bound(const key_type &key_) const;
		iterator				upper_bound(const key_type &key_);
		const_iterator			upper_bound(const key_type &key_) const;
		pair<iterator, iterator>
								equal_range(const key_type &key_);
		pair<const_iterator, const_iterator>
								equal_range(const key_type &key_) const;
		allocator_type			get_allocator() const;
	private:
		base_tree	_tree;
};

template<typename key, typename T, typename Compare, typename Allocator>
map<key, T, Compare, Allocator>::
map(const key_compare &compare, const allocator_type &allocator)
{
	_tree = base_tree(compare, allocator);
}

template<typename key, typename T, typename Compare, typename Allocator>
template<typename InputIterator>
map<key, T, Compare, Allocator>::
map(InputIterator first, InputIterator last, const key_compare &compare,
	const allocator_type &allocator)
{
	_tree = base_tree(compare, allocator);
	insert(first, last);
}

template<typename key, typename T, typename Compare, typename Allocator>
map<key, T, Compare, Allocator>::
map(const map &source)
{
	*this = source;
}

template<typename key, typename T, typename Compare, typename Allocator>
map<key, T, Compare, Allocator>::
~map() { }

template<typename key, typename T, typename Compare, typename Allocator>
map<key, T, Compare, Allocator>	&map<key, T, Compare, Allocator>::
operator=(const map &source)
{
	if (this == &source)
		return *this;
	_tree = source._tree;
	return *this;
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::mapped_type	&map<key, T, Compare, Allocator>::
operator[](const key_type &key_)
{
	// Node<value_type>	*node;

	// node = _tree.Find(make_pair(key_, mapped_type()));
	// if (node != NULL)
	// {
	// 	return node->data.second;
	// }
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator
map<key, T, Compare, Allocator>::
begin()
{
	return _tree.begin();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_iterator
map<key, T, Compare, Allocator>::
begin() const
{
	return _tree.begin();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator
map<key, T, Compare, Allocator>::
end()
{
	return _tree.end();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_iterator
map<key, T, Compare, Allocator>::
end() const
{
	return _tree.end();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::reverse_iterator
map<key, T, Compare, Allocator>::
rbegin()
{
	return _tree.rbegin();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_reverse_iterator
map<key, T, Compare, Allocator>::
rbegin() const
{
	return _tree.rbegin();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::reverse_iterator
map<key, T, Compare, Allocator>::
rend()
{
	return _tree.rend();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_reverse_iterator
map<key, T, Compare, Allocator>::
rend() const
{
	return _tree.rend();
}

template<typename key, typename T, typename Compare, typename Allocator>
bool	map<key, T, Compare, Allocator>::
empty() const
{
	return !_tree.Size();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::size_type	map<key, T, Compare, Allocator>::
size() const
{
	return _tree.Size();
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::size_type	map<key, T, Compare, Allocator>::
max_size() const
{
	size_type	max_size = std::numeric_limits<size_type>::max() / sizeof(T);
	size_type	max_alloc = _tree.get_allocator().max_size();
	
	return std::min(max_size, max_alloc);
}

template<typename key, typename T, typename Compare, typename Allocator>
pair<typename map<key, T, Compare, Allocator>::iterator, bool>
map<key, T, Compare, Allocator>::
insert(const value_type &value)
{
	return _tree.Add(value);
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator map<key, T, Compare, Allocator>::
insert(iterator, const value_type &value)
{
	return _tree.Add(value).first;
}

template<typename key, typename T, typename Compare, typename Allocator>
template<typename InputIterator>
void	map<key, T, Compare, Allocator>::
insert(InputIterator first, InputIterator last)
{
	if (first == last)
		return;
	for (; first != last; ++first)
		_tree.Add(*first);
}

template<typename key, typename T, typename Compare, typename Allocator>
void	map<key, T, Compare, Allocator>::
erase(iterator position)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::size_type	map<key, T, Compare, Allocator>::
erase(const key_type &key_)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
void	map<key, T, Compare, Allocator>::
erase(iterator first, iterator last)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
void	map<key, T, Compare, Allocator>::
swap(map &source)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
void	map<key, T, Compare, Allocator>::
clear()
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::key_compare	map<key, T, Compare, Allocator>::
key_comp() const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::value_compare	map<key, T, Compare, Allocator>::
value_comp() const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator	map<key, T, Compare, Allocator>::
find(const key_type &key_)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_iterator	map<key, T, Compare, Allocator>::
find(const key_type &key_) const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::size_type	map<key, T, Compare, Allocator>::
count(const key_type &key_) const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator	map<key, T, Compare, Allocator>::
lower_bound(const key_type &key_)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_iterator	map<key, T, Compare, Allocator>::
lower_bound(const key_type &key_) const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::iterator	map<key, T, Compare, Allocator>::
upper_bound(const key_type &key_)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::const_iterator	map<key, T, Compare, Allocator>::
upper_bound(const key_type &key_) const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
pair<typename map<key, T, Compare, Allocator>::iterator,
	typename map<key, T, Compare, Allocator>::iterator>
map<key, T, Compare, Allocator>::
equal_range(const key_type &key_)
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
pair<typename map<key, T, Compare, Allocator>::const_iterator,
	typename map<key, T, Compare, Allocator>::const_iterator>
map<key, T, Compare, Allocator>::
equal_range(const key_type &key_) const
{
	// TODO
}

template<typename key, typename T, typename Compare, typename Allocator>
typename map<key, T, Compare, Allocator>::allocator_type	map<key, T, Compare, Allocator>::
get_allocator() const
{
	return _tree.get_allocator();
}

} // namespace ft

#endif
