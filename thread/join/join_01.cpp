//eğer thread nesnesinin detsructor'u çağrıldığında thread joinable durumda ise terminate işlevi çağrılır.

#include <iostream>
#include <thread>

void hello()
{
	std::cout << "Hello World!\n";
}

int main()
{
	std::thread t(hello);
	t.join();
}
