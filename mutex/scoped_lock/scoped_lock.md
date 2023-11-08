_std::scoped_lock_ _std::lock_guard_ ile aynı işlevselliğe sahiptir ancak daha _generic_ hale getirilmiştir. 
_deadlock_ önleyici bir mekanizma ile aynı zamanda birden fazla _mutex_'i kilitleyebilir.
The equivalent code to perform simultaneous locking with std::lock_guard is significantly more complex.
Therefore, it is simpler to use std::scoped_lock all the time, even when locking only one mutex (there will be no performance impact).

+ std::scoped_lock is RAII class for mutexes
+ declaration:
```
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
