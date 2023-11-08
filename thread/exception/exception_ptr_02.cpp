#include <vector>
#include <exception>
#include <mutex>
#include <iostream>

std::vector<std::exception_ptr> g_ex_vec;
std::mutex g_mutex;

void f1()
{
	throw std::exception{ "exception from f1" };
}

//----------------------------------------------------------------------------------------------------

void f2()
{
	throw std::exception{ "exception from f2" };
}

//----------------------------------------------------------------------------------------------------

void th_func1()
{
	try {
		f1();
	}
	catch (...) {
		std::lock_guard<std::mutex> guard{ g_mutex };
		g_ex_vec.push_back(std::current_exception());
	}
}

//----------------------------------------------------------------------------------------------------

void th_func2()
{
	try {
		f2();
	}
	catch (...) {
		std::lock_guard<std::mutex> guard{ g_mutex };
		g_ex_vec.push_back(std::current_exception());
	}
}

//----------------------------------------------------------------------------------------------------

int main()
{
	std::thread t1(th_func1);
	std::thread t2(th_func2);

	t1.join();
	t2.join();

	for (auto const& ex : g_ex_vec) {
		try
		{
			if (ex != nullptr)
				std::rethrow_exception(ex);
		}
		catch (std::exception const& ex)
		{
			std::cout << "exception caught: " << ex.what() << '\n';
		}
	}
}
