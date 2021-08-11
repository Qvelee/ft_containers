/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:13:04 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/11 11:50:57 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "tree.hpp"

using namespace ft;

int		main()
{
	Tree<int, void, void>	tree;
	int		array[] = { 10, 7, 3, 8, 1, 5, 4, 6, 20, 15, 25, 13, 17, 16, 30, 29, 35 };

	for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
		tree.Add(array[i]);
	tree.PrintWidth();
	std::cout << "----------\n";
	tree.Print();
	std::cout << "----------\n";
	tree.Delete(20);
	tree.Print();
	// std::cout << "----------\n";
	// tree.Delete(7);
	// tree.Print();
	std::cout << "----------\n";
	tree.PrintWidth();

	return 0;
}
