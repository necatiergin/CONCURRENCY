_std::scoped_lock_ _std::lock_guard_ ile aynı işlevselliğe sahiptir ancak daha _generic_ hale getirilmiştir. 
_deadlock_ önleyici bir mekanizma ile aynı zamanda birden fazla _mutex_'i kilitleyebilir.
- Birden fazla mutex'i std::lock_guard ile edinmek daha karmaşık
Yalnızca tek bir muteksi kilitlerken bile her zaman std::scoped_lock kullanmak, performansı azaltıcı bir etki yapmaz.

+ std::scoped_lock birden fazla mutex'i tmplate argümanı olarak alabilecek bir template paraemre paketine sahjip

+ Sınıfın bildirimi şu sekilde
```cpp
template <class... Mtx> 
class scoped_lock;
```
+ parameter pack Mtx specifies types of mutexes to be locked.
+ can be used with any mutex types providing necessary locking interface (e.g., std::mutex and std::recursive_mutex)
+ Sınıfın kurucu işlevi bir ya da birden fazla mutex'i argüman olarak alabilir.
+ Sınıfın kurucu işlevi ile edinilen mutex sınıfın destructor'ı ile bırakılır.
+ scoped_lock nesneleri kopyalanamaz ve taşınamaz (non-copyable / non-moveable)
+ using scoped_lock avoids problem of inadvertently failing to release mutexes (e.g., due to exception or forgetting unlock calls)
+ in multiple mutex case, employs deadlock avoidance algorithm from std::lock (discussed later) when acquiring mutexes
+ advisable to use scoped_lock instead of calling lock and unlock explicitly
+ scoped_lock effectively replaces (and extends) lock_guard
