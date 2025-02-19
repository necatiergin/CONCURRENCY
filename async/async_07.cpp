//Example: Futures and Exceptions
#include <iostream>
#include <vector>
#include <cmath>
#include <future>
#include <stdexcept>

double square_root(double x) 
{
	if (x < 0.0) {
		throw std::domain_error("negative value to square root function");
	}
	return std::sqrt(x);
}

int main() 
{
	
	std::vector dvec{ 2.3, 3.4, 1.1, -1.9 };
	std::vector<std::future<double>> results;
	
	for (auto x : dvec) {
		results.push_back(std::async(square_root, x));
	}
	
	for (auto& x : results) {
		try {
			std::cout << x.get() << '\n';
		}
		catch (const std::domain_error&) {
			std::cout << "error\n";
		}
	}
}
