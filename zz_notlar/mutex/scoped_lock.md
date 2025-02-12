_std::scoped_lock_ _std::lock_guard_ ile aynı işlevselliğe sahiptir ancak daha _generic_ hale getirilmiştir. 
_deadlock_ önleyici bir mekanizma ile aynı zamanda birden fazla _mutex_'i kilitleyebilir.
- Birden fazla _mutex_'i _std::lock_guard_ ile edinmek daha karmaşık bir kodu gerektirir.
Yalnızca tek bir _mutex_'i kilitlerken bile her zaman _std::scoped_lock_ kullanmanın performans üstünde kötü etkisi olmaz.

+ _std::scoped_lock_ birden fazla _mutex_'i tmplate argümanı olarak alabilecek bir template parametre paketine sahip.

+ Sınıfın bildirimi şu sekilde
```cpp
template <class... Mtx> 
class scoped_lock;
```
+ parametre paketi edinilecek _mutex_'lerin türlerini alacak.
+ kilitleme ve açma arayüzüne sahip herhangi bir _mutex_ sınıfı template argümanı olarak kullanılabilir. 
+ sınıfın kurucu işlevi bir ya da birden fazla _mutex_'i argüman olarak alabilir.
+ Sınıfın kurucu işlevi ile edinilen _mutex_'ler sınıfın _destructor_'ı ile bırakılır.
+ _scoped_lock_ nesneleri kopyalanamaz ve taşınamaz _(non-copyable / non-moveable)_.
+ _mutex_'lerin serbest bırakılmasının ihmal edilmesi ya da gönderilen bir _exception_ nedeniyle atlanması riskini ortadan kaldırır.  
+ birden fazla _mutex_ edinirken _std::lock_ işlevinin kullandığı _deadlock_'tan kaçınma algoritmasını kullanır.
+ _scoped_lock_ etkin bir şekilde _std::lock_guard_ sınıfının yerine geçer.
