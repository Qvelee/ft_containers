# include "vector_iterator.hpp"
# include <string>
# include <iostream>

using std::string;
using std::cout;

template<typename T>
ft::VectorIterator<T, true>	cbegin(T *array)
{
	return ft::VectorIterator<T, true>(array);
}

template<typename T>
ft::VectorIterator<T, true>	cend(T *array)
{
	return ft::VectorIterator<T, true>(array + 5);
}

int		main(void)
{
	int		array[] = {1, 2, 3, 4, 5};

	ft::VectorIterator<int, true> it_begin = cbegin(array);
	ft::VectorIterator<int, true> it_end = cend(array);

	std::cout << *it_begin << std::endl;
	*it_begin = 10;
	// while (it_begin != it_end)
	// {
		// std::cout << *it_begin << std::endl;
		// *it_begin = 10;
		// it_begin++;
	// }
	// it_begin = begin(array);
	// while (it_begin != it_end)
	// {
		// std::cout << *it_begin << std::endl;
		// it_begin += 1;
	// }
	// it_begin -= 2;
	// std::cout << *it_begin << std::endl;
	return 0;
}
