#### std::atomic_flag
+ _std::atomic_flag_ türü sadece temel işlemler sunar.
+ Bu türden bir değişken _(flag)_ yalnızca iki durumda olabilir. Ya _set_ edilmiş durumda _(true)_ ya da _clear_ edilmiş durumda (yani _false_)
+ bu tür 2 operasyon sunar:
	- _test_and_set_: _state_'i _true_ yaparken set işleminden önceki değeri sorgular _(get eder)_. 
	- clear: _state_' i _false_ değere çeker.
+ varsayılan kurucu işlev _(default ctor)_ nesneyi belirlenmemiş bir değerle başlatır. 
_C++20_ standartları ile bu durum değişti. _Default ctor_ artık _false_ değeri ile başlatıyor.
+ kopyalanamayan ve taşınamayan bir türdür.
+ derleyiciye bağlı olan _ATOMIC_FLAG_INIT_ makrosu bu türden bir değişkene ilk değer vermek için kullanılır: 
```
std::atomic_flag f = ATOMIC_FLAG_INIT; 
```
- Bir kilit mekanizmasının kullanılmadığı garanti edilmektedir.
- Diğer atomik türlerde olan _is_lock_free_ üye fonksiyonuna sahip değildir (zaten _lock-free_ olmak zorunda).
- _std::atomic_flag_, _spinlock mutex_ gibi daha yüksek seviyeli senkronizsayon mekanizmalarında araç olarak kullanılır.
