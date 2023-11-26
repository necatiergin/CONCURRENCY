#### Bir task'in çalıştırılması için farklı seçeneklerimiz var:

+ bir thread nesnesi oluşturmak.
+ bir packaged_task nesnesi oluşturmak.
+ std::sync fonksiyonunu çağırmak.

farklı avantajları ve dezavantajları var:

#### std::async
- fonksiyondan geri dönüş değeri almak çok kolay.
- task'dan gönderilen exception kolayca yakalanıyor.
- task'i senkron ya da asenkron çalıştırma olanağı var.

std::thread'e göre daha yüksek seviyeli vbir soyutlama sağlıyor.
thread ya da theadleri kendisi oluşturuyor.
thread'ler arası iletişimi kendi oluşturuyor.
paylaşılan veri kullanmak gerekmiyor.
