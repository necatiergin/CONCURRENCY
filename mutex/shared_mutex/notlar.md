- _<shared_mutex>_ başlık dosyasında tanımlanmıştır.
- iki ayrı şekilde kilitlenebilir: <br>
exclusive<br>
 - yalnızca tek bir thread kilidi edinebilir.
 - yalnızca tek bir thread kritik bölgeye girebilie.
paylaşımlı <br>
- birden fazla thread kilidi edinebilir.
 - birdenfazla thread kritik bölgeye girebilir.

_mutex_'i exclusive olarak edinmek için _std::lock_guard_ ya da _std:unique_lock_ ile sarmalamak yeterli.

```cpp
std::lock_guard<std::shared_mutex>
std::lock_guard<std::shared_mutex>
```

Bu durumda sadece mutex'i edinen thread kritik bölgeye girebilir.
Diğer thread'ler mutex serbest bırakılıncaya kadar beklemek zorunda.

mutexin exclusive olarak edinilebilmesi için mutex'in kilitli olmaması gerekir.
eğer başka bir shared paylaşımlı ya da paylaşımsız olarak kilidi edinmişse diğer bütün threadler kilidi serbest bırakana kadar beklemek zorunda.
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






