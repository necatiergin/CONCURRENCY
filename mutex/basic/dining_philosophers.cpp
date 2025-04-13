<!---

// Dining philosophers problem (part 2a)
//
// 5 philosophers sit at a round table which has 5 forks on it.
// A philosopher has a fork at each side of them.
// A philosopher can only eat if they can pick up both forks.
// If a philosopher picks up the fork on their right,
// that prevents the next philosopher from picking up their left fork.
//
// The philosophers try to pick up both forks at the same time.
// If they succeed, they can eat.
// If not, both forks are available to their neighbours.
//
// All philosophers are able to eat.
// No deadlock
#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <chrono>

using namespace std::literals;

constexpr int nforks = 5;
constexpr int nphilosophers = nforks;
constexpr const char* pnames[nphilosophers] = { "Nietsche", "Kant", "Spinoza", "Marx", "Shopenhauer" };
constexpr auto think_time = 2s;
constexpr auto eat_time = 1s;
constexpr auto time_out = think_time;

bool eaten[nphilosophers]{};
std::mutex fork_mutex[nforks];
std::mutex print_mutex;

void print(int n, const std::string& str, int lfork, int rfork)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << pnames[n] << str;
	std::cout << lfork << " and " << rfork << '\n';
}


void print(int n, const std::string& str)
{
	std::lock_guard<std::mutex> print_lock(print_mutex);
	std::cout << pnames[n] << str << '\n';
}


void dine(int phil_no)
{
	// Philosopher A has fork 0 on their left
	// and fork 1 on their right
	// Philosopher B has fork 1 on their left
	// and fork 2 on their right
	// ...
	// Philosopher E has fork 4 on their left
	// and fork 0 on their right
	//
	// Each philosopher must pick up their left fork first
	int lfork = phil_no;
	int rfork = (phil_no + 1) % nforks;

	print(phil_no, "\'s forks are ", lfork, rfork);
	print(phil_no, " is thinking...");

	std::this_thread::sleep_for(think_time);

	// Make an attempt to eat
	print(phil_no, " reaches for forks ", lfork, rfork);

	// Try to pick up both forks
	std::lock(fork_mutex[lfork], fork_mutex[rfork]);
	print(phil_no, " picks up fork ", lfork, rfork);

	// Succeeded - this philosopher can now eat
	print(phil_no, " is eating...");
	eaten[phil_no] = true;

	std::this_thread::sleep_for(eat_time);

	print(phil_no, " puts down fork ", lfork, rfork);
	print(phil_no, " is thinking...");

	fork_mutex[lfork].unlock();
	fork_mutex[rfork].unlock();
	std::this_thread::sleep_for(think_time);
}

int main()
{
	// Start a separate thread for each philosopher
	std::vector<std::thread> philos;

	for (int i = 0; i < nphilosophers; ++i) {
		philos.push_back(std::move(std::thread{ dine, i }));
	}

	for (auto& philo : philos)
		philo.join();

	// How many times were the philosophers able to eat?
	for (int i = 0; i < nphilosophers; ++i) {
		std::cout << pnames[i] << " had " << eaten[i] << " mouthful\n";
	}
}

--->
