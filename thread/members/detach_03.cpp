#include <thread>
#include <chrono>
#include <random>
#include <iostream>
#include <syncstream>
#include <exception>

void foo(int n, char digit)
{
	try {
		std::mt19937 eng(765u * digit);
		std::uniform_int_distribution dist(50, 500);
		for (int i = 0; i < n; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(dist(eng)));
			std::cout.put(digit).flush();
		}
	}

	catch (const std::exception& e) {
		std::osyncstream{ std::cerr } << "exception caught (thread " <<
			std::this_thread::get_id() << "): " << e.what() << '\n';
	}
	catch (...) {
		std::osyncstream{ std::cerr } << "exception caught (thread "
			<< std::this_thread::get_id() << ")\n";
	}
}


int main()
{
	std::osyncstream oscout{ std::cout };
	try {
		std::thread tx(foo, 10, '*');
		oscout << "- started forground thread " << tx.get_id() << '\n';

		for (int i = 0; i < 8; ++i) {
			std::thread th(foo, 10, '1' + i);
			oscout << "- detach started bg thread " << th.get_id() << '\n';
			th.detach();
		}
		std::cin.get();
		oscout << "- join fg thread " << tx.get_id() << '\n';
		tx.join();
	}
	catch (const std::exception& e) {
		std::cerr << "exception caught: " << e.what() << '\n';
	}
}
