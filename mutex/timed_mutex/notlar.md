- _std::timed_mutex_ sınıfı, _mutex_ edinilirken zaman aşımının belirtilmesine izin veren bir _mutex_ arayüzü sağlar

- _mutex_ belirtilen sürede elde edilemezse, edinme işlemi başarısız olur (yani mutex kilitlenmez) ve bir hata değeri döndürülür.

- _mutex_'i zaman aşımı ile kilitlemeyi denemek için _try_lock_for_ ve _try_lock_until_ üye fonksiyonlarını ekler.

- Özyinelemeli mutex, bir thread'in aynı mutex'i birden fazla kez kilitleyebileceği yapıdadır.

- Bir mutex A iş parçacığı tarafından ilk kez kilitlendikten sonra, A iş parçacığı mutex üzerinde ek kilitler edinebilir (hali hazırda sahip olduğu kilidi serbest bırakmadan).

- A iş parçacığı mutex üzerindeki tüm kilitlerini serbest bırakana kadar mutex diğer iş parçacıkları tarafından kullanılamaz.

- Özyinelemeli mutex genellikle bir mutex'i kilitleyen kodun aynı mutex'i kilitleyen başka bir kodu çağırması gerektiğinde kullanılır (kilitlenmeyi önlemek için).

- Örneğin, bir mutex alan ve özyinelemeli olarak kendini çağıran (mutex'in yeniden kilitlenmesine neden olan) bir işlevin özyinelemeli bir mutex kullanması gerekir.

- Özyinelemeli bir mutex, özyinelemeli olmayan bir mutex'e göre daha fazla ek yüke sahiptir.

- Özyinelemeli mutex'leri kullanan kodların anlaşılması genellikle daha zor olabilir ve bu nedenle hatalara daha yatkındır.

- Sonuç olarak, mümkünse özyinelemeli mutex'lerin kullanımından kaçınılmalıdır.
