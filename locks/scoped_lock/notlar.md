#### nedir?
_std::scoped_lock_ bir ya da birden fazla _mutex_'i edinebilen (kilitleyebilen) bir _RAII_ sınıfı.<br>

```cpp
template <typename ...Ts>
class scoped_lock {
    //...
}
```
- parametre oaketi olan Ts edinilecek mutex'lerin türleribi belirliyor.
- gerekli olan kilitleme ve kildi açma arayüzüne sahip tüm _mutex_ türleri ile kullanılabilir.
