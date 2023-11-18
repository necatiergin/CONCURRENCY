#include <iostream>
#include <thread>

int main()
{
	using namespace std;

	cout <<
		typeid(this_thread::get_id()).name();

	// class std::thread::id;	
}
