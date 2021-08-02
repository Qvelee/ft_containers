# include "vector.hpp"
# include <string>
# include <iostream>
# include <vector>
# include <cstdlib>

using std::string;
using std::cout;
//using std::vector;
using ft::vector;

int		main(void)
{
	vector<int>		vec;
	std::vector<int>	vec2;

	vec2.push_back(20);
	vec2.push_back(30);
	vec2.push_back(40);

	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	vec.push_back(5);
	auto ite = vec.erase(vec.begin() + 3, vec.end() - 1);
	cout << "erase: " << *ite << '\n';
	cout << "vector: ";
	for (vector<int>::iterator it = vec.begin(); it < vec.end(); ++it)
		cout << *it << ' ';
	cout << '\n';
	return 0;
}
