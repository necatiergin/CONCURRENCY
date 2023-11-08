Bir _shared_future_ nesnesi bir _promise_ nesnesi ile ilişkilendirilmiştir. 
Ancak _std::shared_future_ nesnesi sonucu _(result)_ birden fazla kez sorgulayabilir.
_shared_future_ sınıfı _future_ sınıfları aynı arayüze sahiptir.

_std::future_ nesnesinin _share_ işlevine çağrı yaparak bir _std::future_ nesnesinden bir _shared_future_ nesnesi elde edbiliriz.
