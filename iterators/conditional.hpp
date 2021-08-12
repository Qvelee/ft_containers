/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditional.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/12 12:43:21 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/12 12:43:46 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONDITIONAL_HPP
# define CONDITIONAL_HPP

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

#endif
