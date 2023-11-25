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

#### üye fonksiyonlar

_notify_one_ : bekleyen bir _thread_'e sinyal gönderir. <br>
_notify_all_ : bekleyen bütün thread'lere sinyal gönderir. <br>
_wait_ : thread'i sinyal gelene kadar bloke eder <br>
_wait_for_ : blocks current thread until notified or specified duration passed<br>
_wait_until_ : blocks current thread until notified or specified time point reached<br>
_native_handle_: get native handle associated with condition variable<br>


