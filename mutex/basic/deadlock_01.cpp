#include <mutex>
#include <iostream>
#include <chrono>

std::mutex mtx;

void foo(int x)
{
	using namespace std::chrono_literals;

	std::this_thread::sleep_for(200ms);
	try {
		mtx.lock();
		//code
		if (x % 2 == 0)
			throw std::runtime_error{ "error in foo();" };
		mtx.unlock();
	}
	catch (std::exception& ex) {	 
		std::cout << "exception caught in foo: " << ex.what() << '\n';
	}
}

void my_terminate()
{
	std::cout << "my terminate called!\n";
	std::abort();
}

int main()
{
	//(the following code causes deadlock
	std::set_terminate(my_terminate);
	std::thread t1{ foo, 4 };
	std::thread t2{ foo, 3 };

	t1.join();
	t2.join();
}


