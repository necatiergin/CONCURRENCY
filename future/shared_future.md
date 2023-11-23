- Bir _shared_future_ nesnesi bir _promise_ nesnesi ile ilişkilendirilmiştir. 
- Ancak _std::shared_future_ nesnesi sonucu _(result)_ birden fazla kez sorgulayabilir.
_shared_future_ sınıfı _future_ sınıfları aynı arayüze sahiptir.
_std::future_ nesnesinin _share_ işlevine çağrı yaparak bir _std::future_ nesnesinden bir _shared_future_ nesnesi elde edbiliriz.
- _std::shared_future_ nesneleri _future_ nesnelerinden farklı olarak kopyalanabilir
- _std::future__ nesnesinin içeriğini _shared_future_ nesnesine aktarmak için _future_ sınıfının _share_ üye işlevi kullanılarak _shared_future_ nesnesi elde edilebilir

- sınıfın _get_ işlevi birden fazla kez çağrılabilir.



