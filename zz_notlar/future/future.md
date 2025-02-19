- _std::future_ ve _std::promise_ sınıfları (sınıf şablonları) standart kütüphaneye _C++11_ standartları ile eklendi.
- _std:future_, standart _\<future>_ başlık dosyasında tanımlanmış bir sınıf şablonu. (C++11)
- _std::future_ bir operasyonun sonucunu _(outcome)_ temsil eder. (Ya çalıştırılacak bir fonksiyonun geri dönüş değeri ya da çalıştırılacak fonksiyondan gönderilecek _exception_. Ama ikisi birden değil)

_promise_ ve _future_ iki farklı _thread_ arasında bir sonucu (bir değer ya da bir _exception_) iletmek üzere bir kez kullanılacak bir iletişim kanalı oluşturur:<br>

- _promise_     : Üretilecek sonucu hazırlayacak üretici nesne.
- _future_      : sonucun iletilmesinde kulanılacak nesne.
- _shared state_: _future_ nesnesi tarafından erişilecek söz verilen değeri tutar. _promise_ ve _future_ nesneleri tarafından birlikte kullanılır.
- sonucu üreten kod _promise_ nesnesini kullanarak sonucu _shared state_'te tutar. Tüketici kod _shared state_'te tutulan sonucu _future_ nesnesini kullanarak alır.

_çok thread_'li programlar, genellikle bazı hesaplamaları _asenkron_ olarak gerçekleştirir. Bu durumda sonucun bir _thread_ tarafından hazırlanıp diğer _thread_'in bu sonuca erişmesi gerekir. 
- bu da sonucu üreten ve tüketen _thread_'ler arasında bir senkronizasyon gerektirir.
- sonucu tüketen _thread_ sonuç hazırlanıp kullanılabilir olana kadar beklemelidir.
- _thread_'ler arasında iletilecek sonucu tutan paylaşımlı olarak kullanılacak değişkenlere erişirken _"data race"_'ten kaçınmalıdır.
- Böyle bir senkronizasyon _promise_ ve _future_ nesneleri ile gerçekleştirilebilir.


```
template <class T> 
class future; 

template <class T > 
class future<T&>;  //partial specialization

template<> 
class future<void>; //void türü için explicit specialization 

```

_std::promise_ sınıfının bildirimi şöyledir: <br>

```
template <class T>
class promise;
```
- _T, promise_ nesnesi tarafından set edilecek  sonucun türüdür. _T_ _void_ türü de olabilir.
- _std::promise_ sınıf nesneleri kopyalanamaz ama taşınabilir.
- sınıfın _set_value_ fonksiyonu üretilecek değeri set eder.
- sınıfın _set_exception_ sonuç nesnesini _exception_ bilgisiyle set eder.
- sonuç sadece bir kez yazılabilir (set edilebilir)
- sınıfın _get_future_ üye fonksiyonu _promise_ ile ilişkilendirilen _future_ nesnesini döndürür.
- _get_future_ fonksiyonu yalnızca bir kez çağrılabilir.
- _promise_ nesnesi ilişkili sonuç belirlenmeden önce yok edilirse ve ilgili _future_ nesnesinden sonuç alınmaya çalışılırsa _std::future_error_ türünden bir hata nesnesi gönderilir.

Sonuç bir _shared state_ içinde tutuluyor. Bu _shared state_ 
+ _std::async_ fonksiyonu tarafından
+ _std::packaged_task_ sınıfı tarafından
+ _std::promise_ sınıfı tarafından
  
oluşturulmuş olabilir. 
_std::future_ nesnesi oluşturulduğunda onun tutacağı sonuç henüz hazır olmayabilir. _future_ nesnesi gelecekte oluşacak bir sonucu tutmak için olanaklara sahip.
  
  
Sonuç _std::future_ nesnesi tarafından sadece bir kez _get_ edilebilir. 
Bir kez _get()_ fonksiyonu çağrıldıktan sonra _future_ nesnesi geçersiz hale gelir. <br>

Geçersiz bir _future_ nesnesi için sadece 
+ destructor
+ valid()
+ move assignment

işlevleri çağrılabilir. Başka bir işlevin çağrılması tanımsız davranıştır.

#### promise sınıfının üye fonksiyonları
::swap  <br>
iki _promise_ nesnesini takas eder.

::get_future <br>
hazırlanacak sonuçla ilişkilendirilen _future_ nesnesini döndürür.<br>

::set_value <br>
sonuç olan değeri (iletilecek değeri) set eder. <br>

::set_value_at_thread_exit <br>
üretilen değeri _thread_ sonlandığında iletir.<br>

::set_exception <br>
sonucu bir _exception_ olarak belirler. <br>

::set_exception_at_thread_exit <br>
üretilen _exception_'u _thread_ sonlandığında iletir. <br>

#### std::future sınıfının üye fonksiyonları
```cpp
void wait()const;
``
Bu fonksiyon, _std::future_ nesnesinin ileteceği değerin hazır olmasını bekler. Değer ya da _exception_ hazırlandığında beklemeyi sonlandırır.
Değer ya da exception hazır olana kadar çağrıldığı _thread_'i bloke eder.

```cpp
std::future_status wait_for(const std::chrono::duration<Rep, Period>& timeout_duration) const;
```
Bu fonksiyon, parametresine geçilen süre boyunca _std::future_ nesnesinin değerinin hazır olmasını bekler. 
Süre dolduğunda veya değer hazır olduğunda beklemeyi sonlandırır. Fonksiyonun geri dönüş türü _std::future enum_ türüdür.
```cpp
enum class future_status {
  ready,
  timeout,
  deferred
};
```

Bu değerlerin anlamları şöyledir:

- **std::future_status::ready**    : Sonuç hazır durumdadır. (Yani fonksiyon çalıştırılmış değer elde edilmiş ve _promise_ değerini almıştır. Yani _future_ nesnesinin _get_ işleviyle bu değer hemen alınabilir.  
- **std::future_status::deferred** : Değer henüz hesaplanmamış ve ertelenmiş durumdadır. Bu durum, _std::async_ ile _std::launch::deferred_ seçeneği kullanıldığında ortaya çıkar.
- **std::future_status::timeout**  : Verilen süre dolmuştur, değer halen hazır değildir.


#### shared_future
- Bir _shared_future_ nesnesi bir _promise_ nesnesi ile ilişkilendirilmiştir. 
- Ancak _std::shared_future_ nesnesi sonucu _(result)_ birden fazla kez sorgulayabilir.
_shared_future_ sınıfı _future_ sınıfları aynı arayüze sahiptir.
_std::future_ nesnesinin _share_ işlevine çağrı yaparak bir _std::future_ nesnesinden bir _shared_future_ nesnesi elde edebiliriz.
- _std::shared_future_ nesneleri _future_ nesnelerinden farklı olarak kopyalanabilir
- _std::future__ nesnesinin içeriğini _shared_future_ nesnesine aktarmak için _future_ sınıfının _share_ üye işlevi kullanılarak _shared_future_ nesnesi elde edilebilir

- sınıfın _get_ işlevi birden fazla kez çağrılabilir.




