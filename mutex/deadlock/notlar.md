
#### deadlock senaryoları

Birden fazla kilit edinilmesi gerekiyorsa, kilitlerin her zaman aynı sırada edinilmesi kritiktir; aksi halde _deadlock_ oluşabilir.<br>
Örneğin, bazı işlemleri gerçekleştirmeden önce iki _mutex_'in edinilmesi gereken bir durum olsun.
 Eğer iki _mutex_ tutarlı bir sırayla edinilmezse, aşağıdaki gibi bir durum ortaya çıkabilir:

- _thread_ 1, _mutex1_'i edinir.
- _thread_ 2, _mutex2_' yi edinir.
- _thread_ 1, _mutex 2_'yi elde etmeye çalışır ve _thread_ 2'nin bu _mutex_'i serbest bırakmasını beklerken bloke olur.
- _thread_ 2, _muteks 1_'i elde etmeye çalışır ve _thread_ 1'in bu _mutex_'i serbest bırakmasını beklerken bloke olur.
bu durum _deadlock_'a neden olur. <br>
Yukarıdaki örnekte, iki _mutex_ farklı _thread_'ler tarafından her zaman aynı sırada ediniliyor ise, bu tür bir _deadlock_ oluşmaz.

Bu tür durumlarda deadlock'tan kaçınılması için şu seçeneklerden biri kullanılabilir:
+ tüm _thread_'ler _mutex_'leri aynı sıra ile edinmeliler.
+ _std::lock_ fonksiyonu kullanılarak kilitler edinilmeli.
+ _std::scoped_lock_ _RAII_ sınıfı kullanılmalı.
