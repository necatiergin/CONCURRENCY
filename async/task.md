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

