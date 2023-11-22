#### nedir?
_std::scoped_lock_ bir ya da birden fazla _mutex_'i edinebilen (kilitleyebilen) bir _RAII_ sınıfı.<br>

```cpp
template <typename ...Ts>
class scoped_lock {
    //...
}
```
- parametre paketi olan _Ts_ edinilecek _mutex_'lerin türleribi belirliyor.
- gerekli olan kilitleme ve kildi açma arayüzüne sahip tüm _mutex_ türleri ile kullanılabilir.
- sınıfın kurucu işlevi bir ya da birden fazla _mutex_'i argüman olarak alıyor.
- _mutex_'ler sınıfın kurucu işlevi tarafından ediniliyor sınıfın _destructor_'ı tarafından serbest bırakılıyor.
- _std::scoped_lock_ nesneleri kopyalanamz ve taşınamaz.
- _mutex_'lerin serbest bırakılmasının ihmal edilmesi ya da bir _exception_ gönderilmesi nedeniyle _mutex_'in serbest bırakılmaması riskini ortadan kaldırıyor.
- birden fazla _mutex_'in edinilmesi durumunda _deadlock_'tan kaçınan bir algoritma kullanılıyor. Yani _mutex_'lerin hangi _thread_'de hangi sırayla edinildiğinin bir önemi yok.
- _mutex_ sınıf nesnesinin _lock_ ve _unlock_ fonksiyonlarının çağrılması yerine _scoped_lock_ sınıfı kullanılmalı.
- _scoped_lock _sınıfı bir verim/performans kaybı olmadan _std::lock_guard_ sınıfının yerine geçiyor ve onun arayüzünü genişletiyor.
