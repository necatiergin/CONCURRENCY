#include <mutex>
#include <iostream>
#include <syncstream>
#include <chrono>

std::mutex a_mtx;
std::mutex b_mtx;

using namespace std::literals;
namespace td = std::this_thread;

void foo()
{

	std::osyncstream{ std::cout } << td::get_id() << " is trying to lock a_mtx\n";

	a_mtx.lock();
	std::osyncstream{ std::cout } << td::get_id() << " has locked a_mtx\n";
	std::this_thread::sleep_for(500ms);
	std::osyncstream{ std::cout } << td::get_id() << " is trying to lock b_mtx\n";
	b_mtx.lock();
	std::osyncstream{ std::cout } << td::get_id() << " has locked b_mtx\n";
	a_mtx.unlock();
	std::osyncstream{ std::cout } << td::get_id() << " has unlocked a_mtx\n";
	b_mtx.unlock();
	std::osyncstream{ std::cout } << td::get_id() << " has unlocked b_mtx\n";
}


void bar()
{
	std::osyncstream{ std::cout } << td::get_id() << " is trying to lock a_mtx\n";
	a_mtx.lock();
	std::osyncstream{ std::cout } << td::get_id() << " has locked a_mtx\n";
	std::this_thread::sleep_for(500ms);
	std::osyncstream{ std::cout } << td::get_id() << " is trying to lock b_mtx\n";
	b_mtx.lock();
	std::osyncstream{ std::cout } << td::get_id() << " has locked b_mtx\n";
	a_mtx.unlock();
	std::osyncstream{ std::cout } << td::get_id() << " has unlocked a_mtx\n";
	b_mtx.unlock();
	std::osyncstream{ std::cout } << td::get_id() << " has unlocked b_mtx\n";
}



int main()
{
	std::jthread t1{ foo };
	std::jthread t2{ bar };
}
