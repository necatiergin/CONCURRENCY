#### Thread Pool (thread havuzu) nedir?
_Thread Pool_, bir kuyruktaki görevleri yürüten önceden oluşturulmuş _thread_'lerden oluşan bir yapıdır. Yani bir _thread pool_ önceden oluşturulmuş belirli sayıda _thread_'e sahiptir. _Thread pool_ verimliliği arttırmak amacıyla, _threadleri_ dinamik olarak oluşturmak ve yok etmek yerine, mevcut _thread_'leri yeniden kullanır.

#### Thread Pool Kullanmanın Faydaları
- Geliştirilmiş performans ve daha düşük ek yük (overhead)<br>
Dinamik olarak _thread_leri oluşturmak ve yok etmek maliyetlidir. _Thread_ havuzu, _thread_leri canlı tutarak pahalı oluşturma/yok etme döngülerinden kaçınır.

- Verimli Kaynak Kullanımı <br>
Yüksek CPU kullanımına ve bellek yüküne neden olabilecek aşırı thread oluşturulmasını önler.

- Daha İyi Yük Dengeleme
Görevleri birden fazla iş parçacığı arasında verimli bir şekilde dağıtarak çok çekirdekli sistemlerde verimi artırır.

- Sistemin Aşırı Yüklenmesini Önler<br>
Bir thread havuzu olmadan, fazla sayıda thread oluşturma CPU açlığına ve kaynakların tükenmesine neden olabilir.
thread yönetimini enkapsüle eder.

threadleri manuel olarak yönetmeden çok sayıda threadi işlemek için yapılandırılmış bir yol sağlar.
