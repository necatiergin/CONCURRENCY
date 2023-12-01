+ _std::atomic_flag_ temel atomik işlemler ile gerçekleşitirlen bir bayrak _(flag)_ sunar.
+ bayrak (_std::atomic_flag_ nesnesi) iki durumda _(state)_ olabilir:
	+ _set (yani true)_
	+ _clear (yani false)_

+ _std::atomic_flag_ sadece iki fonksiyona sahiptir (C++20 ilw ywni fonksiyonlar eklendi)
	+ _test_and_set_: _state_'i _true_ değere çeker ve önceki _state_'i döndürür.
	+ _clear_: _state_'i _false_ değere çeker.

+ sınıfın _default ctor_'ı nesneyi hayata belirlenmemiş bir değer ile başlatır. (C++20 standardı ile bu değiştirildi. Artık default ctor'ın nesneyi false değer ile başlatma garantisi geldi.)

+ _atomic_flag_ nesneleri kopyalanamaz ve taşınamaz.

+ _ATOMIC_FLAG_INIT_ makrosu derleyiciye bağlıdır. _static_ ya da otomatik ömürlü _std::atomic_flag_ değişkenini _"false"_ değerle başlatmak için aşağıdaki şekilde kullanılır.
```cpp
std::atomic_flag f = ATOMIC_FLAG_INIT;
```

+ Diğer atomik türlerden farklı olarak _lock-free_ olma garantisi vardır
+ _spinlock mutex_ gibi daha üst düzey senkronizasyon ilkelleri için yapı taşı olarak kullanılmak üzere tasarlanmıştır.
+ C++ 20 standardı ile sınıfa yeni üye fonksiyonlar eklendi.
