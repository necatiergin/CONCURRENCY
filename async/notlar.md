+ _std::async_ fonksiyon şablonu bir "_callable_"ı asenkron olarak çalıştırmak için kullanılır.

İki ayrı yükleme _(overload)_ var:

+ varsayılan çalıştırma stratejisi _(default launch policy)_

```
template <class Func, class... Args>
future<typename result_of<typename decay<Func>::type(typename decay<Args>::type...)>::type>
async(Func&& f, Args&&... args);
```

+ çalıştırma stratejisi _(launch policy)_ isteyen :

```
template <class Func, class... Args>
future<typename result_of<typename decay<Func>::type(typename decay<Args>::type...)>::type>
async(launch policy, Func&& f, Args&&... args);
```

+ çalıştırma stratejisi _std::launch_ türünden bit maskeleri (sabitler) ile belirlenir:
- eğer _asynch_ biti set edilmiş ise _"callable"_ yeni bir _thread_'de çalıştırılır.
- eğer _deferred_ biti set edilmiş ise _"callable"_ ana _thread_'de sonuca ihtiyaç duyulduğu zaman çalıştırılır.
- eğer iki bit de set edilmiş ise implementasyon herhangi bir çalıştırma biçimini seçmekte özgürdür.

+ asenkron çalıştırma durumunda arka planda bir _promise_ ve bir _future_ nesnesi oluşturulmaktadır.
+ _asynch_ tarafından oluşturulan _future_ nesnesi diğer yollarla oluşturulan _future_ nesnelerinden daha farklı davranır.

eğer _future_ nesnesi _async_ işlevi tarafından oluşturulmuş ise: ve _future_ nesnesi _shared state_'e başvuran son _future_ nesnesi ise, _future_ nesnesi için çağrılan _destructor_ _future_ nesnesi ile ilişkili sonuç hazır olana kadar _thread_'i bloke eder.

+ Aslında _std::async_ başlatma ilkesiyle, _future::get()_ işlevini çağırmamız gerekmez. Fonksiyonun döndürmüş olduğu _std::future_ nesnesinin hayatı bittiğinde, program iş yükünün bitmesini bekleyecektir. Bu nedenle, _std::future_ nesnesinin get() işlevini çağırmazsanız, _future_ nesnesinin kapsamının sonunda arka plan görevinin sona ermesini bekleyecektir. Yine de, program sona ermeden önce _get()_ işlevini çağırmak davranışı daha net hale getirir.

+ _std::async_ işlevinin asenkron çalıştırıp işlevin geri dönüş değerini bir değişkene atamadığımızı düşünelim. Bu durumda çağrıyı yapan _thread_ çağrılan işlevin çalışması bitene kadar bloke olur. Bu da fonksiyonun senkron olarak çalıştırıldığı anlamına gelir.

#### hangi durumlarda launch::async seçilmeli:
+ _task_'in ayrı bir _thread_ olarak çalıştırılması gerekiyor ise.
+ _task_'in hemen başlatılması gerekiyor ise (yani get çağrıldığında değil hemen)
+ _task_'in _thread_local_ değişkenleri kullanması gerekiyor ise
+ get fonksiyonu çağrılmasa dahi _task_'in yürütülmesi gerekiyor ise
+ _future_ nenesini alan _thread_,  _future_ nesnesinin _wait_for_ ya da _wait_until_ fonksiyonlarını çağıracak ise


