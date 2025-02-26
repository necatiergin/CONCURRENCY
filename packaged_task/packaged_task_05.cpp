#include <iostream>
#include <thread>
#include <future>
#include <functional>

int sum_square(int x, int y)
{
	return x * x + y * y;
}

void task_lambda()
{
	std::packaged_task<int(int, int)> task([](int a, int b) {
		return a * a + b * b;
		});
	//std::future<int> result = task.get_future();
	auto result = task.get_future();

	task(2, 9); 

	std::cout << "task_lambda\t\t: " << result.get() << '\n';
}

void task_bind()
{
	std::packaged_task<int()> task(std::bind(sum_square, 2, 11));
	//std::future<int> result = task.get_future();
	auto result = task.get_future();

	task();

	std::cout << "task_bind\t\t: " << result.get() << '\n';
}

void task_thread()
{
	std::packaged_task<int(int, int)> task(sum_square);
	//std::future<int> result = task.get_future();
	auto result = task.get_future();

	std::thread task_td(std::move(task), 2, 10);
	task_td.join();  

	std::cout << "task_thread\t\t: " << result.get() << '\n';
}

int main()
{
	task_lambda();
	task_bind();
	task_thread();
}
