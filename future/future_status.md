#### std::future_status

_std::future_status_ bir _enum class_. Bu tür std::future sınıfının
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
- **ready**    : sonuç hazır durumdadır. (yani fonksiyon çalıştırılmış değer elde edilmiş ve _promise_ nesnesi set edilmiştir. Yani future nesnesinin get işleviyle bu değer hemen alınabilir.  
- **timeout**  : verilen süre dolmuştur.
