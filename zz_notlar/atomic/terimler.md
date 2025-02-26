_multi-thread_ programlamada, birden fazla _thread_ aynı anda aynı bellek konumlarına erişebilir. Bu, veri yarışlarına _(data races)_ ve tanımsız davranışlara yol açabilir. 
sequence-before, happens-before, inter-thread happens-before terimleri _thread_'ler arasındaki işlemlerin sırasını ve görünürlüğünü tanımlayarak bu sorunları önlemeye yardımcı olur.

#### sequenced-before (sıralı öncelik garantisi)
**sequenced-before**__, aynı _thread_ içindeki işlemlerin sırasını tanımlar. Eğer bir işlem A, başka bir işlem B'den _"sequenced-before"_ ise, A, B'den önce gerçekleşir.
- tek _thread_ bağlamında: Tek thread'li programlarda, kodun yazıldığı sıraya göre işlemler **_sequenced-before_** ilişkisine sahiptir.
- Çok _thread_'li bağlamda: **sequenced-before**__, her _thread_ için geçerlidir, ancak _thread_'ler arasındaki işlemleri tanımlamaz.

```cpp
int x = 10; // A
int y = x + 5; // B
```
Bu örnekte, A işlemi (x'e 10 atanması), B işleminden (y'ye x + 5 atanması) "sequenced-before" olur.

#### happens-before (önce-gerçekleşme-garantisi)
_happens-before_, işlemlerin görünürlüğünü tanımlar. Eğer bir işlem A, başka bir işlem B'den **"happens-before"** ise, A'nın etkileri B'den önce görünür hale gelir.
**sequenced-before**, _happens-before_ ilişkisini içerir.<br>
_thread_'ler arası senkronizasyon işlemleri de **happens-before** ilişkisi kurar.<br>
görünürlük: **happens-before** ilişkisi, bir _thread_'in diğer diğer bir _thread_'in yaptığı değişiklikleri ne zaman göreceğini belirler.

```cpp
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> x = 0;
std::atomic<bool> ready = false;

void writer() {
    x.store(42, std::memory_order_release);
    ready.store(true, std::memory_order_release);
}

void reader() {
    while (!ready.load(std::memory_order_acquire));
    std::cout << x.load(std::memory_order_acquire) << std::endl;
}

int main() 
{
    std::thread t1(writer);
    std::thread t2(reader);

    t1.join();
    t2.join();

 }
```

Bu örnekte, writer iş parçacığındaki ready.store işlemi, reader iş parçacığındaki ready.load işleminden "happens-before" olur. 
Bu, reader thread'inin x değişkeninin değerini okuduğunda, writer thread'ini x'e yazdığı değeri göreceği anlamına gelir.

inter-thread happens-before (threadler arası önce gerçekleşme garantisi)
Tanım: "Inter-thread happens-before", farklı thread'ler arasındaki "happens-before" ilişkisini tanımlar.
Senkronizasyon: Bu ilişki, atomik işlemler, mutex'ler, condition variable'lar gibi senkronizasyon araçları kullanılarak kurulur.
Örnek
Yukarıdaki writer ve reader örneği, "inter-thread happens-before" ilişkisini gösterir. 
ready.store ve ready.load işlemleri arasındaki "happens-before" ilişkisi, iş parçacıkları arasında gerçekleştiği için "inter-thread happens-before" olarak adlandırılır.

