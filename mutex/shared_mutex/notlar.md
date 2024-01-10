- _<shared_mutex>_ başlık dosyasında tanımlanmıştır.
iki ayrı şekilde kilitlenebilir: <br>
- _exclusive (write)_<br>
  - yalnızca tek bir _thread_ kilidi edinebilir.<br>
  - yalnızca tek bir _thread_ kritik bölgeye girebilir.<br>
- _paylaşımlı_ <br>
  - birden fazla _thread_ kilidi edinebilir. <br>
  - birden fazla _thread_ kritik bölgeye girebilir.  <br>
_mutex_'i _exclusive_ olarak edinmek için _std::lock_guard_ ya da _std:unique_lock_ ile sarmalamak yeterli.

```cpp
std::lock_guard<std::shared_mutex>
std::unique_lock<std::shared_mutex>
```
Bu durumda sadece _mutex_'i edinen _thread_ kritik bölgeye girebilir. Diğer _thread_'ler _mutex_ serbest bırakılıncaya kadar beklemek zorunda. <br>

- _mutex_'in _exclusive_ olarak edinilebilmesi için _mutex_'in kilitli olmaması gerekir.
- eğer başka bir _thread_ paylaşımlı ya da paylaşımsız olarak kilidi edinmişse diğer bütün _exclusive _thread_'ler kilidi edinen _mutex_ kilidi serbest bırakana kadar beklemek zorunda.
- _mutex_'in paylaşımlı olarak edinilebilmesi için bir _shared_lock_ nesnesi oluşturmamız gerekiyor.
- bir _shared_lock_ nesnesine sahip bir _thread_ kritik bölgeye girebilir.
- paylaşımlı olarak kilidi edinebilmek için kilidin _exclusive_ olarak sahibi olan bir _thread_ olmamalı
- _exclusive_ olarak kilide sahip _thread_ serbest bırakana kadar beklemek zorunda.

_writer thread_'in exclusive olarak kilidi edinebilmesi için diğer bütün _thread_'lerin kilidi serbest bırakmış olması gerekir.
Bu durum diğer tüm _thread_'lerin kritik bölgeyi terk etmiş olduğu anlamına gelir.<br>

bir _exclusive thread_ kilidi edindiğinde
- kritik bölgeye girmiş olur.
- _reader thread_'ler kritik bölgeye giremez.
- _writer thread_'ler kilidi elde edemez.
- bunların olabilmesi için kilidi almış olan _writer thread_'in kilidi serbest bırakması gerekir.
- _writer thread_'in kilidi bırakmış olması kritik bölgeyi terk etmiş olduğu anlamına gelir.

#### reader thread

- kilidi elde bulunduran bir _exclusive thread_ kilidi bırakana kadar kilidi edinemez.
- bir _reader thread_ kilidi paylaşımlı olarak edinmişse _exclusive thread_ kritik bölgeyi terk etmiş demektir.
- bir _reader thread_ kilidi paylaşımlı olarak edinmişse diğer _reader thread_'ler de paylaşımlı aynı kilidi edinebilir.

_reader thread_ kilidi edindiğinde 
- kritik bölgeye girer.
- diğer tüm _reader thread_'ler de kilidi edinebilir. _(shared lock)_
- _data race_ oluşacak bir senaryo söz konusu değildir
- _reader_ ve _writer_ _thread_'ler bir arada kritik bölgede olamazlar.
- bu da bir _thread_ değişiklik yaptığında diğer _thread_'lerin kritik bölgede olamayacağı anlamına gelir.

#### ne zaman kullanılmalı?
_std::shared_mutex_ _std::mutex_'e göre daha fazla bellek alanı kullanır.
- _std::mutex_'e göre daha yavaştır.
- _reader thread_'lerin sayısının _writer thread_'lerden çok daha fazla olması durumunda ya da okuma işlemlerinin çok fazla zaman alması durumunda tercih edilebilir.

#### interface

```
std::shared_mutex::lock();
std::shared_mutex::try_lock();
std::shared_mutex::unlock();

std::shared_mutex::lock_shared();
std::shared_mutex::try_lock_shared();
std::shared_mutex::unlock_shared();
```






