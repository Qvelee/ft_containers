/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:39:51 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/03 20:08:20 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <vector>
# include <iostream>
# include <string>
# include <unistd.h>
# include "vector.hpp"
# include "stack.hpp"

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
#else
	using ft::vector;
	using ft::swap;
#endif

using std::cout;
using std::endl;
using std::string;

template<typename T>
void	print_state(const vector<T> &vec);
void	print_test(const string &);
void	print_step(const string &);

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
	}
	if (arg == "stack")
	{
		TestStack();
	}
	return 0;
}
