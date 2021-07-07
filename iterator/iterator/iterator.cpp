#include <iostream>
#include "vector.h"


template <typename T>
void printVector(const vector<T>& a) {
	std::cout << "Size = " << a.size() << std::endl;
	auto start = a.begin();
	while (start != a.end()) {
		std::cout << (*start) << " " << std::endl;
		++start;
	}
}


int main() {
	vector<int> a{ 1,2,3,4 };
	printVector(a);
	vector<int> b{ 1,2,3,4,4 };
	printVector(b);
	std::cout << (a == b) << std::endl;
	std::cout << (a != b) << std::endl;
	std::cout << (a < b) << std::endl;
	std::cout << (a > b) << std::endl;
}