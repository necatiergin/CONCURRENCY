_JThread_ sınıfı, _thread_'in güvenli bir şekilde durdurulmasını sağlayan bir mekanizma sunar. Bu mekanizma, _thread_'e durdurma isteği göndermek ve _thread_'in durdurulup durdurulmadığını kontrol etmek için aşağıdaki üye fonksiyonları ve _std::stop_token_ türünü kullanır.
#### üye fonksiyonlar
```
std::stop_source get_stop_source() noexcept;
```
Bu fonksiyon _std::jthread_ nesnesine bağlı bir _std::stop_source_ nesnesini döndürür. _std::stop_source_, durdurma isteği göndermek için kullanılan bir nesnedir. Bu nesne, _thread_'in çalışmasını durdurmak isteyen başka bir kod parçası (örneğin ana thread) tarafından kullanılabilir. Ana _thread_ ya da başka bir kontrol mekanizması, _std::jthread_ nesnesinin çalışmasını durdurmak istediğinde, bu fonksiyondan _std::stop_source_ nesnesini alır ve durdurma isteğini gönderir.

```
std::stop_token get_stop_token() const noexcept;
```
_std::jthread_ nesnesine bağlı bir _std::stop_token_ nesnesini döndürür. _std::stop_token_, _thread_ tarafından durdurma isteğinin gelip gelmediğini kontrol etmek için kullanılır. _thread_, bu fonksiyonla elde edilen _std::stop_token_ nesnesini kullanarak durdurma isteğini sorgulayabilir ve buna göre davranabilir (örneğin, bir döngüden çıkabilir).

```
bool request_stop() noexcept;
```

_std::jthread_ nesnesine bağlı _std::stop_source_ üzerinden durdurma isteği gönderir. Eğer durdurma isteği daha önce gönderilmemişse _true_, aksi takdirde _false_ döner.
_thread_'in çalışmasını durdurmak isteyen kod, bu fonksiyonu çağırır. Durdurma isteği gönderildiğinde, _thread_ bunu _std::stop_token_ üzerinden algılayabilir ve sonlandırma işlemini yapabilir.

#### std::stop_token
_std::stop_token_, _C++20_ ile standartlaştırılmış bir türdür ve platformdan bağımsızdır. <br>
_std::stop_token_, durdurma isteğinin durumunu kontrol etmek için kullanılan bir türdür. _std::stop_source_ nesnesinden elde edilen bu token, _thread_'in durdurma isteğine yanıt vermesini sağlar.
_std::stop_token_, _thread_'in dışarıdan gelen bir durdurma isteğini fark etmesini sağlar.<br>
 _stop_requested()_ üye fonksiyonu ile durdurma isteğinin gelip gelmediği kontrol edilir. Bu fonksiyon, durdurma isteği gelip gelmediğini kontrol eder. Eğer durdurma isteği gelmemişse false gelmişse true döndürür.

_std::stop_callback_ ile, durdurma isteği geldiğinde çağrılacak fonksiyonu _(callback)_ kaydedilebilir.<br>
_stop_token_ nesneleri küçüktür ve kopyalanabilir. (kopyalanma maliyeti düşüktür)

_std::stop_token_, _std::jthread_ tarafından otomatik olarak sağlanır. 
Yani, biz _std::jthread_ nesnesini oluşturduğunuzda ve ona bir fonksiyon verdiğimizde, _std::jthread_ bu fonksiyona bir _std::stop_token_ nesnesi geçirir. Bu, _thread_'in durdurma isteğini kontrol edebilmesi için bir nevi "iletişim kanalı"dır.
_thread_'in çalıştıracağı fonksiyon _std::stop_token_ türünden bir parametre değişkenine sahip ise bu parametreye std::jthread jt tarafından otomatik olarak argüman gönderilir. Biz bu parametreye argüman göndermeyiz; _std::jthread_ sınıf nesnesi bunu bizim için yapar.




