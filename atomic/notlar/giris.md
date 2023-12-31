### atomic

- _Thread_'ler arasında veriyi paylaşırken _"data race"_ oluşmaması için genellikle bir senkronizasyon mekanizması gereklidir. (örneğin _mutex_ kullanarak senkronizasyonu sağlamak).
- Veriye senkronize edilmiş erişim sağlamanın başka bir yolu da atomik türleri kullanmaktır.
- Bölünemeyecek _(indivisible)_ bir işleme "atomik işlem" denir. Atomik bir işlem arasına başka bir işlem giremez. Örneğin arttırma işlemi atomik ise bu işleme tabi tutulan bir değişken diğer _thread_'ler tarafından ya işlemden önceki ya da işlemden sonraki değeri ile görülebilir.
 İşlemcilerin çoğunda atomik bellek işlemleri özel makine komutları ile gerçekleştirilir.
- atomik bellek işlemleri _"torn read"_ ya da _"torn write"_ durumu oluşturmazlar.
- C++ standart kütüphanesi atomik bellek işlemleri için aşağıdaki atomik türleri sunmaktadır:
    - _std::atomic_flag_
    - _std::atomic_\<>
- Bu türler donanımın sağladığı atomik operasyonlar için uniform bir arayüz sunarlar.

Atomik bir tür aşağıdaki garantileri sağlar:
- _atomicity_ (atomiklik - bölünmezlik)
- _ordering_ (bellek işlemlerinin sıralanması - önceliği sonralığı)
- _visibility_ (bellek işlemlerinin sonuçlarının diğer _thread_'lerden görülmesi)
Sıralı işlem garantisi bellek işlemlerinin diğer _thread_'lerde ne şekilde görülebileceği garantisidir. 
Atomik türler birbirinden bellek işlemlerinin sıralanması konusunda farklı garantiler sunarlar. 
Varsayılan düzen _"sequentially consistency_"'dir. (daha sonra değineceğim)

+ _atomic_  değişkenlerle yapılan işlemler atomik olma garantisini taşırlar. Yani bu işlemler tamamlanıncaya kadar bir başka _thread_ aynı değişken üzerinde işlem yapamaz.
+ _atomic_ bir değişkenin değerinin _(atomik olarak)_ bir arttırıldığını _(increment)_ düşünelim. 
Bu işlem aslında 3 farklı işleme karşılık gelir: oku - değiştir - yaz _(read - modify - write)_. 
Eğer değişkenimizin atomik olma garantisi yok ise bu işlemlerin arasına başka _thread_'lerin işlemleri girebilir. 
Değişkenimiz atomik ise diğer _thread_'ler değişkenimizi ya değiştirilmeden önceki değeri ile ya da değiştirildikten sonraki değeriyle görebilirler, ara bir değerde göremezler. Bir başka deyişle atomik değişkenler için _torn-read_ ya da _torn-write_ olamaz. 




