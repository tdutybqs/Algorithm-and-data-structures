#include <iostream>
#include "vector.h"


int main() {
	vector<int> a{ 1,2,3,4 };
	a.push_back(10);
	auto start = a.begin();
	while (start != a.end()) {
		std::cout << (*start) << " " << std::endl;
		start++;
	}
	std::cout <<"Iterator + n = " << *(a.begin() + 2) << std::endl;
	std::cout <<"Equality = " << (a.begin() == a.begin()) << std::endl;
	auto test = a.end();
	advance(test, -4);
	std::cout << "Advance = " << *test << std::endl;
}