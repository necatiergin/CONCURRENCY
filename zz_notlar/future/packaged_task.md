#### std::packaged_task

_std::packaged_task_, eşzamanlı programlama _(concurrent programming)_ için kullanılan bir sınıftır. Bu sınıf, bir fonksiyonu ya da  çağrılabilir bir nesneyi _(callable object)_ sarmalar ve bu fonksiyonun çalıştırılması sonucunda üretilen değeri ya da _exception_'ı bir _std::future_ nesnesi aracılığıyla kullanıma sunar. 
_std::packaged_task_, genellikle _thread_'ler arasında görev tabanlı iletişim kurmak için kullanılır.

+ _std::packaged_task_ sınıfı türünden bir nesne senkron ya da asenkron çağrı yapmak amaçlı bir _callable_ sarmalar. Sarmalanan fonksiyon, daha sonra bir başka _thread_'de veya başka bir bağlamda çalıştırılabilir.
+ _std::packaged_task_ nesnesinin _get_future_ işlevi ile onunla ilişkilendirilmiş _std::future_ nesnesini elde edilir. Paketlenen fonksiyon çalıştırıldığında, üretilen değer veya wxception, bir _std::future_ nesnesi aracılığıyla alınabilir.
+ sınıfın fonksiyon çağrı operatör fonksiyonu sarmalanan _callable_'ı çağırır.
+ _std::packaged_task_, taşınabilir _(movable)_ ancak kopyalanamaz _(non-copyable)_ bir sınıftır. 
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

#### _std::packaged_task_ sınıfı senkron olarak kullanılabilir:
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
Oluşturulan _task_ bir _thread_'e iş yükü olarak da verilebilir:

```
	std::packaged_task<int(int, int)> ptask([](int a, int b)
					{ return a * a + b * b; });
        std::jthread th{std::move(ptask), 4, 7};
```


#### sınıfın üye fonksiyonları
- **::valid**  : _packaged_task_ nesnenin bir _"shared_state"_ ile ilişkilendirilmiş durumda olup olmadığını sınar. 
- **::swap**   : iki nesneyi takas eder.
- **::get_future** : get future associated with promised result<
- **::operator()** : invoke function
- **::make_ready_at_thread_exit** : _thread_ sonlandığında değeri hazır hale getirir.<br>
- **::reset** : paylaşılan durumu reset eder.Yeni bir _std::future_ nesnesi alınabilir hale getirir. Bu, aynı görevin _(task)_ tekrar çalıştırılmasını sağlar.

