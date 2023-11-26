#### Bir task'in çalıştırılması için farklı seçeneklerimiz var:

+ bir _std::thread_ nesnesi oluşturmak.
+ bir _std::packaged_task_ nesnesi oluşturmak.
+ _std::async_ fonksiyonunu çağırmak.

bu seçeneklerin farklı avantajları ve dezavantajları var:

#### _std::async_
- fonksiyondan geri dönüş değeri almak çok kolay.
- _task_'dan gönderilen _exception_ kolayca yakalanıyor.
- _task_'i senkron ya da asenkron çalıştırma olanağı var.

_std::thread_'e göre daha yüksek seviyeli bir soyutlama sağlıyor.
_thread_ ya da _thread_'leri kendisi oluşturuyor.
- _thread_'ler arası iletişimi kendi oluşturuyor.
- paylaşılan veri _(shared variables)_ kullanmak gerekmiyor.

dezavantajlar<br>
- _detach_ etme olanağı yok.


#### std::packaged_task avantajları
+ _task_'i bir nesne olarak temsil etmenin en kolay yolu.
+ _std::async_'e göre daha düşük seviyeli bir soyutlama.
	- _task_'in ne zaman yürütüleceğini kendimiz belirleyebiliyoruz;
	- _task_'in hangi _thread_ tarafından yürütüleceğini kendimiz belirleyebiliyoruz.

#### std::thread
+ _std::thread_ sınıfı türünden nesne oluşturmak.
+ standart kütüphanenin sunduğu en düşük seviyeli soyutlama.
+ diğer seçeneklere göre çok daha esnek.
+ işletim sisteminin öğelerine erişim olanağı sağlıyor.
+ Standard C++ tarafından sunulmayan olanakları kullanabiliyoruz.
+ _thread detach_ edilebiliyor.

