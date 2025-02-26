#### Thread Pool (thread havuzu) nedir?
_Thread Pool_, bir kuyruktaki görevleri yürüten önceden oluşturulmuş _thread_'lerden oluşan bir yapıdır. Yani bir _thread pool_ önceden oluşturulmuş belirli sayıda _thread_'e sahiptir. _Thread pool_ verimliliği arttırmak amacıyla, _threadleri_ dinamik olarak oluşturmak ve yok etmek yerine, mevcut _thread_'leri yeniden kullanır.

#### Thread Pool Kullanmanın Faydaları
- Geliştirilmiş performans ve daha düşük ek yük sağlar (overhead)<br>
Dinamik olarak _thread_'leri oluşturmak ve yok etmek maliyetlidir. _Thread_ havuzu, _thread_'leri canlı tutarak pahalı oluşturma/yok etme döngülerinden kaçınır.

- Verimli kaynak kullanımı sağalr <br>
Yüksek CPU kullanımına ve bellek yüküne neden olabilecek aşırı _thread_ oluşturulmasını önler.

- Daha iyi bir yük dengelenmesi sağlar _(load balancing)_
Görevleri birden fazla iş parçacığı arasında verimli bir şekilde dağıtarak çok çekirdekli sistemlerde verimi artırır.

- Sistemin aşırı yüklenmesini önler<br>
Bir _thread havuzu_ olmadan, fazla sayıda _thread_ oluşturma _CPU_ açlığına ve kaynakların tükenmesine neden olabilir.

- Thread yönetimini enkapsüle eder. <br>
_Thread_'leri manuel olarak yönetmeden çok sayıda _thread_'i işlemek için yapılandırılmış bir yol sağlar.
