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
	catch (const std::system_error& ex) 
		//catch (const std::runtime_error& ex) 
		//catch (const std::exception& ex) 
	{
		std::cout << "exception caught : " << ex.what() << '\n';
	}
}
