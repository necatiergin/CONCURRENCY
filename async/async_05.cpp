#include <iostream>
#include <future>
#include <chrono>

unsigned long long fibo(unsigned long long n)
{
	return  n <= 1 ? 1 : fibo(n - 1) + fibo(n - 2);
}

using namespace std::literals;

int main()
{
	auto ft_result = std::async(std::launch::async, fibo, 45);

	while (ft_result.wait_for(300ms) != std::future_status::ready) {
		//do something else
		std::cout << "Waiting for the result...\n";
	}

	std::cout << "value is ready : " << ft_result.get() << '\n';
}
