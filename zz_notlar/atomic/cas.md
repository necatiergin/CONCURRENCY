_std::atomic_ sınıfının _compare_exchange_strong_ üye fonksiyonu, atomik bir değişkenin değerini belirli bir koşul altında güncellemek için kullanılır.
Bu fonksiyon, karşılaştırma ve değiştirme _(Compare-and-Swap, CAS)_ işlemini atomik olarak gerçekleştirir. _CAS_ işlemi, _multi-thread_ programlamada senkronizasyon için kullanılır ve veri yarışlarını _(data races)_ önlemek için temel bir araçtır.<br>

_compare_exchange_strong_ fonksiyonu, aşağıdaki adımları yürütür: <br>
Atomik değişkenin var olan değerini belirtilen bir beklenen değer _(expected)_ ile karşılaştırır.<br>
Eğer değerler birbirine eşit ise, atomik değişkenin değerini yeni bir değer _(desired)_ ile günceller, ve _true_ değer döndürür<br>
Eğer değerler eşit değilse, atomik değişkenin var olan değerini _expected_ değişkenine yazar ve _false_ değer döndürür. <br>
 Bu işlem, atomik olarak gerçekleştirilir, yani başka bir _thread_ tarafından kesintiye uğramaz.

fonksiyonun prototipi
```cpp
bool compare_exchange_strong(T& expected, T desired, std::memory_order success = std::memory_order_seq_cst, 
                             std::memory_order failure = std::memory_order_seq_cst);
```

- **expected:** Beklenen değer. Eğer atomik değişkenin değeri bu değere eşit ise, atomik değişkene _desired_ değeri atanır.
- **desired:** Eğer _expected_ değeri atomik değişkenin değerine eşit ise, bu değer atanır.
- **success:** İşlem başarılı olduğunda kullanılacak bellek sıralama _(memory ordering)_ modeli.
- **failure:** İşlem başarısız olduğunda kullanılacak bellek sıralama modeli.
- **dönüş değeri:** İşlem başarılı olduysa **true**, aksi takdirde **false**.

**neden kullanılır? <br>**
- kilitsiz (_lock-free)_ veri yapıları oluşturmak: _std::mutex_ gibi kilitleme mekanizmalarına başvurmadan güvenli güncellemeler yapmak için kullanılır.
- yarış koşullarını _(data race)_ önlemek: paylaşılan bir değişkeni, yalnızca belirli bir koşul sağlandığında güncellemek için uygundur.
- beklenmeyen değişiklikleri algılamak: Eğer başka bir _thread_ aynı değişkeni değiştirmişse, işlem başarısız olur ve tekrar denenebilir.

**_compare_exchange_strong_ ve _compare_exchange_weak_ fonksiyonları arasındaki fark** <br>
_std::atomic_ sınıfının _compare_exchange_weak_ adlı bir başka üye fonksiyonu da vardır. 
_compare_exchange_strong_ ve _compare_exchange_weak_ arasındaki temel fark, _compare_exchange_weak_ fonksiyonunun başarısız olabileceği durumların daha fazla olmasıdır. <br>
_compare_exchange_weak_ fonksiyonunu değişkenin değeri beklenen eşit olsa bile gerçekleşebilir. Bu tür başarısızlıklar, _spurious failures_ ("sahte başarısızlıklar") olarak adlandırılır.<br>
Genel olarak, _compare_exchange_strong_ kullanmak daha güvenlidir. Ancak, bazı durumlarda _compare_exchange_weak_ daha yüksek performans sağlayabilir.
