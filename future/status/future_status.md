#### std::future_status

_std::future_status_ bir _enum class_ _(scoped enum)_. Bu tür _std::future_ sınıfının

- wait_for
- wait_until

fonksiyonlarının geri dönüş türüdür. 
Yani bir _std::future_ nesnesinin _wait_for_ ya da _wait_until_ fonksiyonlarını çağırırsak _std::future_ nesnesinin durum bilgisini elde ederiz. 

```cpp
enum class future_status {
  ready,
  timeout,
  deferred
};
```
Bu değerlerin anlamları şöyledir:

- **deferred** : Fonksiyon henüz çalışmaya başlamamıştır.
- **ready**    : Sonuç hazır durumdadır. (Yani fonksiyon çalıştırılmış değer elde edilmiş ve _promise_ nesnesi set edilmiştir. Yani _future_ nesnesinin _get_ işleviyle bu değer hemen alınabilir.  
- **timeout**  : verilen süre dolmuştur.
