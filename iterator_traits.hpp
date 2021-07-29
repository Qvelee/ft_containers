/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator_traits.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/29 16:17:52 by nelisabe          #+#    #+#             */
/*   Updated: 2021/07/29 16:50:17 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <iterator>

namespace ft
{

using std::random_access_iterator_tag;

template<typename Iterator>
struct iterator_traits
{
	typedef Iterator::difference_type	differrence_type;
	typedef Iterator::value_type		value_type;
	typedef Iterator::pointer			pointer;
	typedef Iterator::reference			reference;
	typedef Iterator::iterator_category	iterator_category;
};

template<typename T>
struct iterator_traits<T*>
{
	typedef ptrdiff_t					differrence_type;
	typedef T							value_type;
	typedef T*							pointer;
	typedef T&							reference;
	typedef random_access_iterator_tag	iterator_category;
};

template<typename T>
struct iterator_traits<const T*>
{
	typedef ptrdiff_t					differrence_type;
	typedef T							value_type;
	typedef const T*					pointer;
	typedef const T&					reference;
	typedef random_access_iterator_tag	iterator_category;
};
}

#endif
