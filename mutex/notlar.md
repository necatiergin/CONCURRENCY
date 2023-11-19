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

Bir _mutex_'in açılması (_mutex_ kilitli iken) yaplan değişikliklerin diğer threadler tarafından erişilebilir olması anlamına gelir.

Bir mutex'in açılması (mutex kilitli iken) yaplan değişikliklerin diğer thread'ler tarafından erişilebilir olması anlamına gelir. <br>

Bir thread bir mutex'i kilitleyerek kritik bölgeye yalnızca kendisinin erişimini sağlar (acquire)<br>
Bir thread bir mutex'i açar: <br>
	- kritik bölgeye erişimi  yalnızca bir başka thread'in erişimine açar. (release)
	- yaptığı değişiklikleri diğer thread'lere sunmuş olur
	- bir başka thread mutex'i kilitler ve değişiklikleri (sonuçları) edinir (aquire).

acquire-release sementiği thradlerin sıralanmasını sağlar.
- data race olmaz.
- paylaşılan veri her zaman tutarlı (consistent) durumdadır.

mutex nesnesi bütün iş yükü (task) fonksiyonlarına görünür olmalıdır.
- global olabilir
- sınıfın veri elemanı olabilir
- fonksiyonlar referans semantiği ile edinebilirler. örneğin lambda ifadeleri ile capture edilebilirler.

mutex sade bir arayğüze sahiptir. <br>
- lock() <br> 
thread mutex'i ya kilitler ya da kilitleyene kadar bekler (bloke olur)
- unlock() <br>
thread mutex'i açar
- try_lock<br>
thread mutex'i kilitlemeyi dener. Başarmazsa bloke olmaz.

