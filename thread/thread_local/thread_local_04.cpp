#include <iostream>
#include <string>
#include <syncstream>
#include <vector>


thread_local std::string name("Necati");

void func(std::string const& surname) {

	name += surname;
	std::osyncstream ocout{std::cout };
	ocout << name << " &name: " << &name << std::endl;
}

int main() 
{
	const char* const pa[] = { "Ergin", "Ozkan", "Ersoy", "Toptan", "Erdogan", "Demirkapi" };

	std::vector<std::thread> tvec;

	for (auto p : pa) {
		tvec.emplace_back(func, p);
	}


	for (auto &t : tvec) {
		t.join();
	}
}
