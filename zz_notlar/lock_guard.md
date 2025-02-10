_std::lock_guard_ bir _mutex_ sarmalayıcı _RAII_ sınıfıdır. <br>
Bir _std::lock_guard_ nesnesinin _constructor_'ı bir _mutex_'i kilitler _(lock)_ ve destructor'ı bu kilidi serbest bırakır _(unlock)_. Böylece manuel olarak _mutex_ nesnesinin _lock_ ve _unlock_ donksiyonlarının çağrılması ihtiyacı ortadan kalkar ve hata yapma riski azalır. Örneğin, bir_ exception_ gönderildiğinde _mutex_'in _unlock_ fonksiyonunun çağrılmaması biçiminde ortaya çıkan hatalar yaşanmaz. (_exception safety_ sağlar.) _mutex_ sınıf nesnesinin _unlock_ fonksiyonunun çağrılmasının unutulması riski yoktur.<br>
_std::lock_guard_ kopyalanamaz ve taşınamaz (non-copyable ve non-movable).<vr>
Sınıfın hiçbir üye fonksiyonu yoktur. sarmalanan _mutex_'in _unlock_ fonksiyonu _explicit_ olarak çağrılamaz.
+ Sınıfın _copy ctor_ ve _copy assignment_ fonksiyonları _delete_ edilmiştir. _std::lock_guard_ nesneleri kopyalanamaz ve taşınamaz. _(non-copyable - non-moveable)_
