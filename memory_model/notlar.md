#### memory model nedir?

+ bilgisayar programının belleğe erişiminde izin verilebilen semantik yapıyı tanımlar.
- bellekten bir okuma yapıldığında hangi değer /değerler okunabilir? (hangi değerlerin okunması beklenebilir?)
- hangi durumlarda tanımsız davranış oluşabilir?
- memory model, _multithread_ programlar için kritik olan bir bileşendir.
- _thread_'ler bellek ve paylaşılan veril(ler) ile nasıl etkileşime giriyor? Bellek programa ve programda kullanılan _thread_'lere nasıl görünüyor?
- _multi-thread_ programların yürütülmesine ilşkin kuralların belirlenebilmesi için programlama dilinin bir _memory model_ oluşturulması gerekiyor.

_thread_'ler, programın çalışma zamanında paylaşılan verileri farklı değerlerde görebilir. 
bir _memory model_ oluşturmadan derleyici optimizasyonları ve donanım tarafında yapılan optimizasyonlar sorunlar oluşturabilir. 
_thread_'lerin paylaşılan değişkenlerde yapılan değişiklikleri anında gözlemleyebilmeleri verim _(efficiency)_ açısından  yüksek bir maliyet oluşturur.<br>

kaynak kodumuzdaki işlemler: 
- derleyici tarafından
- CPU tarafından;
- bellek _(caching)_ tarafından yeniden sıralanabilir

_memory model_ hangi durumlarda yeniden sıralamaya _(reordering)_ izin verilip verilmediğini belirler. 
- Birden fazla _thread_ hangi durumlarda paylaşılan değişkenlere erişebilir? 
- Bir _thread_ tarafından bir değişkene yapılan atama eş zamanlı çalışan _thread_'ler tarafından ne zaman görünür olacak?
- Programcılar _multi thread_ programların nasıl çalışacağını (belirli garantiler altında) kestirebilmeliler. _memory model_ bunu sağlıyor.

- C++11 öncesinde C++ dilinden formal bir bir _memory model_ yoktu. C++ soyut makinesi _(abstract machine)_ _single-thread_ olarak tasarlanmıştı. _java memory model_ 1995 yılında oluşturuldu. Yaygın kullanılan programlama dilleri içinde bu açıdan Java bir ilk oldu. 
_pthreads_ kütüphanesi ilk olarak 1995 yılında, bir _memory modele_ dayanmadan geliştirildi. _Posix_, _memory model_ oluşturmuyor. Tanımlar kesin _(precise)_ değil. Yani, "program doğru mu" sorusunun formal bir cevabı yok. İlk olarak C++ dilinde java'nın memory modelinin kullanılması düşünüldü, ancak bunun uygun olmadığı görüldü (fazla kısıtılayıcı). Java memory modeli belirli veri türlerinin atomik olmasını gerektiriyor. Java memory model C++ için çok pahalı. Bir thread library oluşturabilemek için derleyici üstünde bazı kısıtlamaların olması gerekiyor. Bunun için de bir memory model'e ihtiyaç duyuluyor.

Bir programın çalışma zamanında nasıl davranacağını kestirebilmemiz için şunları bilebilmemiz gerekir:
- programdaki (farklı _thread_'ler tarafından gerçekleştirilebilecek) işlemlerin _(operasyonların)_ hangi sırayla yürütüleceği _(ordering)_
- programdaki bir işlemin/işlemlerin sonuçlarının (başka _thread_'ler tarafından yürütülebilecek) diğer bir işlem/işlemler yapılmadan görülür olup olmadığı _(visibility)_

Tek bir _thread_'in söz konusu olduğu programlarda yukarıdaki soruların cevabı sezgisel olarak verilebilir.
Birden fazla _thread_'in söz konusu olduğu programlarda ise bu durum çok daha karmaşıktır.

#### happens-before ilişkisi

_A_ ve _B_ iki operasyon olsun. Bu operasyonlar aynı _thread_'de gerçekleştirilen operasyonlar olabildiği gibi farklı _thread_'lerde gerçekleştirilen operasyonlar da olabilir. Eğer _A_ operasyonunun etkileri _B_ operasyonunu yürütecek _thread_'de _B_ operasyonu yürütüldüğünde görülür durumda ise

**A happens before B** <br>

garantisi söz konusudur.

**_happens-before_ ilişkisi "zamansal olarak daha önce gerçekleşme" ilişkisine göre çok daha güçlü bir durumdur.**

Eğer _A_ operasyonu _B_ operasyonuna göre zamansal açıdan daha önce gerçekleştiriliyor ise bu _A_'nın etkilerinin _B_'yi yürütecek _thread_'de _B_ yürütülmeden önce görülür olma garantisi değildir. _caching_, _store buffer_ vs gibi mekanizmalar operasyonun etkilerinin diğer _thread_'lerde görülmesini geciktirebilir.

#### sequenced before ilişkisi
_sequenced-before_ ilişkisi aynı _thread_'deki işlemlere ilişkindir.

- _Sequenced-before_ ilişkisi geçişkendir _(transitive)_ 
A _sequenced before_ B  doğru ise
B _sequenced before_ C  doğru ise
A _sequenced before_ C  doğrudur.

```
x = 1; 		// A
y = 2; 		// B
z = x + 1;	// C
```

Aşağıdaki kodu ele alalım:<br>

```
y = a * x + b; // (y = ((a * x) + b);
```
Bu ifadede 3 işlem var: çarpma toplama ve atama. Burada<br>
çarpma işlemi  _sequenced before_ toplama işlemi <br>
toplama işlemi _sequenced before_ atama işlemi <br>
dolayısıyla <br>
atama işlemi _sequenced before_ toplama işlemi <br>

Eğer bir _thread_ için <br>
A _sequenced before_ B doğru ise <br>
A _happens before_ B doğrudur.<br>

Bu şu anlama geliyor:<br>
_sequenced-before_ ilişkisi aynı zamanda _thread_ içindeki _(intra-thread)_ happens before ilişkisine karşılık geliyor.<br>

- _happens-before_ ilişkisi zamana bağlı değildir, görünürlüğe _(visibility)_ bağlıdır.
- _A happens before B_ ise, bu A'nın B'de önce yapılması anlamına gelmez (böyle bir garanti yoktur).
- A B'den önce yapılmış ise _A happens-before B_ olmak değildir.
- happens-before ilişkisi _acquire-release_ semantiği ile gerçekleştirilebilir. (Daha sonra ele alacağım)

**Happens-Before Does Not Imply Happening Before!**

Aşağıdaki koda bakalım:
```
#include <iostream>

int is_ready{ 0 };
int value{0};

void producer()
{
    value = 42;                         // (1)
    is_ready = 1;                       // (2)
}

void consumer()
{
    if (is_ready)                       // (3) Burada okunan değerin 1 olduğunu düşünelim
        std::cout << value;             // (4)
}
```
Buradaki fonksiyonlar iki ayrı _thread_ tarafından çalıştırılıyor olsun. Değişkenlere yapılan atamalar _(stores)_ ve değişkenlerden yapılan okumalar _(loads)_ atomik olsun. Programın çalışma zamanında _consumer thread_'inin **(3)** noktasına geldiğini ve _is_ready_ değişkeninin okunan değerinin **1** olduğunu düşünelim. Bu değer _producer thread_'inde **(2)** noktasında _is_ready_ değişkenine atanan değer. <br>
**(2) (3)**'ten önce olmuş olmalı. Ama bu **(2)** ve **(3)** arasında _happens-before_ ilişkisi olduğu anlamına gelmez.<br>
**(2)** ve **(3)** arasında _happens-before_ ilişkisi olmadığı gibi **(1)** ile **(4)** arasında da _happens-before_ ilişkisi yoktur. Bu yüzden **(1) (4)** arasındaki bellek işlemleri farklı şekilde sıralanabilir (reordering). derleyici tarafından oluşturulan _instruction_'lar işlemci ya da bellek tarafından farklı şekilde sıralanabilir _(instruction reordering / memory reordering)_. _consumer thread_'i **(4)** noktasına geldiğinde ekrana 0 değeri yazılabilir.

- Inter-thread happens-before ilişkisi farklı thread'ler arasındaki happens-before ilişkisidir.
- A ve B farklı threadler'deki operasyonlar olsun. Eğer A ve B arasında _inter-thread-happens_before_ ilişkisi varsa A ve B arasında _happens-before_ ilişkisi vardır. Yani A'daki operasyonların sonucu B'de görülebilir olmak zorundadır.
- Inter-thread happens-before ilşkisi geçişkendir _(transitive)_
- Inter-thread-happens-before ilişkisinin oluşması için (dil tarafından tanımlanan) bir senkronizasyonun söz konusu olması gerekir.
- A ve B arasında happens-before ilişkisi olsun. Bu durumda
    - A ve B aynı thread'de olabilir ve aralarında sequenced-before ilişkisi vardır.
    - A ve B aynı farklı thread'lerde olabilir ve aralarında intra-thread-happens-before ilişkisi vardır.
