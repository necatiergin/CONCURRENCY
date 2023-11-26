+ std::async fonksiyon şablonu bir "_callable_"ı asenkron olarak çalıştırmak için kullanılır.

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

eğer _future_ nesnesi async işlevi tarafından oluşturulmuş ise: ve _future_ nesnesi _"shared state"_e başvuran son _future_ nesnesiyse, _future_ nesnesi için çağrılan _destructor_ _future_ nesnesi ile ilişkili sonuç hazır olana kadar _thread_'i bloke eder.
