#include <iostream>
#include <future>

template <typename T>
void print_validity(const std::future<T>& ftr)
{
	std::cout << (ftr.valid() ? "valid" : "invalid") << '\n';
}

int main()
{
	std::promise<int> prom{};

	std::future<int> ftr = prom.get_future();

	print_validity(ftr);
	
	prom.set_value(12);
	auto val = ftr.get();
	std::cout << "val = " << val << '\n';
	print_validity(ftr);
}
