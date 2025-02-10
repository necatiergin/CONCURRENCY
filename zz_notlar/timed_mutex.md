C++11 standardı ile dile eklenen _std::timed_mutex_ sınıfı sınırlı kilitleme özellikleri sunan bir _mutex_ türüdür. 
Bu sınıf, _std::mutex_ ile benzer şekilde çalışır, ancak kilit denemeleri için zaman sınırlamaları koyma olanağı sağlar. 
Bu, özellikle çok _threadli_ uygulamalarda _deadlock_ riskini azaltmak ve kilit alma sürelerini kontrol etmek için fayda sağlar. <br>
_std::timed_mutex_ nesneleri kopyalanamaz ve taşınamaz _(non-copyable non moveable)_

#### Sınıfın üye fonksiyonları 
- **lock(): **_mutex_'i. kilit başka bir thread tarafından edinilmiş ise çağrıldığı _thread_'i bloke eder.
- **try_lock():** _mutex_'i kilitlemeye çalışır. Kilitlerse _true_ kilitleyemez ise _false_ değer döndürür.
- **unlock():** _mutex_'in kilidini serbest bırakır.
- **try_lock_for():** Belirli bir süre boyunca kilidi almaya çalışır.
- **try_lock_until(): **Belirli bir zamana _(timepoint)_ kadar kilidi almaya çalışır.


Kopyalanamaz ve Taşınamaz:
