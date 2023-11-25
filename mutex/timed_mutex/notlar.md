- _std::timed_mutex_ sınıfı, _mutex_ edinilirken zaman aşımının belirtilmesine izin veren bir _mutex_ arayüzü sağlar

- _mutex_ belirtilen sürede elde edilemezse, edinme işlemi başarısız olur (yani _mutex_ kilitlenmez) ve bir hata değeri döndürülür.

- _mutex_'i zaman aşımı ile kilitlemeyi denemek için _try_lock_for_ ve _try_lock_until_ üye fonksiyonlarını ekler.

- Özyinelemeli _mutex_, bir _thread_'in aynı _mutex_'i birden fazla kez kilitleyebileceği yapıdadır.

- Bir _mutex_ A iş parçacığı tarafından ilk kez kilitlendikten sonra, A iş parçacığı _mutex_ üzerinde ek kilitler edinebilir (hali hazırda sahip olduğu kilidi serbest bırakmadan).

- A iş parçacığı mutex üzerindeki tüm kilitlerini serbest bırakana kadar _mutex_ diğer iş parçacıkları tarafından kullanılamaz.

- Özyinelemeli _mutex_ genellikle bir _mutex_'i kilitleyen kodun aynı _mutex_'i kilitleyen başka bir kodu çağırması gerektiğinde kullanılır (kilitlenmeyi önlemek için).

- Örneğin, bir _mutex_ alan ve özyinelemeli olarak kendini çağıran (_mutex_'in yeniden kilitlenmesine neden olan) bir işlevin özyinelemeli bir _mutex_ kullanması gerekir.

- Özyinelemeli bir _mutex_, özyinelemeli olmayan bir _mutex_'e göre daha fazla ek yüke sahiptir.

- Özyinelemeli _mutex_'leri kullanan kodların anlaşılması genellikle daha zor olabilir ve bu nedenle hatalara daha yatkındır.

- Sonuç olarak, mümkünse özyinelemeli _mutex_'lerin kullanımından kaçınılmalıdır.
