#include <future>
#include <iostream>
#include <stdexcept>


void sum_square(std::promise<int>&& prom, int x, int y)
{
	prom.set_value(x * x + y * y);
}

struct Div
{
	void operator()(std::promise<int>&&prom, int x, int y)const
	{
		prom.set_value(x / y);
	}
};



int main() 
{
	int x{ 90 }, y{ 15 };
	std::promise<int> sum_square_prom;
	std::promise<int> div_prom;

	std::future<int> fp_sum_square = sum_square_prom.get_future();
	std::future<int> fp_div = div_prom.get_future();

	std::thread tx{ sum_square,std::move(sum_square_prom),x,y };
	std::thread ty{ Div{}, std::move(div_prom) ,x ,y};

	std::cout << x << " * " << x << " + "
		<< y << " * " << y << " = "
		<< fp_sum_square.get() << std::endl; // Sonuç hazırsa get ile alacak
							// değilse bloke edecek.

	std::cout << x << " / " << y << " = " << fp_div.get() << std::endl;


	tx.join();
	ty.join();

}
