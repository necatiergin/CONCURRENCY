#include <future>
#include <iostream>

double get_value() 
{
	//code
	return 4.896;
}

int main() 
{
	auto fn = std::async(std::launch::async, get_value);
	std::cout << fn.get() << '\n';
}
