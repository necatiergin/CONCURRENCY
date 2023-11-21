_std::scoped_lock_ _std::lock_guard_ ile aynı işlevselliğe sahiptir ancak daha _generic_ hale getirilmiştir. 
_deadlock_ önleyici bir mekanizma ile aynı zamanda birden fazla _mutex_'i kilitleyebilir.
- Birden fazla mutex'i std::lock_guard ile edinmek daha karmaşık
Yalnızca tek bir muteksi kilitlerken bile her zaman std::scoped_lock kullanmak, performansı azaltıcı bir etki yapmaz.

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
+ _scoped_lock_ nesneleri kopyalanamaz ve taşınamaz _(non-copyable / non-moveable)_
+ _mutex_'lerin serbest bırakılmasının ihmal edilmesi ya da gönderilen bir _exception_ nedeniyle atlanması riskini ortadan kaldırır.  
+ birden fazla _mutex_ edinirken _std::lock_ işlevinin kullandığı _deadlock_'tan kaçınma algoritmasını kullanır.
+ _scoped_lock_ etkin bir şekilde std::lock_guard sınıfının yerine geçer
