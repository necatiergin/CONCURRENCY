- _<shared_mutex>_ başlık dosyasında tanımlanmıştır.
- iki ayrı şekilde kilitlenebilir: <br>
exclusive<br>
 - yalnızca tek bir _thread_ kilidi edinebilir.
 - yalnızca tek bir _thread_ kritik bölgeye girebilir.
paylaşımlı <br>
birden fazla _thread_ kilidi edinebilir. <br>
birden fazla _thread_ kritik bölgeye girebilir.  <br>
_mutex_'i _exclusive_ olarak edinmek için _std::lock_guard_ ya da _std:unique_lock_ ile sarmalamak yeterli.

```cpp
std::lock_guard<std::shared_mutex>
std::lock_guard<std::shared_mutex>
```
Bu durumda sadece _mutex_'i edinen _thread_ kritik bölgeye girebilir. Diğer _thread_'ler _mutex_ serbest bırakılıncaya kadar beklemek zorunda. <br>

- _mutex_'in _exclusive_ olarak edinilebilmesi için _mutex_'in kilitli olmaması gerekir.
- eğer başka bir _thread_ paylaşımlı ya da paylaşımsız olarak kilidi edinmişse diğer bütün _exclusive _thread_'ler kilidi edinen _mutex_ kilidi serbest bırakana kadar beklemek zorunda.
mutexin paylaşımlı olarak edinilebilmesi için bir shared_lock nesnesi oluşturmamız gerekiyor.
bir shared_lock nenseine sahip bir threadf kritik bölgeye girebilri
paylaşımlı olarak kilidi edinebilmek için kilidin exclusive olarak sahibi olan bir thread olmamalı
exlucive sahip kilidi serbest bırakana kadar beklemek zorund<a


writer thread'in eclusive lock alabilmesiiçin diğer bütün threadlerin kilidi relaase etmiş olması gerekir.
Bu durum diğer tüm thread'lerin kritik bölgeyi terk etmiş olduğu anlamına gelir

bir write thread kilidi edindiğinde
- kritik bölgeye girmiş olur.
- reader thread'ler kritik bölgeye giremez
- writer threadler kilidi elde edemz
- bunların olabilmesi için kilidi almış olan write thread'in kilidi serbest bırakması gerekir


writer threadin kilidi bırakmış olması kritik bölgeyi terk etmiş olduğu anlamına gelir


reader thread

kilidi elde bulunduruan birwrite thread kilidi bırakana kadar kilidi edineme<
bir reader thread kilidi edinmişse write threadkrtiik bölgeyi terk etmiş demektir.

reader thread kilidi edindiğinde 
kritik bölgeye girer.
diğer reader thread'ler de kilidi edinebilir. (shared lock)

Data race oluşacak bir senaryok söz konusu değildir

readrt ve writer threadler bir arada kritik bölgede olamazlar

bu da bir thread değişiklik yaptığında diğer threadleri n kritik bölgede olaayaxağı anlamına gelir



std::shared_mutex std::mutex'e göre daha fazla bellek alanı kullanır.
std::mutex'e göre daha yavaştır.

- reader thread'lerin sayısının write thread'lerden çok daha fazla olması durumunda
- read işlemlerinin çok fazla zaman alması durumunda tercih edilebilir






