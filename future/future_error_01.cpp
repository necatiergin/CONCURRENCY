/*
	bir std::promise nesnesini 2. kez set edersek std::future_error
	sınıfı türünden hata gönderir 
*/

#include <future>
#include <iostream>

int main() 
{
	std::promise<int> prom;
	prom.set_value(10);

	try {
		prom.set_value(19);
	}
	//catch (const std::exception& ex) {
	catch (const std::future_error ex) {
		std::cout << "exception caught: " << ex.what() << '\n';
	}
}
