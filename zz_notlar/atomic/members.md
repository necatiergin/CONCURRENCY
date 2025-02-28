
#### fetch_add üye fonksiyonu

_fetch_add_, _std::atomic_ sınıf şablonunun bir üye fonksiyonudur ve atomik bir şekilde bir değere ekleme yapar.
_fetch_add_, bir atomik nesnenin mevcut değerine, verilen bir artırma miktarını ekler ve işlemin atomik olmasını sağlar. 
Yani, bu işlem sırasında başka bir iş parçacığı aynı değişken üzerinde çakışan bir işlem yapamaz. 
Fonksiyon, ekleme işlemini gerçekleştirmeden önceki eski değeri döndürür.

_std::atomic<T>::fetch_add_ fonksiyonunun genel prototipi şöyledir:

```cpp
T fetch_add(T val, std::memory_order order = std::memory_order_seq_cst) noexcept;
```

- **val**: Atomik nesneye eklenecek değer (artırma miktarı).
- **order**: bellek sıralama düzeni _(memory order)_. Varsayılan olarak _std::memory_order_seq_cst (sequential consistency)_ kullanılır, ancak performans için daha gevşek sıralama düzenleri de (örneğin _std::memory_order_relaxed_) kullanılabilir.<br>
- **geri dönüş değeri**: İşlemden önceki atomik nesnenin eski değeri _(T türünde)_.
işlem atomiktir; yani kesintiye uğramaz ve diğer _thread_'ler ile çakışma olmadan tamamlanır.<br>
_noexcept_ olarak nitelenmiştir yani bu fonksiyon _exception_ göndermez. <br>
_std::atomic<T>_  sınıf şablonunun yalnızca tam sayı türleri _(örneğin int, long, char)_ ve _pointer_ türleri için açılımlarında _(specialization) fetch_add_ fonksiyonunu vardır. Gerçek sayı türleri _(float, double, long double)_ için bu fonksiyon tanımlı değildir.
- **bellek sıralama (memory order)**: Bellek sıralama, _thread_'ler arasındaki operasyonların nasıl senkronize edileceğini belirler. 
Varsayılan argüman _std::memory_order_seq_cst_, en katı sıralamayı sağlar ve tüm _thread_'lerde tutarlı bir yürütme sırası garanti eder. 
Daha gevşek sıralamalar _(örneğin std::memory_order_acquire veya std::memory_order_relaxed)_ ise performansı artırabilir, ancak dikkatli kullanılmalıdır.
