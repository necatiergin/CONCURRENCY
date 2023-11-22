#### std::unique_lock

- _std::unique_lock_,  bir _mutex_'i sarmalayan başka bir _RAII_ sınıfı. Bildirimi şöyle:

```
template <class T> 
class unique_lock;
```

- template parametresi sarmalanacak _mutex_'in türü _(std::mutex, std::recursive_mutex)_. 
- _std::scoped_lock_ ya da _std::lock_guard_'dan farklı olarak _std::unique_lock_ nesneni tüm hayatı boyunca _mutex_'i tutmak zorunda değil.
- _mutex_'in sınıfın kurucu işlevi tarafından edinilip edinilmemesi konusunda farklı seçenekler sağlıyor.
- _std::unique_lock_ nesnesi sarmaladığı _mutex_'i (kendi hayatı boyunca) birden fazla kez edinip serbest bırakabilir.
- sınıfın _destructor_'u çağrıldığında sarmalanan _mutex_ halen kilitli durumdaysa kilidi serbest bırakır.
- _std::unix_lock_ nesneleri taşınabilir ama kopyalanamaz.
- _mutex_ nesnesinin serbest bırakılmama ihtimalini ortadan kaldırıyor.
- mülkiyeti aynı türden başka bir nesneye devredebiliyor.
- _std::unique_lock_ döndüren bir fabrika fonksiyonu yazılabilir.


+ _std::lock_guard_'a göre daha esnek.
+ ctor'a argüman verebiliyoruz.
  - default olarak edindiği _mutex_'in _lock_ fonksiyonu çağırıyor.
  - istersek edindiği mutex'in _try_lock_ fonksiyonunu çağırabiliyor. Bunun için ctor'ın ikinci parametresine _std::try_lock_ sabitini argüman olarak geçiyoruz.
  - istersek _mutex_'i edinmeden başlatabliyoruz. Bunun için _constructor_'ın ikinci parametresine _std::defer_lock_ sabitini argüman olarak geçiyoruz.
  - istersek zaten kilidi edinmiş bir _mutex_ ile başlatabiliyoruz. Bunun için _constructor_'ın ikinci parametresine _std::adopt_lock_ sabitini argüman olarak geçiyoruz.
+ _owns_lock_ isimli üye fonksiyonu çağırarak _mutex_'in edinilmiş olup olmadığını sınayabiliyoruz. 

Sınıfın _mutex_'i edinmek ve serbest bırakmak için sunduğu üye fonksiyonlar şunlar:
- ::lock()
- ::try_lock()
- ::try_lock_for()
- ::try_lock_until()
- ::unlock()

- Sınıfın _::mutex_type_ içsel türü template argümanı olan _mutex_ türüne eş isim.


