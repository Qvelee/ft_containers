# include "vector.hpp"
# include <string>
# include <iostream>
# include <vector>
# include <cstdlib>

using std::string;
using std::cout;
// using std::vector;
using ft::vector;

int		main(void)
{
	vector<int>		vec;
	std::vector<int>	vec2;

	vec2.push_back(20);
	vec2.push_back(30);
	vec2.push_back(40);

	vec.push_back(3);
	vec.push_back(10);
	vec.insert(vec.begin() + 2, vec2.begin(), vec2.end());
	cout << "vector: ";
	for (vector<int>::iterator it = vec.begin(); it < vec.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	return 0;
}
