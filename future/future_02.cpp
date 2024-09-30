// function promise parameter

#include <future>
#include <functional>
#include <thread>

void foo(std::promise<int>);
void bar(std::promise<int>&);
void baz(std::promise<int>&&);

int main(void)
{
	std::promise<int> pr;

	//std::thread t1(foo, pr);  //error
	std::thread t2(foo, std::move(pr)); //valid
	//std::thread t3(bar, pr); // error
	std::thread t4(bar, std::ref(pr));	//valid
	std::thread t5(baz, std::move(pr));	  //valid

	//...
}
