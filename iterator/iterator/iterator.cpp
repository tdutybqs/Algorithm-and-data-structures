#include <iostream>
#include "vector.h"


template <typename T>
void printVector(vector<T>& a) {
	std::cout << "Size = " << a.size() << std::endl;
	auto start = a.begin();
	while (start != a.end()) {
		std::cout << (*start) << " " << std::endl;
		++start;
	}
}


int main() {
	vector<int> a{ 1,2,3,4 };
	a.push_back(10);
	printVector(a);
	a.erase(a.begin());
	printVector(a);
}