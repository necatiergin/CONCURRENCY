#include <future>
#include <iostream>
#include <thread>

int fib(int n)
{
	return (n < 3) ? 1 : fib(n - 1) + fib(n - 2);
}

int main()
{
	std::packaged_task<int(int)> fib_task(&fib);

	auto result = fib_task.get_future();
	std::thread th(std::move(fib_task), 40);

	std::cout << "task'in bitmesi bekleniyor...\n";
	std::cout << result.get() << '\n';

	std::cout << "task tamamlandi\n";
	th.join();
}

