C++'da eş zamanlı programlamada (concurrency) "memory order" (bellek sıralaması), atomik işlemlerin _(atomic operations)_ bellek erişimlerinin sıralamasını belirleyen bir kavramdır. Bu, _thread_'lerin paylaşılan verilere erişimini düzenleyerek bellek tutarlılığını sağlamaya yardımcı olur.
Modern işlemciler ve derleyiciler, performansı artırmak için bellek erişimlerini yeniden sıralayabilirler. 
Bu yeniden sıralama, tek _thread_'li programlarda sorun yaratmazken, birden fazla thread kullanılan programlarda yarış (data race)  durumlarına ve hatalı sonuçlara yol açabilir. 
Bellek sıralama kısıtlamaları, bu yeniden sıralamayı kontrol ederek iş _thread_'lerin bellek erişimlerinin belirli bir sırayla gerçekleşmesini sağlar.
