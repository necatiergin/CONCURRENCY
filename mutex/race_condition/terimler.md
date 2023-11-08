+ **race condition:** Öyle bir davranış ki bu davranıştan çıkan sonuç iki ya da ikiden fazla _thread_'in yürütülmesindeki görece sıraya göre değişebiliyor.
_race condition_ bir sorun oluşturmak zorunda değil. (_benign_ olabilir). Ancak bu terim daha çok problemli durumlar için kullanılıyor. (_invariant_'lar bozuluyor ya da tanımsız davranış oluşuyor.)

+ **data race** kötü _(benign olmayan)_ bir _race condition_. _data race_ tanımsız davranış oluşturuyor. <br>
Bir veriyi _(data)_ değiştirmeye _(modify)_ yönelik bir operasyon verinin iki ayrı parçasına erişmek zorunda. Bu iki parça ayrı komutlar _(instructions)_ ile değiştiriliyor. Bir _thread_ sadece parçalardan birini değiştirdiğinde (henüz ikinciyi değiştirmeden) bir başka _thread_ aynı veriye erişiyor. Bu tür hataları bulmak ya da duplike etmek çok zor olabilir, çünkü çok dar bir zaman aralığında gerçekleşiyor olabilir.<br>
Yazılım geliştirmede "data race" den kaçınmak zorunluluğu karmaşıklığı bir hayli arttırıyor.

+ **deadlock:** iki ya da daha fazla sayıda _thread_ ilerleme kaydedemiyor. Her ikisi de diğerinin tuttuğu kaynağı bekleyecek şekilde bloke oluyorlar.

+ **livelock:** iki ya da daha fazla _thread_ (bloke olmadan) birbirlerinin tuttuğu kaynakları beklediklerinden ilerleme kaydedemiyorlar.

+ **critical section** Birden fazla _thread_ tarafından eş zamanlı olarak erişilmemesi gereken bir kaynak içeren bir kod parçası. _critical_section_ girişinden çıkışına kadar, birden fazla _thread_'in aynı zamanda bu kodları yürütmesini engelleyecek şekilde bir senkronizasyon mekanizması oluşturmak gerekiyor.
