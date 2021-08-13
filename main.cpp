/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:39:51 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/13 11:32:18 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <vector>
# include <map>
# include <iostream>
# include <string>
# include <unistd.h>
# include "vector.hpp"
# include "stack.hpp"
# include "map.hpp"

#ifndef MODE
#define MODE 0
#endif

#define YELLOW	"\033[33m"
#define RED		"\033[31m"
#define RESET	"\033[0m"
#define BOLD	"\033[1m"
#define GREEN	"\033[32m"

#if MODE
	using std::vector;
	using std::swap;
	using std::map;
	using std::pair;
	using std::make_pair;
#else
	using ft::vector;
	using ft::swap;
	using ft::map;
	using ft::pair;
	using ft::make_pair;
#endif

using std::cout;
using std::endl;
using std::string;

template<typename T>
void	print_state(const vector<T> &vec);
void	print_test(const string &);
void	print_step(const string &);

void	TestStack()
{
	ft::stack<int>	stck;

	cout << "stack empty?: " << std::boolalpha << stck.empty() << endl;
	stck.push(20);
	stck.push(10);
	
	cout << "last element: " << stck.top() << endl;
	stck.pop();
	
	cout << "last element: " << stck.top() << endl;
	stck.push(30);
	stck.push(40);
	cout << "size: " << stck.size() << endl;
	
	ft::stack<int>	stck2;
	stck2.push(20);
	stck2.push(30);
	stck2.push(40);
	cout << "is stacks ==?: " << std::boolalpha << (stck == stck2) << endl;
	cout << "is stacks !=?: " << std::boolalpha << (stck != stck2) << endl;
	stck2.push(50);
	cout << "is stacks <?: " << std::boolalpha << (stck < stck2) << endl;
	cout << "is stacks >?: " << std::boolalpha << (stck > stck2) << endl;
	cout << "is stacks <=?: " << std::boolalpha << (stck <= stck2) << endl;
	cout << "is stacks >=?: " << std::boolalpha << (stck >= stck2) << endl;
}

void	TestOperators()
{
	print_test("TestOperator");
	vector<int>	vec;
	vector<int>	vec2;

	vec.assign(10, 100);
	vec2.assign(9, 100);
	cout << "is vectors ==?: " << std::boolalpha << (vec == vec2) << endl;
	cout << "is vectors !=?: " << std::boolalpha << (vec != vec2) << endl;
	cout << "is vectors <?: " << std::boolalpha << (vec < vec2) << endl;
	cout << "is vectors <=?: " << std::boolalpha << (vec <= vec2) << endl;
	cout << "is vectors >?: " << std::boolalpha << (vec > vec2) << endl;
	cout << "is vectors >=?: " << std::boolalpha << (vec >= vec2) << endl;
}

void	TestOther()
{
	print_test("TestOther");
	vector<int>	vec;
	
	print_step("Test []");
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	cout << "front: " << vec.front() << endl;
	cout << "end: " << vec.back() << endl;
	cout << "vec: ";
	for (size_t i = 0; i < vec.size(); ++i)
		cout << vec[i] << ' ';
	cout << '\n';

	print_step("Test at");
	vector<int>	vec2;

	vec2.push_back(6);
	vec2.push_back(7);
	vec2.push_back(8);
	vec2.push_back(9);
	vec2.push_back(10);
	cout << "vec2: ";
	for (size_t i = 0; i < vec.size(); ++i)
		cout << vec.at(i) << ' ';
	cout << '\n';
	try
	{
		vec.at(10000);
	}
	catch(const std::exception& e)
	{
		std::cerr << "Error: " << e.what() << '\n';
	}
	cout << endl;
	print_step("Test swap");
	print_step("1 swap");
	
	vec.insert(vec.begin(), 10, 1110);
	cout << "vec: \n";
	print_state(vec);
	cout << "vec2: \n";
	print_state(vec2);
	
	vector<int>::iterator it1 = vec.begin();
	vector<int>::iterator it2 = vec2.begin();
	cout << "it vec: " << *it1 << " | it vec2: " << *it2 << endl;
	vec.swap(vec2);

	print_step("2 swap");
	cout << "vec: \n";
	print_state(vec);
	cout << "vec2: \n";
	print_state(vec2);

	cout << "it vec: " << *it1 << " | it vec2: " << *it2 << endl;

	print_step("3 swap");
	swap(vec, vec2);
	cout << "vec: \n";
	print_state(vec);
	cout << "vec2: \n";
	print_state(vec2);
	cout << "it vec: " << *it1 << " | it vec2: " << *it2 << endl;
}

void	TestElementsMemory()
{
	print_test("TestElementsMemory");
	vector<int>	vec;
	
	cout << "Vector max size: " << vec.max_size() << endl;
	print_state(vec);

	print_step("Push Pop to vec");
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	print_state(vec);

	vec.pop_back();
	vec.pop_back();
	print_state(vec);

	print_step("Insert to vec");
	vector<int> insertme(4, 20);
	vec.insert(vec.begin() + 2, 30);
	print_state(vec);

	vec.insert(vec.begin() + 3, 5, 110);
	print_state(vec);

	vec.insert(vec.end() - 2, insertme.begin(), insertme.end());
	print_state(vec);

	print_step("Insert to vec2");
	vector<int>	vec2;
	vec2.insert(vec2.begin(), 2);
	print_state(vec2);

	vec2.insert(vec2.begin(), 3);
	print_state(vec2);

	vec2.insert(vec2.begin() + 1, 4, 250);
	print_state(vec2);

	print_step("Erase from vec2");
	vec2.erase(vec2.begin() + 1);
	print_state(vec2);

	vec2.erase(vec2.end() - 3, vec2.end());
	print_state(vec2);

	vec2.erase(vec2.begin(), vec2.end());
	print_state(vec2);

	print_step("Resize vec2");
	vec2.resize(4);
	print_state(vec2);

	vec2.resize(7, 13221);
	print_state(vec2);

	vec2.resize(15);
	print_state(vec2);
}

void	TestBeginEndIterators()
{
	print_test("TestBeginEndIterators");
	vector<int>	vec;

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	vec.push_back(6);
	vec.push_back(7);	
	
	cout << "created vector:\n";
	print_state(vec);
	
	vector<int>::iterator	it_begin = vec.begin();
	vector<int>::iterator	it_end = vec.end();

	cout << "3 index element: " << *(it_begin + 3) << endl;
	it_begin += 4;
	cout << "4 index element: " << *it_begin << endl;
	it_begin - 4;
	cout << "1 index element: " << *it_begin << endl;
	it_begin -= 4;
	cout << "0 index element: " << *it_begin << endl;
	cout << "itrator it_begin < it_begin + 5: ";
	cout << std::boolalpha << (it_begin < it_begin + 5) << endl;
	cout << "itrator it_begin > it_end: ";
	cout << std::boolalpha << (it_begin > it_end) << endl;
	cout << "itrator it_begin == it_end - 3: ";
	cout << std::boolalpha << (it_begin == it_end - 3) << endl;
	cout << "itrator it_begin != it_end: ";
	cout << std::boolalpha << (it_begin != it_end) << endl;
	cout << "it_begin[0]: " << it_begin[0] << endl;
	cout << "it_begin++ : " << *(it_begin++) << endl;
	cout << "++it_begin: " << *(++it_begin) << endl;
	
	cout << "printing vector using const iterators: " << endl;
	for (vector<int>::const_iterator it = vec.begin(); it < vec.end(); ++it)
		std::cout << *it << ' ';
	cout << endl;

	cout << "printing vector using reverse iterators: " << endl;
	for (vector<int>::reverse_iterator it = vec.rbegin(); it < vec.rend(); ++it)
		std::cout << *it << ' ';
	cout << endl;
	
	cout << "printing vector using const reverse iterators: " << endl;
	for (vector<int>::const_reverse_iterator it = vec.rbegin(); it - vec.rend(); ++it)
		std::cout << *it << ' ';
	cout << endl;

	cout << "finish\n\n";
}

void	TestCopyConstructor()
{
	print_test("TestCopyConstructor");
	vector<float>	initvec(5, 255.35);
	vector<float>	vec(initvec);

	print_state(vec);
	cout << "finish\n\n";
}

void	TestRangeConstructor()
{
	print_test("TestRangeConstructor");
	std::vector<int>	initvec(5, 100);
	vector<int>	vec(initvec.begin() + 1, initvec.end());

	print_state(vec);
	cout << "finish\n\n";
}

void	TestFillConstructor()
{
	print_test("TestFillConstructor");
	vector<int>	vec(5, 11);

	print_state(vec);
	cout << "finish\n\n";
}

void	TestDefaultConstructor()
{
	print_test("TestDefaultConstructor");
	vector<int>	vec;

	print_state(vec);
	cout << "finish\n\n";
}

template<typename T>
void	print_state(const vector<T> &vec)
{
	cout << "-- state of vector --\n";
	cout << "size: " << vec.size() << endl;
	cout << "capacity: " << vec.capacity() << endl;
	
	cout << "vector: ";
	for (typename vector<T>::const_iterator it = vec.begin();
		it < vec.end(); ++it)
	cout << *it << ' ';
	cout << "END\n";
	cout << endl;
}

void	print_test(const string &str)
{
	cout << YELLOW << str << RESET << "\n\n";
}

void	print_step(const string &str)
{
	cout << GREEN << str << RESET << "\n\n";
}

void	hello()
{
	cout << "Testing ";
	if (MODE)
		cout << BOLD << RED << "std" << RESET;
	else
		cout << BOLD << RED << "ft" << RESET;
	cout << "!\n" << endl;
	sleep(1);
}

void	TestMoreMap()
{
	map<int, int>	map1;
	
	print_step("Testing lower upper bounds, equal");
	int		array[] = { 10, 7, 3, 8, 1, 5, 4, 6, 20, 15, 25, 13, 17, 16, 30, 29, 35 };
// 
	std::cout << "Size: " << map1.size() << std::endl;
	for (size_t i = 0; i < sizeof(array) / sizeof(array[0]); ++i)
		map1.insert(make_pair(array[i], array[i]));
	std::cout << "Size: " << map1.size() << std::endl;

	map<int, int>::iterator itlower = map1.lower_bound(5);
	map<int, int>::const_iterator itlowerconst = map1.lower_bound(5);
	std::cout << itlower->first << std::endl;
	std::cout << itlowerconst->first << std::endl;
	std::cout << "----------\n";

	map<int, int>::iterator itupper = map1.upper_bound(35);
	map<int, int>::const_iterator itupperconst = map1.lower_bound(20);
	if (itupper == map1.end())
		std::cout << "No element upper 35\n";
	std::cout << itupperconst->first << std::endl;
	std::cout << "----------\n";

	pair<map<int, int>::iterator, map<int, int>::iterator>	range = map1.equal_range(6);
	std::cout << range.first->first << ' ';
	std::cout << range.second->first << std::endl;
	std::cout << "----------\n";

	print_step("Testing key and value compare");
	map<int, int>::key_compare comp = map1.key_comp();

	for (map<int, int>::iterator it = map1.begin(); it != map1.end(); ++it)
		if (!comp(it->first, 10))
			std::cout << it->first << ' ';
	std::cout << std::endl;

	map<int, int>::value_compare val_comp = map1.value_comp();
	for (map<int, int>::iterator it = map1.begin(); it != map1.end(); ++it)
		if (!val_comp(*it, make_pair(10, 10)))
			std::cout << it->first << ' ';
	std::cout << std::endl;
}

void	TestMap()
{
	map<int, int>	mymap;
	
	print_step("Testing insert");
	std::cout << mymap.size() << std::endl;
	
	map<int, int>::iterator it = mymap.insert(make_pair(10, 10)).first;

	std::cout << mymap.insert(make_pair(10, 10)).second << std::endl;
	std::cout << it->first << std::endl;
	std::cout << it->second << std::endl;
	std::cout << "size: " << mymap.size() << std::endl;

	std::cout << mymap.insert(it, make_pair(30, 30))->first << std::endl;
	std::cout << "size: " << mymap.size() << std::endl;

	for (map<int, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	map<int, int>	map2;
	map2.insert(make_pair(100, 100));
	map2.insert(make_pair(50, 50));
	mymap.insert(map2.begin(), map2.end());

	for (map<int, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	print_step("Testing erase and iterators");
	mymap.erase(mymap.begin());
	for (map<int, int>::reverse_iterator it = mymap.rbegin(); it != mymap.rend(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	mymap.erase(mymap.begin(), --mymap.end());
	for (map<int, int>::const_reverse_iterator it = mymap.rbegin(); it != mymap.rend(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

 	std::cout << "Deleted: " << mymap.erase(100) << std::endl;
 	std::cout << "Deleted: " << mymap.erase(1010) << std::endl;
	for (map<int, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";
	
	print_step("Testing swap & clear");
	mymap.swap(map2);
	for (map<int, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
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

	mymap.clear();
	std::cout << "size: " << mymap.size() << std::endl;
	for (map<int, int>::const_iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		std::cout << "first: " << it->first;
		std::cout << " second: " << it->second << std::endl;
	}
	std::cout << "----\n";

	print_step("Testing find & count");
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

	print_step("Testing []");
	std::cout << map2[200] << std::endl;
	std::cout << map2[123] << std::endl;
	map2[123] = 123;
	std::cout << map2[123] << std::endl;
	std::cout << "----\n";

	TestMoreMap();
}

int		main(int argc, char **argv)
{
	hello();
	if (argc != 2)
	{
		cout << "Usage: ./containers \"container\"" << endl;
		return 0;
	}
	std::string	arg = std::string(argv[1]);
	if (arg == "vector")
	{
		TestDefaultConstructor();
		TestFillConstructor();
		TestRangeConstructor();
		TestCopyConstructor();
		TestBeginEndIterators();
		TestElementsMemory();
		TestOther();
		TestOperators();
	}
	if (arg == "stack")
	{
		TestStack();
	}
	if (arg == "map")
	{
		TestMap();
	}
	return 0;
}
