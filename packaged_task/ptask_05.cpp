#include <thread>
#include <future>
#include <string>
#include <iostream>

std::string get_data_from_db(const std::string& token)
{
	std::string sdata = "string got from the data base:: " + token;
	return sdata;
}

int main()
{
	using ftype = std::string(const std::string&);
	std::packaged_task<ftype> ptask(get_data_from_db);

	auto result = ptask.get_future();
	std::thread th(std::move(ptask), "Necati Ergin");

	th.join();

	std::cout << result.get();
}
