#include <stdexcept>
#include <cmath>
#include <iostream>
#include <future>


double get_power(double base, double exp)
{
	if (exp < 0.)
		throw std::invalid_argument{ "negative exponent" };

	return std::pow(base, exp);
}

int main()
{
	double base, exp;

	std::cout << "enter base and exp: ";
	std::cin >> base >> exp;

	auto ft_result = std::async(get_power, base, exp);

	try {
		std::cout << "result is : " << ft_result.get() << '\n';
	}
	catch (std::exception& e) {
		std::cout << "exception caught: " << e.what() << '\n';
	}
}
