/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:13:04 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/10 13:51:43 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tree.hpp"

using namespace ft;

int		main()
{
	Tree<int, void, void>	tree;

	tree.Add(5);
	tree.Add(5);
	tree.Add(6);
	tree.Add(3);
	tree.Print();
	return 0;
}
