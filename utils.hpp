/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/02 15:26:40 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/02 17:30:58 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

namespace ft
{

template<typename InputIterator1, typename InputIterator2>
bool	lexicographical_compare(InputIterator1 first_1, InputIterator1 last_1,
	InputIterator2 first_2, InputIterator2 last_2)
{
	while (first_1 != last_1)
	{
		if (first_2 == last_2 || *first_1 > *first_2)
			return false;
		else if (*first_1 < *first_2)
			return true;
		++first_1;
		++first_2;
	}
	return first_2 != last_2;
}

struct true_type { };

struct false_type { };

template<typename T>
struct is_integral
{
	typedef false_type	value;
};

template<>
struct is_integral<bool>
{
	typedef true_type	value;
};

template<>
struct is_integral<char>
{
	typedef true_type	value;
};

template<>
struct is_integral<wchar_t>
{
	typedef true_type	value;
};


template<>
struct is_integral<signed char>
{
	typedef true_type	value;
};


template<>
struct is_integral<short int>
{
	typedef true_type	value;
};


template<>
struct is_integral<int>
{
	typedef true_type	value;
};


template<>
struct is_integral<long int>
{
	typedef true_type	value;
};


template<>
struct is_integral<long long int>
{
	typedef true_type	value;
};


template<>
struct is_integral<unsigned char>
{
	typedef true_type	value;
};


template<>
struct is_integral<unsigned short int>
{
	typedef true_type	value;
};


template<>
struct is_integral<unsigned int>
{
	typedef true_type	value;
};


template<>
struct is_integral<unsigned long int>
{
	typedef true_type	value;
};


template<>
struct is_integral<unsigned long long int>
{
	typedef true_type	value;
};

} // namespace ft

#endif
