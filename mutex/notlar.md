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
