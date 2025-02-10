- _recursive mutex_'ler _std::recursive_mutex_ ve _std::recursive_timed_mutex_ sınıfları tarafından sunulur.
- _recursive_mutex_ sınıfı _std::mutex_ sınıfına benzer ancak yeniden kilitlemeye izin verir.
- izin verilen kilitleme sayısı derleyiciye bağlıdır.

- Özyinelemeli _mutex_, bir _thread_'in aynı _mutex_'i birden fazla kez kilitleyebileceği yapıdadır.

- Bir _mutex_ A thread'i tarafından ilk kez kilitlendikten sonra, A thread'i _mutex_ üzerinde ek kilitler edinebilir (hali hazırda sahip olduğu kilidi serbest bırakmadan).

- A _thread'i mutex_ üzerindeki tüm kilitlerini serbest bırakana kadar _mutex_ diğer iş parçacıkları tarafından kullanılamaz.

- Özyinelemeli _mutex_ genellikle bir _mutex_'i kilitleyen kodun aynı _mutex_'i kilitleyen başka bir kodu çağırması gerektiğinde kullanılır (kilitlenmeyi önlemek için).

- Örneğin, bir _mutex_ alan ve özyinelemeli olarak kendini çağıran (_mutex_'in yeniden kilitlenmesine neden olan) bir işlevin özyinelemeli bir _mutex_ kullanması gerekir.

- Özyinelemeli bir _mutex_, özyinelemeli olmayan bir _mutex_'e göre daha fazla ek yüke sahiptir.

- Özyinelemeli _mutex_'leri kullanan kodların anlaşılması genellikle daha zor olabilir ve bu nedenle hatalara daha yatkındır.

- Sonuç olarak, mümkünse özyinelemeli _mutex_'lerin kullanımından kaçınılmalıdır.
