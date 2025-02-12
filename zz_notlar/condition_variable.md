+ Eşzamanlı programlarda, genellikle bir _thread_'in belirli bir olay gerçekleşene kadar beklemesi gerekir (örneğin, bir giriş çıkış işlemi tamamlanana kadar ya da bir veri kullanılabilir duruma gelene kadar).
+ Bir _thread_'in beklediği bir olayın gerçekleşip gerçekleşmediğini tekrar tekrar kontrol etmesi verimsiz olabilir (yani işlemci kaynaklarını boşa harcayabilir).
+ _thread_'in bloke edilmesi ve ancak ilgili olay gerçekleştikten sonra yürütülmesinin devam ettirilmesi genellikle daha iyidir. Böylece bekleyen _thread_ kıymetli işlemci zamanını boş yere harcamamış olur.
+ _condition variable_, _thread_'lerin belirli bir koşul gerçekleşene kadar beklemesine (bloke olarak) olanak tanıyan temel bir senkronizasyon aracıdır.
+ Bir _conditional_variable_ (koşul değişkeni), ilgilenilen bazı olaylara karşılık gelir.
+ Bir olayı beklemek isteyen bir _thread_, _condition variable_ üzerinde bir bekleme işlemi (wait) gerçekleştirir.
+ Bir veya daha fazla bekleyen _thread_'i bir olaydan haberdar etmek isteyen bir _thread_, _condition variable_ üzerinden bir sinyal gönderir.
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
+ Bir _condition_variable_ nesnesi oluşturulamıyor ise, sınıfın kurucu işlevi _std::system_error_exception_ türünden bir hata nesnesini _resource_unavailable_try_again_ hata kodu ile gönderir.


#### üye fonksiyonlar

_notify_one_ : bekleyen bir _thread_'e sinyal gönderir. <br>
_notify_all_ : bekleyen bütün _thread_'lere sinyal gönderir. <br>
_wait_ : thread'i sinyal gelene kadar bloke eder. <br>
_wait_for_ : _thread_'i bildirim gelene kadar ya da belirli bir süre bloke eder.<br>
_wait_until_ : hread_'i bildirim gelene kadar ya da belirli zaman gelinceye kadar blloke eder.<br>
_native_handle_: işletim sisteminin sistem fonksiyonları için bir _handle_ döndürür.<br>

Bir _thread_'in bir başka _thread_ tarfından bir sonucun üretilmesini beklemek için aşağıdaki gibi bir sorgulama _(polling)_ gerçekleştirdiğini düşünelim.

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

+ bekleyen _thread_ bayrak değişkeni tekrar tekrar kontrol ederek değerli işlemci süresini alır ve _mutex_'i kilitlediğinde bayrak değişkeni set eden _thread_'i bloke eder. 
+ olay gerçekleşene kadar beklenecek süreyi _(uyku süresini)_ doğru olarak seçmek de zordur: 
  + kontroller arasındaki uyku süresi çok kısa olursa bekleyen _thread_ sürekli bayrak değişkeni kontrol ederek işlemci süresini boşa harcar.
  + kontroller arasındaki uyku süresi çok uzun olursa bekleyen _thread_ görev tamamlandığında bile uyumayı sürdürür ve gereksiz bir gecikmeye neden olur.

+ daha iyi bir yaklaşım, C++ standart kütüphanesinin _<condition_variable>_  başlık dosyasında sağladığı koşul değişkenlerini kullanmaktır. 
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

#### spurious wakeup

+ Bazen (önceden öngörülemeyecek biçimde) _reader thread_ bekleme durumunda iken "_spuriously_" (yanlış biçimde) uyandırılır.
+ Oysa _writer thread_ henüz sinyal _(notification)_ göndermemiştir ama _condition variable_ uyumakta olan _reader thread_'i uyandırır.
+ Bunun nedeni _condition variable_'ın gerçekleştirilme _(implementation)_ biçimidir. Böyle uyandırmalardan kaçınmanın maliyeti çok daha yüksek olduğu için _"yanlış uyandırmalara"_ izin verilir.

#### lost wakeup

+ _condition_variable_ sınıfının _wait_ fonksiyonu sınıfın _notify_ fonksiyonu çağrılana kadar _thread_'i bloke eder.
+ eğer _writer thread_'de _notify_ fonksiyonu _reader thread_'deki _wait_ çağrısından daha önce gerçekleştirilirse bir sinyal _(notification)_ gönderilmiş olmasına karşın henüz beklemekte olan bir _thread_ yoktur.
+ bu durumda _reader thread_ hiçbir şekilde uyanamaz ve bloke olarak kalır.
+ bu duruma _lost-wakeup_ denir. (kod örneğine bakınız)
