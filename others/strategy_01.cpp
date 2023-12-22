#include <iostream>
#include <memory>

class Strategy {
public:
	virtual void operator()() = 0;
	virtual ~Strategy() = default;
};

class Context {
public:
	void set_strategy(std::shared_ptr<Strategy> st) 
	{
		msp = st;
	}
	
	void do_something() 
	{
		if (msp) 
			(*msp)(); 
	}
private:
	std::shared_ptr<Strategy> msp{};
};


class FooStrategy : public Strategy {
	void operator()() override 
	{
		std::cout << "FooStrategy\n";
	}
};



class BarStrategy : public Strategy {
	void operator()() override 
	{
		std::cout << "BarStrategy\n";
	}
};

class BazStrategy : public Strategy {
	void operator()() override 
	{
		std::cout << "BazStrategy\n";
	}
};


int main() 
{
	Context con;
	con.set_strategy(std::make_shared<FooStrategy>());
	con.do_something();
	con.set_strategy(std::make_shared<BarStrategy>());
	con.do_something();
	con.set_strategy(std::make_shared<BazStrategy>());
	con.do_something();
}
