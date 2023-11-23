_std::future_ ve _std::promise_ sınıfları (sınıf şablonları) standart kütüphaneye _C++11_ standartları ile eklendi.;
_std:future_, standart _\<future>_ başlık dosyasında tanımlanmış bir sınıf şablonu. (C++11)
Bir operasyonun sonucunu _(outcome)_ temsil ediyor. (Ya çalıştırılacak bir fonksiyonun geri dönüş değeri ya da çalıştırılacak fonksiyondan gönderilecek _exception_. Ama ikisi birden değil)

_promise_ ve _future_ iki farklı _thread_ arasında bir sonucu (bir değer ya da bir _exception_) iletmek üzere bir kez kullanılacak bir iletişim kanalı oluştururlar:<br>

- _promise_     : Üretilecek sonucu hazırlayacak üretici nesne
- _future_      : sonucun iletilmesinde kulanılacak nesne
- _shared state_: _future_ nesnesi tarafından erişilecek söz verilen değeri tutar. _promise_ ve _future_ nesneleri tatafından birlikte kullanılır.
- sonucu üreten kod _promise_ nesnesini kullanarak sonucu _shared state_'te tutar. Tüketici kod _shared state_'te tutulan sonucu _future_ nesnesini kullanarak alır.

_çok thread_'li programlar, genellikle bazı hesaplamaları _asenkron_ olarakgerçekleştirir. Bu durumda sonuç bir_ thread_ tarafından hazırlanı ve diğer _thread_'in bu sonuca erişmesi gerekir. 
- bu da sonucu üreten ve tüketen _thread_'ler arasında bir senkronizasyon gerektirir.
- sonucu tüketen _thread_ sonuç hazırlanıp kullanılabilir olana kadar beklemelidir.
- _thread_'ler arasında iletilecek sonucu tutan paylaşımlı olarak kullanılacak değişkenlere erişirken "data race"ten kaçınmalıdır.
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
- _promise_ nesnesi ilişkili sonuç belirlenmeden önce yok edilirse ve ilgili _future_ nesnesinden sonuç alınmaya çalışılırsa _std::future_error_ türündne bir hata nesnesi gönderilir.

Sonuç bir _shared state_ içinde tutuluyor. Bu _shared state_ 
+ std::async fonksiyonu tarafından
+ std::packaged_task tarafından
+ std::promise tarafından
  
oluşturulmuş olabilir. 
_std::future_ nesnesi oluşturulduğunda onun tutacağı sonuç henüz hazır olmayabilir. 
Gelecekte oluşacak bir sonucu tutmak için olanaklara sahip.
  
  
Sonuç _std::future_ nesnesi tarafından sadece bir kez _get_ edilebilir. 
Bir kez _get()_ fonksiyonu çağrıldıktan sonra _future_ nesnesi geçersiz hale gelir. <br>

Geçersiz bir _future_ nesnesi için sadece 
+ destructor
+ valid()
+ move assignment

işlevleri çağrılabilir. Başka bir işlevin çağrılması tanımsız davranıştır.


