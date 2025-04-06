#include <iostream>
#include <string>
#include <syncstream>
#include <vector>

thread_local std::string name("Necati ");

void func(const std::string& surname) {

	name += surname;
	std::osyncstream { std::cout } << name << " &name: " << &name << std::endl;
}

int main()
{
	const char* const pa[] = { "Ergin", "Ozkan", "Ersoy", "Toptan", "Erdogan", "Demirkapi" };

	std::vector<std::jthread> tvec;

	for (auto psurname : pa) {
		tvec.emplace_back(func, psurname);
	}
}
