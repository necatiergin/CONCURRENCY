### atomic

- _Thread_'ler arasında veriyi paylaşırken _"data race"_ oluşmaması için genellikle bir senkronizasyon mekanizması gereklidir. (örneğin _mutex_ kullanarak senkronizasyonu sağlamak).
- Veriye senkronize edilmiş erişim sağlamanın başka bir yolu da atomik işlemleri kullanmaktır.
_multithreaded_ programlamada atomik işlem _(atomic operation)_, bölünemez _(indivisible)_ ve kesintiye uğratılamaz _(uninterruptible)_ bir işlem anlamına gelir. 

Atomik işlemler aşağıdaki özelliklere sahiptir:
Kesintiye uğramaz _(Uninterruptible)_: İşlem tamamlanmadan başka bir işlem parçacığı _(thread)_ araya giremez. Örneğin arttırma işlemi atomik ise bu işleme tabi tutulan bir değişken diğer _thread_'ler tarafından ya işlemden önceki ya da işlemden sonraki değeri ile görülebilir.<br>
Kesinlik _(Certainty)_: Bir atomik işlem ya tamamen gerçekleşir ya da hiç gerçekleşmez. atomik bellek işlemleri _"torn read"_ ya da _"torn write"_ durumu oluşturmazlar. <br>
Bağımsızlık _(Independence)_: İşlem, başka işlem parçacıklarından bağımsızdır ve herhangi bir ara durumda görünmez.<br>
Atomik işlemler kritik bölge _(critical section)_ oluşturma gereksinimini azaltarak, senkronizasyon mekanizmalarının performans yükünü hafifletir.
 İşlemcilerin çoğunda atomik bellek işlemleri özel makine komutları ile gerçekleştirilir.

- C++ standart kütüphanesi atomik bellek işlemleri için aşağıdaki atomik türleri sunmaktadır:
    - _std::atomic_flag_
    - _std::atomic_\<>
- Bu türler donanımın sağladığı atomik operasyonlar için uniform bir arayüz sunarlar. 

Atomik bir tür aşağıdaki garantileri sağlar:
- _atomicity_ (atomiklik - bölünmezlik)
- _ordering_ (bellek işlemlerinin sıralanması - önceliği sonralığı)
- _visibility_ (bellek işlemlerinin sonuçlarının diğer _thread_'lerden görülmesi)
Sıralı işlem garantisi bellek işlemlerinin diğer _thread_'lerde ne şekilde görülebileceği garantisidir. 
Atomik türler birbirinden bellek işlemlerinin sıralanması konusunda farklı garantiler sunarlar. 
Varsayılan düzen _"sequentially consistency_"'dir. (daha sonra değineceğim)

+ _atomic_  değişkenlerle yapılan işlemler atomik olma garantisini taşırlar. Yani bu işlemler tamamlanıncaya kadar bir başka _thread_ aynı değişken üzerinde işlem yapamaz.
+ _atomic_ bir değişkenin değerinin _(atomik olarak)_ bir arttırıldığını _(increment)_ düşünelim. 
Bu işlem aslında 3 farklı işleme karşılık gelir: oku - değiştir - yaz _(read - modify - write)_. 
Eğer değişkenimizin atomik olma garantisi yok ise bu işlemlerin arasına başka _thread_'lerin işlemleri girebilir. 
Değişkenimiz atomik ise diğer _thread_'ler değişkenimizi ya değiştirilmeden önceki değeri ile ya da değiştirildikten sonraki değeriyle görebilirler, ara bir değerde göremezler. Bir başka deyişle atomik değişkenler için _torn-read_ ya da _torn-write_ olamaz.

#### std::atomic
_std::atomic_ bir sınıf şablonudur. Bu sınıf şablonundan elde edilen türler atomik operasyonlar sunar.

```
template <typename T>
struct atomic;
```
- tam sayı türleri ve _pointer_ türleri için bu sınıfın _partial specialization_'ları var.

- _T_ türünden bir nesne için atomik operasyonlar sağlıyor.
- tüm temel türler _(fundamental types)_ için standart kütüphane tarafından _"full specialization"_ sağlanmış durumda.
- template argümanı olarak kullanılacak türün _"trivially copyable"_ ve _"bitwise equality comparable"_ olması gerekiyor.
- Kilit sistemi kullanılmama _(lock-free)_ olma garantisi verilmiyor. Ancak platformların çoğunda temel türler olan template argümanları söz konusu olduğunda bir kilit sistemi kullanılmadan _(lock-free)_ gerçekleştiriliyor.
- Kopyalama ya da taşıma yoluyla nesne oluşturulamıyor. _(not copy-constructible - not move constructible)_
- Atama yapılabilir _(assignable)_ bir tür. Ancak atama operatörü referans değil değer döndürüyor.
- varsayılan bellek düzeni _(memory order)_ _std::memory_order_seq_cst_.

- #### std::atomic_flag
+ _std::atomic_flag_ türü sadece temel işlemler sunar.
+ Bu türden bir değişken _(flag)_ yalnızca iki durumda olabilir. Ya _set_ edilmiş durumda _(true)_ ya da _clear_ edilmiş durumda (yani _false_)
+ bu tür 2 operasyon sunar:
	- _test_and_set_: _state_'i _true_ yaparken set işleminden önceki değeri sorgular _(get eder)_. 
	- clear: _state_' i _false_ değere çeker.
+ varsayılan kurucu işlev _(default ctor)_ nesneyi belirlenmemiş bir değerle başlatır. 
_C++20_ standartları ile bu durum değişti. _Default ctor_ artık _false_ değeri ile başlatıyor.
+ kopyalanamayan ve taşınamayan bir türdür.
+ derleyiciye bağlı olan _ATOMIC_FLAG_INIT_ makrosu bu türden bir değişkene ilk değer vermek için kullanılır: 
```
std::atomic_flag f = ATOMIC_FLAG_INIT; 
```
- Bir kilit mekanizmasının kullanılmadığı garanti edilmektedir.
- Diğer atomik türlerde olan _is_lock_free_ üye fonksiyonuna sahip değildir (zaten _lock-free_ olmak zorunda).
- _std::atomic_flag_, _spinlock mutex_ gibi daha yüksek seviyeli senkronizsayon mekanizmalarında araç olarak kullanılır.


