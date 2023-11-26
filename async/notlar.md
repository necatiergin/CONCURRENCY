+ std::async fonksiyon şablonu bir "callable"ı asenkron olarak çalıştırmak için kullanılır.

İki ayrı yükleme (overload) var

+ varsayılan çalıştırma stratejisi

```
template <class Func, class... Args>
future<typename result_of<typename decay<Func>::type(typename decay<Args>::type...)>::type>
async(Func&& f, Args&&... args);
```

çalıştırma stratejisi isteyen

```
template <class Func, class... Args>
future<typename result_of<typename decay<Func>::type(typename decay<Args>::type...)>::type>
async(launch policy, Func&& f, Args&&... args);
```

+ std::launch türünden bitmask sabitler ile çalıştırma stratejisi belirlenir.

- eğer asynch biti set edilmiş ise "callable" "yeni bir thread'de çalıştırılır.
- eğer deferred biti set edilmiş ise "callable" ana thread'de sonuca ihtiyaç duyulduğu zaman çalıştırılır.
- eğer iki bit de set edilmiş ise implementasyon herhangi bir çalıştırma biçimini seçmekte özgürdür.

+ asenkron çalıştırma durumunda arka planda bir promise ve bir future nesnesi oluşturulmaktadır.
+ asynch tarafından oluşturulan future nesnesi diğer yollarla oluşturulan future nesnelerinden daha farklı davranır.

eğer future nesnesi async işlevi tarafından oluşturulmuş ise: ve future nesnesi "shared state'e başvuran son future nesnesiyse, future nesnesi için çağrılan destructor future nesnesi ile ilişkili sonuç hazır olana kadar thread'i bloke eder.
