_JThread_ sınıfı, _thread_'in güvenli bir şekilde durdurulmasını sağlayan bir mekanizma sunar. Bu mekanizma, _thread_'e durdurma isteği göndermek ve _thread_'in durdurulup durdurulmadığını kontrol etmek için aşağıdaki üye fonksiyonları ve _std::stop_token_ türünü kullanır.

<!---
Üye Fonksiyonlar
1. get_stop_source
Tanım: std::stop_source get_stop_source() noexcept;

Ne İşe Yarar: std::jthread nesnesine bağlı bir std::stop_source nesnesini döndürür. std::stop_source, durdurma isteği göndermek için kullanılan bir nesnedir. 
Bu nesne, iş parçacığının çalışmasını durdurmak isteyen başka bir kod parçası (örneğin ana iş parçacığı) tarafından kullanılabilir.

Kullanım Amacı: Ana iş parçacığı veya başka bir kontrol mekanizması, std::jthread nesnesinin çalışmasını durdurmak istediğinde, bu fonksiyonla std::stop_source nesnesine erişir ve durdurma isteği gönderir.

2. get_stop_token
Tanım: std::stop_token get_stop_token() const noexcept;

Ne İşe Yarar: std::jthread nesnesine bağlı bir std::stop_token nesnesini döndürür. std::stop_token, iş parçacığı tarafından durdurma isteğinin gelip gelmediğini kontrol etmek için kullanılır.

Kullanım Amacı: İş parçacığı, bu fonksiyonla elde edilen std::stop_token nesnesini kullanarak durdurma isteğini sorgulayabilir ve buna göre davranabilir (örneğin, bir döngüden çıkabilir).

3. request_stop
Tanım: bool request_stop() noexcept;

Ne İşe Yarar: std::jthread nesnesine bağlı std::stop_source üzerinden durdurma isteği gönderir. Eğer durdurma isteği daha önce gönderilmemişse true, aksi takdirde false döner.

Kullanım Amacı: İş parçacığının çalışmasını durdurmak isteyen kod, bu fonksiyonu çağırır. Durdurma isteği gönderildiğinde, iş parçacığı bunu std::stop_token üzerinden algılayabilir ve sonlanma işlemini gerçekleştirebilir.

std::stop_token Türü
Tanım: std::stop_token, durdurma isteğinin durumunu kontrol etmek için kullanılan bir türdür. std::stop_source nesnesinden türetilen bu token, iş parçacığının durdurma isteğine yanıt vermesini sağlar.

Kullanım: 
stop_requested() üye fonksiyonu ile durdurma isteğinin gelip gelmediği kontrol edilir (bool döner).

std::stop_callback ile, durdurma isteği geldiğinde çağrılacak bir geri çağırma (callback) fonksiyonu kaydedilebilir.

--->
