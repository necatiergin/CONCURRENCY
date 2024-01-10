#include <iostream>
#include <string>
#include <thread>
#include <syncstream>

using namespace std;

void foo() 
{
	const string slocal("local string");
	thread th1([slocal] {
		osyncstream{ cout } << "by copy capture : " << slocal << '\n';
	});

	thread th2([&slocal] {
		osyncstream{ cout } << "by reference capture : " << slocal << '\n';
	});
	th1.detach();
	th2.detach();
}


int main() 
{
	using namespace std::literals;
	foo();
	std::this_thread::sleep_for(2s);
}
