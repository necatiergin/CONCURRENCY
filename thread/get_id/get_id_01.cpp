#include <syncstream>
#include <iostream>

using namespace std;

void foo()
{
	osyncstream{ cout } << this_thread::get_id() << '\n';
}

int main()
{
	thread tx{ foo };
	osyncstream{ cout } << tx.get_id() << '\n';
	tx.join();
}
