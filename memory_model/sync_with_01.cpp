#include <thread>
#include <cassert>

int x = 0;

void foo() 
{
	// A1 (thread fonksiyonun yürütülmesi başlıyor)
	assert(x == 1); // assertion doğrulanır çünkü M1 A1 ile senkronize
	x = 2;
	//A2 (thread fonksiyonunun yürütülmesi tamamlannıyor)

}

int main()
{
	x = 1;
	std::thread t(foo); // M1 (constructor kodunun çalışması tamamlanıyor)
	t.join(); // M2 (join fonksiyonu return etmiş durumda)
	assert(x == 2); // assertion doğrulanır. Çünkü A2 M2 ile senkronize
}

