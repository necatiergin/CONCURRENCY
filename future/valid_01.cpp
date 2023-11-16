#include <iostream>
#include <future>

int main()
{
	std::promise<int> prom{};

	std::future<int> ftr = prom.get_future();

	if (ftr.valid())
	{
		std::cout << "Valid\n";  //Valid
	}
	else
	{
		std::cout << "Invalid\n";
	}

}
