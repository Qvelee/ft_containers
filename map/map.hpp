/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:43:56 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/10 11:54:50 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <functional>
# include <memory>
# include <cstddef>
# include <cstdlib>
# include "pair.hpp"
# include "tree.hpp"

namespace ft
{

template<typename key, typename T, typename Compare = std::less<key>,
	typename Allocator = std::allocator<pair<const key, T>>>
class map
{
	public:
		typedef key									key_type;
		typedef T									mapped_type;
		typedef	pair<const key_type, mapped_type>	value_type;
		typedef Compare								key_compare;
		typedef	Compare								value_compare; // ????
		typedef Allocator							allocator_type;
		typedef value_type&							reference;
		typedef const value_type&					const_reference;
		typedef value_type*							pointer;
		typedef const value_type*					const_pointer;
		typedef iterator; // TODO
		typedef const_iterator;
		typedef reverse_iterator;
		typedef const_reverse_iterator;
		typedef std::ptrdiff_t						difference_type;
		typedef	size_t								size_type;

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
		const_iterator			begin();
		iterator				end();
		const_iterator			end();
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
								equal_range(const key_type &key_) const;
		pair<const_iterator, const_iterator>
								equal_range(const key_type &key_) const;
		allocator_type			get_allocator() const;
	private:
		Tree<value_type, std::_Select1st<value_type>, Compare, Allocator>	tree;
};

} // namespace ft

#endif
