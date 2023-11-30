std::atomic_flag temel atomik işlemler ile gerçekleşitirlen bir flag sağlar.
bayrak (std::atomic_flag nesnesi) iki durumda olabilir:
set (yani true)
clear (yani false)

+ atomic_flag sadece iki fonksiyona sahiptir:
	+ test_and_set: state'i true değere çeker ve önceki state'i döndürür.
	+ clear: state'i false değere çeker.

+ Sınıfın default ctor'ı belirlenmemiş bir değer ile başlatır.
+ atomic_flag nesneleri kopyalanaaz ve taşınamaz


ATOMIC_FLAG_INIT makrosu derleyiciey bağlıdır.

Aşağıdaki şekilde kullanılır:
+ static ya da otomatik ömürlü std::atomic_flag değişkenini "false" değeriyle başlatmak için aşağıdaki şekilde kullanılır.
```cpp
std::atomic_flag f = ATOMIC_FLAG_INIT;
```

+ lock-free olma garantisi vardır
+ spinlock mutex gibi daha üst düzey senkronizasyon ilkelleri için yapı taşı olarak kullanılmak üzere tasarlanmıştır.
