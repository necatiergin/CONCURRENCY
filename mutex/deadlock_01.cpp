/*
	Aşağıdaki kodda deadlock oluşuyor.
	Her iki thread'de bloke oluyor.
        foo'yu yürüten threadin devam edebilmesi için bar'ı yürüten thread'in b_mtx'i serbest bırakması gerekiyor.
	bar'ı yürüten threadin devam edebilmesi için foo'yu yürüten thread'in a_mtx'i serbest bırakması gerekiyor.
        Eğer mutex'ler her iki thread tarafından da aynı sırada edinilseydi bir sorun oluşmayacaktı.
*/

#include<mutex>
#include <iostream>

std::mutex a_mtx;
std::mutex b_mtx;

void foo() 
{
	using namespace std::literals;

	a_mtx.lock();
	std::this_thread::sleep_for(100ms); 
	b_mtx.lock(); 
	std::cout << "func()" << std::endl;
	a_mtx.unlock();
	b_mtx.unlock();
}


void bar() 
{
	using namespace std::literals;
	b_mtx.lock();
	std::this_thread::sleep_for(100ms);
	a_mtx.lock();
	std::cout << "bar()" << std::endl;
	b_mtx.unlock();
	a_mtx.unlock();
}


int main()
{
	std::thread t1{ foo };
	std::thread t2{ bar };
	t1.join();
	t2.join();
}
