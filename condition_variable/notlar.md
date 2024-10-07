+ Eşzamanlı programlarda, genellikle bir _thread_'in belirli bir olay gerçekleşene kadar beklemesi gerekir (örneğin, bir giriş çıkış işlemi tamamlanana kadar ya da bir veri kullanılabilir duruma gelene kadar).
+ Bir _thread_'in bir olayın gerçekleşip gerçekleşmediğini tekrar tekrar kontrol etmesi verimsiz olabilir (yani işlemci kaynaklarını boşa harcayabilir).
+ _thread_'in bloke edilmesi ve ancak ilgili olay gerçekleştikten sonra yürütülmesinin devam ettirilmesi genellikle daha iyidir.
+ _condition variable_, _thread_'lerin belirli bir koşul gerçekleşene kadar beklemesine (bloke olarak) olanak tanıyan bir senkronizasyon aracıdır.
+ Bir koşul değişkeni, ilgilenilen bazı olaylara karşılık gelir.
+ Bir olayı beklemek isteyen bir _thread_, _condition variable_ üzerinde bir bekleme işlemi gerçekleştirir.
+ Bir veya daha fazla bekleyen _thread_'i bir olaydan haberdar etmek isteyen bir _thread_, _condition variable_ üzerinde bir sinyal işlemi gerçekleştirir.
+ Bununla birlikte, sinyal verilen _thread_ çalışmaya tekrar başladığında, sinyal verilen koşulun doğru olduğu garanti edilmez (ve yeniden kontrol edilmesi gerekir), çünkü örneğin başka bir _thread_ koşulun değişmesine neden olmuş olabilir veya sahte _(spurious)_ bir uyanma meydana gelmiş olabilir.

#### _std::condition_variable_ sınıfı
+ _std::condition_variable_ sınıfı _condition variable_ sağlar.
+ _std::condition_variable_ sınıf nesneleri kopyalanamaz ve taşınamaz.
+ Gerekli koşulun sağlanmasını beklemek için sınıfın
  - wait
  - wait_for
  - wait_until 
fonksiyonlarından biri çağrılır.

+ koşulun oluşmasını bekleyen _thread_ ya da _thread_'lere haber vermek için sınıfın
  - notify_one
  - notify_all 
fonksiyonları kullanılır.

+ _thread_ uyandığında uyanan _thread_'in koşulun gerçekleşip gerçekleşmediğini tekrar kontrol etmesi gerekir, çünkü
  - sahte _(spurious)_ uyanışlara izin verilir
  - uyanacak _thread_'e sinyal gönderildiği zaman ile uyandığı ve _mutex_'i kilitlediği zaman arasında, başka bir iş parçacığı durumun değişmesine neden olabilir.
+ _notify_one, notify_all, wait, wait_for, wait_until_ fonksiyonları eş zamanlı olarak çağrılabilir
+ _wait, wait_for, and wait_until_ fonksiyonları _mutex_'i atomik olarak serbest bırakırlar ve bloke olurlar.
+ _notify_one_ ve _notify_all_ fonksiyonları atomiktir.
+ Bir condition_variable nesnesi oluşturulamıyor ise,sınıfın kurucu işlevi _std::system_error_exception_ türünden bir hata nesnesini _resource_unavailable_try_again_ hata kodu ile gönderir.


#### üye fonksiyonlar

_notify_one_ : bekleyen bir _thread_'e sinyal gönderir. <br>
_notify_all_ : bekleyen bütün thread'lere sinyal gönderir. <br>
_wait_ : thread'i sinyal gelene kadar bloke eder <br>
_wait_for_ : blocks current thread until notified or specified duration passed<br>
_wait_until_ : blocks current thread until notified or specified time point reached<br>
_native_handle_: get native handle associated with condition variable<br>

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

