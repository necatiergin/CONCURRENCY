#include <future>
#include <iostream>
#include <thread>
#include <utility>

//producer code receives promise object by R value reference
void sum_square(std::promise<int>&& prom, int x, int y)
{
	//calls set_value member function to set the shared state
	//calls set_value member function to set the shared state
	prom.set_value(x * x + y * y);
}

struct Div {
	//producer code receives promise object by R value reference
	void operator() (std::promise<int>&& prom, int x, int y) const
	{
		//calls set_value member function to set the shared state
		prom.set_value(x / y);
	}
};

//consumer code here is the main function

int main()
{
	int x{ 90 }, y{ 15 };

	// we define promise objects
	std::promise<int> sum_square_prom;
	std::promise<int> div_prom;

	// we get the future objects by calling the member function get_future of promise object
	auto fp_sumsquare = sum_square_prom.get_future();
	auto fp_div = div_prom.get_future();

	// we launch the threads
	std::jthread tss(sum_square, std::move(sum_square_prom), x, y);
	std::jthread tdd(Div{}, std::move(div_prom), x, y);
	
	//we call the get function of the future object to get the result
	// get function blocks the current thread until the value is ready
	std::cout << x << " * " << y << " = " << fp_sumsquare.get() << '\n';
	std::cout << x << " / " << y << " = " << fp_div.get() << '\n';
}
