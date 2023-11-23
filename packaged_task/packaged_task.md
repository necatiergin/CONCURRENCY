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
+ _packaged_task_ çoğunlukla _thread_ fonksiyonu olarak kullanılır. Kendisi de bir _callable_ olduğu için bir _thread_'e iş yükü olarak verilebilir.
+ _packaged_task_ sınıf nesneleri taşınabilir ama kopyalanamaz.
+ _get_future_ fonksiyonu ile _packaged_task_ ile ilişkilendirilen _std::future_ nesnesi elde edilir.
+ _get_future_ fonksiyonu yalnızca bir kez çağrılabilir.
#### _std::packaged_task_ sınıfı çoğunlukla aşağıdaki gibi kullanılır:
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

#### sınıfın üye fonksiyonları
- ::valid <br>
_packaged_task_ nesnenin bir _"shared_state"_ ile ilişkilendirilmiş durumda olup olmadığını sınar. 
- ::swap<br>
swap two task objects<br>
- ::get_future<br>
get future associated with promised result<br>
- ::operator()<br>
invoke function<br>
- ::make_ready_at_thread_exit<br>
invoke function ensuring result ready only once current thread exits<br>
- ::reset <br>
reset shared state, abandoning any previously stored result<br>


