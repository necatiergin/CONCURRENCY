- _mutex_, _thread_'leri kritik bölümden dışlamak için kullanılır. _(exclusion)_
- _thread_'ler _mutex_'e ortak bir şekilde uyralar. _(mutual)_

- Bir _mutex_ sadece 2 durumda olabilir
  - kilitli _(locked)_
  - açık _(unlocked)_

- eğer _mutex_ kilitli değilse bir _thread_ kritik bölgeye girebilir.
- eğer _mutex_ kilitli ise bir _thread_ kritik bölgeye giremez.

- Bir _thread_ kritik bölgeye girdiğinde _mutex_'i kilitler kritik bölgeden çıktığında _kilidi_ açar.
- _mutex_ yalnızca bir kez kilitlenebilir. (bkz. _recursive mutex_)
- Belirli bir anda kritik bölgede yalnızca tek bir _thread_'in bulunması sağlanır.

X, Y, Z thread'lerinin kritik bölgeye girmek istediğini düşünelim.<br>
- X mutex'i kilitler. 
- X kritik bölgeye girer. 
- Y ve Z mutex'i kilitleyecekleri zamana kadar beklerler.
- X kritik bölgeyi terkeder. 
- X kilidi açar. 
- Artık Y ya da Z _mutex_'i kilitleyebilir ve kritik bölgeye girebilir.

Bir _mutex_'in açılması (_mutex_ kilitli iken) yaplan değişikliklerin diğer _thread_'ler tarafından erişilebilir olması anlamına gelir.

Bir mutex'in açılması (mutex kilitli iken) yaplan değişikliklerin diğer _thread_'ler tarafından erişilebilir olması anlamına gelir. <br>

Bir _thread_ bir _mutex_'i kilitleyerek kritik bölgeye yalnızca kendisinin erişimini sağlar _(acquire)_.<br>
Bir _thread_ bir _mutex_'i açar: <br>
	- kritik bölgeye erişimi  yalnızca bir başka thread'in erişimine açar. _(release)_
	- yaptığı değişiklikleri diğer thread'lere sunmuş olur
	- bir başka thread mutex'i kilitler ve değişiklikleri (sonuçları) edinir _(aquire)_.

_acquire-release_ semantiği _thrad_'lerin sıralanmasını sağlar.
- _data race_ olmaz.
- paylaşılan veri her zaman tutarlı _(consistent)_ durumdadır.

_mutex_ nesnesi bütün iş yükü _(task)_ fonksiyonlarına görünür olmalıdır.
- global olabilir.
- sınıfın veri elemanı olabilir
- fonksiyonlar referans semantiği ile edinebilirler. örneğin _lambda_ ifadeleri ile yakalanabilirler.

_mutex_ sade bir arayüze sahiptir. <br>
- lock() <br> 
_thread mutex_'i ya kilitler ya da kilitleyene kadar bekler _(bloke olur)_.
- unlock() <br>
_thread mutex_'i açar.
- try_lock<br>
_thread_ _mutex_'i kilitlemeyi dener. Başaramazsa bloke olmaz. _try_lock_ işlevi tipik olarak aşağıdaki gibi bir döngünün oluşturulmasını sağlar:

```cpp
while (!mtx.try_lock()) {
	// kilitleyemedi tekrar deneyecek
	// burada başka kodlar olabilir
	std::this_thread::sleep(20ms);
}
// kritik bölgeye girdi.
```



