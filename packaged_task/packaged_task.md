#### std::packaged_task


+ _std::packaged_task_ sınıfı türünden bir nesne asenkron çağrı yapmak amaçlı bir _callable_ sarmalar.
+ _std::packaged_task_ nesnesinin _get_future_ işlevi ile onunla ilişkilendirilmiş _std::future_ nesnesini elde ederiz.
+ sınıfın fonksiyon çağrı operatör fonksiyonu sarmalanan _callable_'ı çağırır.
+ _std::packaged_task_ sınıfının bildirimi şöyledir:

```cpp
template <class R, class... Args>
class packaged_task<R(Args...)>;
```
+ template parametreleri olan _R_ and _Args_ sarmalanacak _callable_'ın geri dönüş türünü ve parametrelerinin türünü temsil eder.
+ _std::packaged_task_, _std::function_ sınıfına benzer. Ancak _std::packaged_task_ sarmalanan _callable_'ın geri dönüş değerini bir _future_ nesnesi ile iletebilir.
+ _packaged_task_ çoğunlukla _thread_ fonksiyonu olarak kullanılır.
+ packaged_task sınıf nesneleri taşınabilir ama kopyalanamaz.
+ _get_future_ fonksiyonu ile _packaged_task_ ile ilişkilendirilen _std::future_ nesnesi elde edilir.
+ _get_future_ fonksiyonu yalnızca bir kez çağrılabilir.
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


