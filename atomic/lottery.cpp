#include <iostream>
#include <vector>
#include <atomic>
#include <thread>

std::atomic is_ready{ false }; //CTAD
std::atomic is_done{ false };
std::atomic go_count{0};

 void lottery(std::string name) 
 {
	++go_count;
	
	while (!is_ready)
		;

	for (volatile int i = 0; i < 20000; ++i) 
	{
	
	}
	bool expected{ false };
	if (is_done.compare_exchange_strong(expected, true)) {
		std::cout << "kazanan: " << name << '\n'; 
	}
}

int main()
{
	constexpr const char* pnames[] = { "necati", "akif", "ahmet", "harun", "mehmet", "dogukan"};
	std::vector<std::jthread> tvec;
	for (auto p : pnames) {
		tvec.emplace_back(lottery, p); 
	}
	
	while (go_count != std::size(pnames))
		;
	is_ready = true;
	for (auto& t : tvec) {
		t.join();
	}

}
