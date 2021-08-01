# include "vector.hpp"
# include <string>
# include <iostream>
# include <vector>

using std::string;
using std::cout;
// using std::vector;
using ft::vector;

int		main(void)
{
	vector<int>	vec;

	vec.push_back(1);
	vec.push_back(3);
	vec.insert(vec.begin() + 1, 5);
	cout << "vector: ";
	for (vector<int>::iterator it = vec.begin(); it < vec.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	return 0;
}
