/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pair.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/04 12:51:23 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/12 16:30:20 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAIR_HPP
# define PAIR_HPP

# include "utils.hpp"

namespace ft
{

// make_pair function defined and implemented in this file below

template<typename T1, typename T2>
struct pair
{
	typedef T1	first_type;
	typedef T2	second_type;
	
	pair(); // default
	template<typename U, typename V>
	pair(const pair<U, V> &source); // copy
	pair(const first_type &fvalue, const second_type &svalue); // initialization
	~pair();

	pair	&operator=(const pair &source);

	T1	first;
	T2	second;
};

template<typename T1, typename T2>
pair<T1, T2>::
pair() : first(T1()), second(T2()) { }

template<typename T1, typename T2>
template<typename U, typename V>
pair<T1, T2>::
pair(const pair<U, V> &source) : first(source.first), second(source.second) { }

template<typename T1, typename T2>
pair<T1, T2>::
pair(const first_type &fvalue, const second_type &svalue) :
	first(fvalue), second(svalue) { }

template<typename T1, typename T2>
pair<T1, T2>::
~pair() { }

template<typename T1, typename T2>
pair<T1, T2>	&pair<T1, T2>::
operator=(const pair &source)
{
	first = source.first;
	second = source.second;
	return *this;
}

template<typename T1, typename T2>
bool
operator==(const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
bool
operator!=(const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
bool
operator< (const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
bool
operator<=(const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
bool
operator> (const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
bool
operator>=(const pair<T1, T2> &left, const pair<T1, T2> &rigth);

template<typename T1, typename T2>
pair<T1, T2>
make_pair(T1 first, T2 second)
{
	return pair<T1, T2>(first, second);
}

} // namespace ft

#endif
