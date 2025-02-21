Spinlock, _multi-thread_ uygulamalarda paylaşılan kaynaklara erişimi senkronize etmek için kullanılan bir kilitleme mekanizmasıdır. 
Bir _thread_ bir _spinlock_'u elde etmeye çalıştığında ve kilidin zaten başka bir _thread_ tarafından tutulduğunu gördüğünde, kilit serbest bırakılana kadar "döner" _(spin)_. 
Yani _thread_, uyku moduna geçmek yerine sürekli olarak kilidin durumunu kontrol eder.
