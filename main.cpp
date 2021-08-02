/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nelisabe <nelisabe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 14:39:51 by nelisabe          #+#    #+#             */
/*   Updated: 2021/08/02 21:09:01 by nelisabe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "vector.hpp"
# include <vector>
# include <iostream>
# include <string>
# include <unistd.h>

#ifndef MODE
#define MODE 0
#endif

#define YELLOW	"\033[33m"
#define RED		"\033[31m"
#define RESET	"\033[0m"
#define BOLD	"\033[1m"

#if MODE
	using std::vector;
#else
	using ft::vector;
#endif

using std::cout;
using std::endl;
using std::string;

template<typename T>
void	print_state(const vector<T> &vec);
void	print_test(const string &);

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
	for (vector<int>::const_reverse_iterator it = vec.rbegin(); it < vec.rend(); ++it)
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

void	hello()
{
	cout << "Testing ";
	if (MODE)
		cout << BOLD << RED << "std" << RESET;
	else
		cout << BOLD << RED << "ft" << RESET;
	cout << " vector!\n" << endl;
	sleep(2);
}

int		main(void)
{
	hello();
	TestDefaultConstructor();
	TestFillConstructor();
	TestRangeConstructor();
	TestCopyConstructor();
	TestBeginEndIterators();
}
