# include "vector_iterator.hpp"
# include <string>
# include <iostream>

using std::string;
using std::cout;

template<typename T>
ft::VectorIterator<T>	begin(T *array)
{
	return ft::VectorIterator<T>(array);
}

template<typename T>
ft::VectorIterator<T>	end(T *array)
{
	return ft::VectorIterator<T>(array + 5);
}

int		main(void)
{
	// string	array[] = {"One", "Two", "Three"};
// 
	// ft::VectorIterator<string> it_begin = begin(array);
	// ft::VectorIterator<string> it_end = end(array);

	int		array[] = {1, 2, 3, 4, 5};

	ft::VectorIterator<int> it_begin = begin(array);
	ft::VectorIterator<int> it_end = end(array);

	while (it_begin != it_end)
	{
		std::cout << *it_begin << std::endl;
		*it_begin = 10;
		it_begin++;
	}
	it_begin = begin(array);
	while (it_begin != it_end)
	{
		std::cout << *it_begin << std::endl;
		it_begin += 1;
	}
	it_begin -= 2;
	std::cout << *it_begin << std::endl;
	return 0;
}
