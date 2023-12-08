#### std::atomic
_std::atomic_ bir sınıf şablonudur. Bu sınıf şablonundan elde edilen türler atomik operasyonlar sunar.

```
template <typename T>
struct atomic;
```
- tam sayı türleri ve _pointer_ türleri için bu sınıfın _partial specialization_'ları var.

- _T_ türünden bir nesne için atomik operasyonlar sağlıyor.
- tüm temel türler _(fundamental types)_ için standart kütüphane tarafından _"full specialization"_ sağlanmış durumda.
- template argümanı olarak kullanılacak türün _"trivially copyable"_ ve _"bitwise equality comparable"_ olması gerekiyor.
- Kilit sistemi kullanılmama _(lock-free)_ olma garantisi verilmiyor. Ancak platformların çoğunda temel türler olan template argümanları söz konusu olduğunda bir kilit sistemi kullanılmadan _(lock-free)_ gerçekleştiriliyor.
- Kopyalama ya da taşıma yoluyla nesne oluşturulamıyor. _(not copy-constructible - not move constructible)_
- Atama yapılabilir _(assignable)_ bir tür. Ancak atama operatörü referans değil değer döndürüyor.
- varsayılan bellek düzeni _(memory order)_ _std::memory_order_seq_cst_.
