■ _std::timed_mutex_ sınıfı, _mutex_ edinilirken zaman aşımının belirtilmesine izin veren bir _mutex_ arayüzü sağlar

■ _mutex_ belirtilen sürede elde edilemezse, edinme işlemi başarısız olur (yani mutex kilitlenmez) ve bir hata değeri döndürülür.

■ a_mutex_'i zaman aşımı ile kilitlemeyi denemek için _try_lock_for_ ve _try_lock_until_ üye fonksiyonlarını ekler.
