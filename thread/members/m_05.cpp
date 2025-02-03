#include <thread>
#include <iostream>

void foo()
{
	//...
}

int main()
{
	std::thread tx{ foo };
	tx.join();

	try {
		tx.join(); // throws exception
	}
	catch (const std::exception& ex)
	{
		std::cout << "exception cauhgt : " << ex.what() << '\n';
	}
}
