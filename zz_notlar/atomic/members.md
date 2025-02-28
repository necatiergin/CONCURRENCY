<!---
Tabii ki! C++ standart kütüphanesindeki std::atomic sınıf şablonu, çoklu iş parçacığı (multithreading) programlamada atomik operasyonlar sağlamak için kullanılır. 


fetch_add bir atomik işlenmdir.
veri yarışlarını (data races) önlemek ve iş parçacıkları arasında güvenli bir şekilde paylaşılan verilere erişim veya değişiklik yapmak için oldukça önemlidir. 
fetch_add ise std::atomic sınıf şablonunun bir üye fonksiyonudur ve atomik bir şekilde bir değere ekleme yapar.
fetch_add, bir atomik nesnenin mevcut değerine, verilen bir artırma miktarını ekler ve işlemin atomik olmasını sağlar. 
Yani, bu işlem sırasında başka bir iş parçacığı aynı değişken üzerinde çakışan bir işlem yapamaz. 
Fonksiyon, ekleme işlemini gerçekleştirmeden önceki eski değeri döndürür.

std::atomic<T>::fetch_add fonksiyonunun genel prototipi şöyledir:

```cpp
T fetch_add(T val, std::memory_order order = std::memory_order_seq_cst) noexcept;
```

val     : Atomik nesneye eklenecek değer (artırma miktarı).
order: Bellek sıralama düzeni (memory order). 
Varsayılan olarak std::memory_order_seq_cst (sequential consistency) kullanılır, 
ancak performans için daha gevşek sıralama düzenleri (örneğin std::memory_order_relaxed) de belirtilebilir.

geri dönüş değeri
İşlemden önceki atomik nesnenin eski değeri (T türünde).


şlem atomiktir; yani kesintiye uğramaz ve diğer iş parçacıklarıyla çakışma olmadan tamamlanır.

noexcept olarak işaretlenmiştir, yani bu fonksiyon istisna (exception) fırlatmaz.

Desteklenen Türler:
std::atomic<T> yalnızca integral türler (örneğin int, long, char) ve işaretçi türleri (pointers) için fetch_add fonksiyonunu destekler. 
Kayan nokta türleri (float, double) için bu fonksiyon tanımlı değildir.

Bellek Sıralama (Memory Order)
Bellek sıralama, iş parçacıkları arasındaki operasyonların nasıl senkronize edileceğini belirler. 
Varsayılan std::memory_order_seq_cst, en katı sıralamayı sağlar ve tüm iş parçacıklarında tutarlı bir yürütme sırası garanti eder. 
Daha gevşek sıralamalar (örneğin std::memory_order_acquire veya std::memory_order_relaxed) ise performansı artırabilir, ancak dikkatli kullanılmalıdır.
Kullanım Örneği
Aşağıda, std::atomic ve fetch_add kullanarak çoklu iş parçacıklarının bir sayaç üzerinde güvenli bir şekilde artırma yaptığı bir kod örneği verilmiştir:
cpp

#include <iostream>
#include <atomic>
#include <thread>
#include <vector>

std::atomic<int> counter(0); // Global bir atomik sayaç

void increment_counter(int increments) {
    for (int i = 0; i < increments; ++i) {
        int old_value = counter.fetch_add(1); // Eski değeri al ve 1 artır
        std::cout << "Eski değer: " << old_value << ", Yeni değer: " << counter << std::endl;
    }
}

int main() {
    const int num_threads = 4;
    const int increments_per_thread = 5;

    std::vector<std::thread> threads;

    // Birden fazla iş parçacığı oluştur
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(increment_counter, increments_per_thread);
    }

    // Tüm iş parçacıklarının tamamlanmasını bekle
    for (auto& t : threads) {
        t.join();
    }

    std::cout << "Sonuç: " << counter << std::endl; // Toplam artırma sayısını yazdır

    return 0;
}

Kod Açıklaması
std::atomic<int> counter(0);: Bir atomik tamsayı değişkeni tanımlanır ve başlangıç değeri 0 olarak ayarlanır.

fetch_add(1): Her iş parçacığı, counter değerini atomik olarak 1 artırır ve artırma işleminden önceki eski değeri döndürür.

Çoklu İş Parçacıkları: 4 iş parçacığı oluşturulur ve her biri increment_counter fonksiyonunu 5 kez çalıştırır. Toplamda 4 * 5 = 20 artırma işlemi yapılır.

Çıktı: Her artırma işleminde eski ve yeni değerler yazdırılır. Sonuç olarak counter 20 olur.

Örnek Çıktı (Sıralama değişebilir)

Eski değer: 0, Yeni değer: 1
Eski değer: 1, Yeni değer: 2
Eski değer: 2, Yeni değer: 3
...
Eski değer: 19, Yeni değer: 20
Sonuç: 20

Önemli Notlar
fetch_add vs +=: Normal bir int üzerinde += kullanmak atomik değildir ve çoklu iş parçacıklarında veri yarışı (data race) oluşturabilir. fetch_add bu sorunu çözer.

Performans: Atomik operasyonlar, kilitleme (locking) mekanizmalarına göre daha hafif olabilir, ancak yine de işlemci seviyesinde senkronizasyon gerektirir.

Kullanım Alanı: Sayaçlar, işaretçiler veya sıralı işlemler gibi senaryolarda sıkça kullanılır.

Eğer bu konuda daha fazla sorunuz varsa veya başka bir örnek isterseniz, sormaktan çekinmeyin!

std::memory_order türleri

std::mutex kullanımı

DeepSearch
Think

Attach

--->
