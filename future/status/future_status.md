#### std::future_status

_std::future_status_ bir _enum class_. Bu tür _std::future_ sınıfının
- wait_for
- wait_until

fonksiyonlarının geri dönüş türüdür. Yanibir _std::future_ nesnsinin _wait\_for_ ya da _wait\_until_ fonksiyonlarını çağırırsak _std::future_ nesnesinin durum bilgisini elde ederiz. 

```
enum class future_status {
  ready,
  timeout,
  deferred
};
```
Bu değerlerin anlamları şöyledir:

- **deferred** : fonksiyon henüz çalışmaya başlamamıştır.
- **ready**    : sonuç hazır durumdadır. (yani fonksiyon çalıştırılmış değer elde edilmiş ve _promise_ nesnesi set edilmiştir. Yani _future_ nesnesinin _get_ işleviyle bu değer hemen alınabilir.  
- **timeout**  : verilen süre dolmuştur.
