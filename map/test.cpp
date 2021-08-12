/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 13:13:04 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/12 18:25:06 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "map.hpp"
# include <functional>
# include <map>
# include "pair.hpp"

using namespace ft;

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

template<typename T>
struct Select
{
	T &operator()(T &x) const
	{
		return x;
	}
	const T &operator()(const T &x) const
	{
		return x;
	}
};

int		main()
{
	map<int, int>	mapp;

	std::cout << mapp.size() << std::endl;
	
	map<int, int>::iterator it = mapp.insert(make_pair(10, 10)).first;

	std::cout << mapp.insert(make_pair(10, 10)).second << std::endl;
	std::cout << it->first << std::endl;
	std::cout << it->second << std::endl;
	std::cout << "size: " << mapp.size() << std::endl;

	std::cout << mapp.insert(it, make_pair(30, 30))->first << std::endl;
	std::cout << "size: " << mapp.size() << std::endl;

	for (map<int, int>::iterator it = mapp.begin(); it != mapp.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";
	map<int, int>	map2;
	map2.insert(make_pair(100, 100));
	map2.insert(make_pair(50, 50));
	mapp.insert(map2.begin(), map2.end());

	for (map<int, int>::const_iterator it = mapp.begin(); it != mapp.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	mapp.erase(mapp.begin());
	for (map<int, int>::reverse_iterator it = mapp.rbegin(); it != mapp.rend(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	mapp.erase(mapp.begin(), --mapp.end());
	for (map<int, int>::const_reverse_iterator it = mapp.rbegin(); it != mapp.rend(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

 	std::cout << "Deleted: " << mapp.erase(100) << std::endl;
 	std::cout << "Deleted: " << mapp.erase(1010) << std::endl;
	for (map<int, int>::const_iterator it = mapp.begin(); it != mapp.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";
	mapp.swap(map2);
	for (map<int, int>::const_iterator it = mapp.begin(); it != mapp.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";
	for (map<int, int>::const_iterator it = map2.begin(); it != map2.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	mapp.clear();
	std::cout << "size: " << mapp.size() << std::endl;
	for (map<int, int>::const_iterator it = mapp.begin(); it != mapp.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";
	map2.insert(make_pair(200, 200));
	map2.insert(make_pair(400, 400));
	std::cout << map2.find(200)->first << std::endl;
	if (map2.find(10000) == map2.end())
		std::cout << "No element 10000\n";
	std::cout << "----\n";
	
	map<int, int>::const_iterator	it3 = map2.find(111);
	if (it3 == map2.end())
		std::cout << "No element 111\n";
	std::cout << "----\n";
	
	if (map2.count(200))
		std::cout << "200 found\n";
	if (map2.count(333))
		std::cout << "333 found\n";
	std::cout << "----\n";

	// Tree<int, Select<int>, std::less<int> >	tree;
	// int		array[] = { 10, 7, 3, 8, 1, 5, 4, 6, 20, 15, 25, 13, 17, 16, 30, 29, 35 };

	// std::cout << "Size: " << tree.Size() << std::endl;
	// for (int i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
	// 	tree.Add(array[i]);
	// std::cout << "----------\n";
	// tree.Print();
	
	
	// for (Tree<int, Select<int>, std::less<int> >::iterator it =
	// 	tree.begin(); it != tree.end(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-----------\n";
	// for (Tree<int, Select<int>, std::less<int> >::const_iterator it =
	// 	tree.begin(); it != tree.end(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-----------\n";
	// for (Tree<int, Select<int>, std::less<int> >::reverse_iterator it =
	// 	tree.rbegin(); it != tree.rend(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-----------\n";
	// for (Tree<int, Select<int>, std::less<int> >::const_reverse_iterator it =
	// 	tree.rbegin(); it != tree.rend(); ++it)
	// {
	// 	std::cout << *it << std::endl;
	// }

	return 0;
}
