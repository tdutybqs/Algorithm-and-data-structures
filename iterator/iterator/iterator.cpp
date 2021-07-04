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
	vector<int> const a{ 1,2,3,4 };
	printVector(a);
	//a.erase(a.begin());
	printVector(a);
}