#include <atomic>
#include <cassert>

int main()
{
	using namespace std;

	int ar[5]{};

	atomic ptr(ar);
	ptr++;
	assert(ptr.load() == ar + 1);
	ptr += 1;
	assert(ptr.load() == ar + 2);
	--ptr;
	assert(ptr.load() == ar + 1);
}
