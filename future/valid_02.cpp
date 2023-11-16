#include <future>
#include <iostream>

int main() 
{
	std::promise<int> prom;
	std::future<int> ftr = prom.get_future();
	
	prom.set_value(991);
	auto val = ftr.get(); 
	
	std::cout << "val = " << val << '\n';
	if (ftr.valid())
	{
		std::cout << "future nesnesi valid durumda\n";
	}
	else
	{
		std::cout << "future nesnesi invalid\n";
	}
}
