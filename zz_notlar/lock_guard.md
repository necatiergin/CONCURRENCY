+ _std::lock_guard_ bir _mutex_ sarmalayıcı _RAII_ sınıfı.
+ kapsamı tamamlandığında _lock_guard_ sınıfının _destructor_'ı sarmaladığı _mutex_'i serbest bırakıyor. _(unlock)_
+ _mutex_ sınıf nesnesinin _unlock_ fonksiyonunun çağrılmasının unutulması riski yok.
+ _exception safety_ sağlanıyor.
+ sarmalanan _mutex_'in _unlock_ fonksiyonunu _explicit_ olarak çağıramıyoruz.
+ _copy ctor delete_ edilmiş. _(non-copyable - non-moveable)_
