Bir _thread_'in bir başka thread tarfından bir sonucun üretilmesini beklemek için aşağıdaki gibi bir sorgulama _(polling)_ gerçekleştirdiğini düşünelim.

```cpp
#include <mutex>
#include <chrono>


bool go_flag{};
std::mutex mtx;

void func()
{
	std::unique_lock lock(mtx);
	while (!go_flag) {
		lock.unlock();
		std::this_thread::yield(); 
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		lock.lock();
	}
}
```
böyle bir sorgulama iyi bir çözüm olmayabilir:

+ bekleyen _thread_ bayrak değişkeni tekrar tekrar kontrol ederek değerli işlemci süresini alır ve _mutex_'i kilitlediğinde bayrak değişkeni set eden _thread_i bloke eder. 
+ olay gerçekleşene kadar beklenecek süreyi _(uyku süresini)_ doğru olarak seçmek de zordur: 
  + kontroller arasındaki uyku süresi çok kısa olursa bekleyen _thread_ sürekli bayrak değişkeni kontrol ederek işlemci süresini boşa harcar.
  + kontroller arasındaki uyku süresi çok uzun olursa bekleyen _thread_ görev tamamlandığında bile uyumayı sürdürür ve gereksiz bir gecikmeye neden olur.

+ daha iyi bir yaklaşım, C++ standart kütüphanesinin _<condition_variable>_  başlık dosyasında  sağladığı koşul değişkenlerini kullanmaktır. 
+ koşul değişkeni, bir iş parçacığının bir veya birden fazla bekleyen iş parçacığını uyandırabileceği bir değişkendir.

```
{
	std::unique_lock<std::mutex> ul(readyMutex);
	readyCondVar.wait(ul, []{ return readyFlag; });
} // release lock
```
kod karşılığı derleyicinin aşağıdaki gibi bir kod ürettiğini düşünebiliriz.
```
{
	std::unique_lock<std::mutex> ul(readyMutex);
	while (!readyFlag) {
		readyCondVar.wait(ul);
	}
} // release lock
```
