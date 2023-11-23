/*
	std::future nesnesinin get işlevi 2. kez çağrıldığında>
	std::future_error sınıfı türünden bir hata nesnesi gönderilir.
*/

#include <iostream>
#include <future>

int main()
{
	std::promise<double> dprom;
	auto ftr = dprom.get_future();
	dprom.set_value(1.5);

	auto val = ftr.get();
	std::cout << "val = " << val << "\n";

	try {
		auto x = ftr.get();
	}
	//catch (const std::exception& ex) {
	catch (const std::future_error& ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
