■ _std::lock variadic_ fonksiyon şablonu, bir _deadlock_ riski olmaksızın birden fazla _mutex_'in edinilmesini sağlar.<br>
■ bildirimi şöyle: <br>

```cpp
template <class T1, class T2, class... TN>
void lock(T1&, T2&, TN& ...);
```
