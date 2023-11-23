#### std::packaged_task


+ _std::packaged_task_ sınıfı türünden bir nesne asenkron çağrı yapmak amaçlı bir _callable_ sarmalar.
+ _std::packaged_task_ nesnesinin _get_future_ işlevi ile onunla ilişkilendirilmiş _std::future_ nesnesini elde ederiz.
+ sınıfın fonksiyon çağrı operatör fonksiyonu sarmalanan _callable_'ı çağırır.
+ _std::packaged_task_ sınıfının bildirimi şöyledir:

```cpp
template <class R, class... Args>
class packaged_task<R(Args...)>;
```

+  _std::packaged_task_ sınıfı çoğunlukla aşağıdaki gibi kullanılır:
+ İş yükü olan _callable_ bir _std::packaged_task_ nesnesi ile sarmalanır:
	
```
	std::packaged_task<int(int, int)> ptask([](int a, int b)
					{ return a * a + b * b; });
```

+ Bir _std::future_ nesnesi oluşturulur:
```
	std::future<int> ftr = ptask.get_future();
```

+ callable çağrılır:
```
ptask(10, 20);
```
+ sonuç elde edilir
```
ftr.get();
```
