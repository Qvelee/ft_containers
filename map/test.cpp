/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:13:04 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/10 14:52:29 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tree.hpp"

using namespace ft;

int		main()
{
	Tree<int, void, void>	tree;
	int		array[] = {10, 7, 3, 8, 1, 4, 20, 15, 25, 13, 17, 16, 30, 29, 35 };

	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
		tree.Add(array[i]);
	tree.Print();
	// std::cout << "----------\n";
	// tree.Print();
	return 0;
}
