#### std::unique_lock

- _std::unique_lock_,  bir _mutex_'i sarmalayan başka bir _RAII_ sınıf şablonu. Bildirimi şöyle:

```
template <class T> 
class unique_lock;
```

- template parametresi sarmalanacak _mutex_'in türü _(std::mutex, std::timed_mutex, std::recursive_mutex, vs)_. 
- _std::scoped_lock_ ya da _std::lock_guard_'dan farklı olarak _std::unique_lock_ nesneni tüm hayatı boyunca _mutex_'i tutmak zorunda değil.
- _mutex_'in sınıfın kurucu işlevi tarafından edinilip edinilmemesi konusunda farklı seçenekler sağlar.
- _std::unique_lock_ nesnesi sarmaladığı _mutex_'i (kendi hayatı boyunca) birden fazla kez edinip serbest bırakabilir.
- sınıfın _destructor_'u çağrıldığında sarmalanan _mutex_ halen kilitli durumdaysa kilidi serbest bırakır.
- _std::unique_lock_ nesneleri taşınabilir ama kopyalanamaz.
- _mutex_ nesnesinin serbest bırakılmama ihtimalini ortadan kaldırır..
- mülkiyeti aynı türden başka bir nesneye devredebilir.
- _std::unique_lock_ döndüren bir fabrika fonksiyonu yazılabilir.


_std::lock_guard_'a göre daha esnek kullanım olanakları sağlar. <br>
_default_ olarak edindiği _mutex_'in _lock_ fonksiyonu çağırır. <br>
Sınıfın _constructor_'ına _mutex_ nesnesi dışında ikinci bir argüman geçilebilir.<br>
istenirse _mutex_'i edinmeden bir _unique_lock_ nesnesi oluşturulabilir. Bunun için _constructor_'ın ikinci parametresine _std::defer_lock_ sabiti geçilmelidir.
```cpp
{
	std::mutex mtx;
	std::unique_lock lock(mtx, std::defer_lock);
	// bazı kodlar
	lock.lock(); // mutex'i şimdi kilitle
	// krtitik bölge
	lock.unlock(); // mutex'in kilidini aç
	//bazı kodlar
}
```

_unique_lock_ nesnesinin  edindiği _mutex_'in _try_lock_ fonksiyonunu çağırması sağlanabilir. Bunun için _ctor_'ın ikinci parametresine _std::try_lock_ sabiti geçilmelidir:
```cpp
{
	std::mutex mtx;
	std::unique_lock  lock(mtx, std::try_to_lock);
	if (lock.owns_lock()) {
		// ... korunan koda erişim ...
	}
	else {
		// Mutex kilitlenemedi
	}
}
```

_unique_lock_ nesnesi zaten kilidi edinmiş bir _mutex_ ile hayata başlatılabilir. Bunun için _constructor_'ın ikinci parametresine _std::adopt_lock_ sabiti geçilmelidir.<br>
+ sınıfın _owns_lock_ ya da _operator bool_ fonksiyonları ile _mutex_'in edinilmiş olup olmadığı sınanabilir. <br>

##### Sınıfın try_lock_for ve try_lock_until fonksiyonları
_try_lock_for_ ve _try_lock_until_ fonksiyonları, _mutex_'in kilitlenmesini garanti etmezler. Bu fonksiyonlar sadece belirli bir süre veya zamana kadar _mutex_'i kilitlemeyi denerler. Mutex'in kilitlenmesinin garanti edilmesi gerekiyorsa,sınıfın _lock_ fonksiyonu kullanılmalıdır. Ancak, _lock_ fonksiyonu _mutex_ kilitlenene kadar ilgili _thread_'i bloke eder.
**try_lock_for fonksiyonu**<br>
```cpp
bool try_lock_for(const std::chrono::duration<Rep, Period>& rel_time);
```
_mutex_'i belirli bir süre boyunca kilitlemeye çalışır. Verilen süre içinde _mutex_'i kilitleyebilirse _true_ değer döndürür. Başarısız olursa, yani verilen süre içinde _mutex_'i kilitleyemezse _false_ değer döndürür.


Sınıfın _mutex_'i edinmek ve serbest bırakmak için sunduğu üye fonksiyonlar şunlar:
- ::lock()
- ::try_lock()
- ::try_lock_for()
- ::try_lock_until()
- ::unlock()

- Sınıfın _::mutex_type_ içsel türü template argümanı olan _mutex_ türüne eş isim.

