C++'da eş zamanlı programlamada (concurrency) "memory order" (bellek sıralaması), atomik işlemlerin _(atomic operations)_ bellek erişimlerinin sıralamasını belirleyen bir kavramdır. Bu, _thread_'lerin paylaşılan verilere erişimini düzenleyerek bellek tutarlılığını sağlamaya yardımcı olur.
Modern işlemciler ve derleyiciler, performansı artırmak için bellek erişimlerini yeniden sıralayabilirler. 
Bu yeniden sıralama, tek _thread_'li programlarda sorun yaratmazken, birden fazla thread kullanılan programlarda yarış _(data race)_ durumlarına ve hatalı sonuçlara yol açabilir. 
Bellek sıralama kısıtlamaları, bu yeniden sıralamayı kontrol ederek iş _thread_'lerin bellek erişimlerinin belirli bir sırayla gerçekleşmesini sağlar.

#### Atomik işlemlerde kullanılan bellek sıralaması kategorileri

**std::memory_order_relaxed:**<br>
En zayıf bellek sıralama kısıtlamasıdır. Sadece atomiklik garantisi verir, herhangi bir sıralama garantisi vermez. İş parçacıkları arasında herhangi bir senkronizasyon sağlamaz. Performans açısından en hızlı seçenektir. Sayaçlar gibi basit atomik işlemlerde kullanılabilir.

**std::memory_order_acquire:** <br>
Bir _thread_'in bir atomik değişkeni okuduktan sonra, bu okuma işleminden önce gerçekleşen tüm bellek erişimlerinin, okuma işleminden önce gerçekleşmesini garanti eder.
Diğer _thread_'lerin bu okuma işleminden sonra bellek erişimlerini yeniden sıralamasına izin verir. Kilit edinme _(lock acquisition)_ ve koşul değişkeni bekleme _(condition variable wait)_ gibi senkronizasyon mekanizmalarında kullanılır.

**std::memory_order_release:** <br>
Bir _thread_'in bir atomik değişkene yazdıktan sonra, bu yazma işleminden sonra gerçekleşen tüm bellek erişimlerinin, yazma işleminden sonra gerçekleşmesini garanti eder.
Diğer _thread_'lerin bu yazma işleminden önce bellek erişimlerini yeniden sıralamasına izin verir. Kilit serbest bırakma _(lock release)_ ve koşul değişkeni sinyali _(condition variable signal)_ gibi senkronizasyon mekanizmalarında kullanılır.

**std::memory_order_acq_rel:** <br>

Hem _acquire_ hem de _release_ sıralama kısıtlamalarını birleştirir. Bir atomik değişken üzerinde hem okuma hem de yazma işlemleri yapan durumlarda kullanılır.
Örneğin, bir atomik değişkeni artırmak veya azaltmak gibi işlemlerde kullanılabilir.

**std::memory_order_seq_cst:** <br>
En güçlü bellek sıralama kısıtlamasıdır. Tüm _thread_'lerin atomik işlemlerin aynı sırayla gerçekleştiğini görmesini garanti eder. Varsayılan bellek sıralama kısıtlamasıdır.
Performans açısından en yavaş seçenektir. Karmaşık senkronizasyon senaryolarında ve hata ayıklama amaçlı kullanılabilir.
