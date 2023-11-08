/*
	if we join an unjoinable thread it throws an exception
*/

#include <iostream>
#include <thread>

void foo() 
{
	//...
}
 
int main()
{
	std::thread tx{ foo };
	std::thread ty(std::move(tx));

	try {
		tx.join();
	}
	catch (const std::exception& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
