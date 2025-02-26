_multi-thread_ programlamada, birden fazla _thread_ aynı anda aynı bellek konumlarına erişebilir. Bu, veri yarışlarına _(data races)_ ve tanımsız davranışlara yol açabilir. 
sequence-before, happens-before, inter-thread happens-before terimleri _thread_'ler arasındaki işlemlerin sırasını ve görünürlüğünü tanımlayarak bu sorunları önlemeye yardımcı olur.

#### sequenced-before (sıralı öncelik garantisi)
**sequenced-before**, aynı _thread_ içindeki işlemlerin sırasını tanımlar. Eğer bir işlem A, başka bir işlem B'den _"sequenced-before"_ ise, A, B'den önce gerçekleşir.
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

Bu örnekte, _writer_ thread'indeki _ready.store_ işlemi, _reader_ thread'inde _ready.load_ işleminden **happens-before** olur. <br>
Bu, _reader thread_'inin x değişkeninin değerini okuduğunda, _writer thread_'ini x'e yazdığı değeri göreceği anlamına gelir.

#### inter-thread happens-before (threadler arası önce gerçekleşme garantisi)
**Inter-thread happens-before**, farklı _thread_'ler arasındaki **happens-before** ilişkisini tanımlar. <br>
**Senkronizasyon:** Bu ilişki, atomik işlemler, **mutex**'ler, _condition variable_'lar gibi senkronizasyon araçları kullanılarak kurulur.<br>
Yukarıdaki writer ve reader örneği, "inter-thread happens-before" ilişkisini gösterir. <br>
_ready.store_ ve _ready.load_ işlemleri arasındaki "happens-before" ilişkisi, _thread_'ler arasında gerçekleştiği için **inter-thread happens-before** olarak adlandırılır.

