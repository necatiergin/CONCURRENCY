+ _std::atomic_flag_ temel atomik işlemler ile gerçekleşitirlen bir bayrak _(flag)_ sunar.
+ bayrak (_std::atomic_flag_ nesnesi) iki durumda _(state)_ olabilir:
	+ _set (yani true)_
	+ _clear (yani false)_

+ _std::atomic_flag_ sadece iki fonksiyona sahiptir:
	+ _test_and_set_: _state_'i _true_ değere çeker ve önceki _state_'i döndürür.
	+ _clear_: _state_'i _false_ değere çeker.

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
