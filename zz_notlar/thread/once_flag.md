+ Bazı durumlarda bir kodun birden fazla _thread_ tarafından tek bir kez çalıştırılmasını isteriz.
+ Bunu gerçekleştirmek için _std::once_flag_ sınıfı türünden bir değişkeni _std::call_once_ fonksiyon şablonu ile birlikte kullanabiliriz.
+ _std::once_flag_ değişkeni bir eylemin gerçekleşip gerçekleşmediği bilgisini tutan bir bayrak olarak kullanılır.
+ _std::call_once_ fonksiyonunun bildirimi şöyle:
  
```cpp
template <class Callable, class... Args>
void call_once(std::once_flag& flag, Callable&& f, Args&&... args);
```

+ _std::call_once_ _f_ işlevini _flag_ nesnesini kullanarak yalnızca bir kez çağırır.
+ _f_ işlevinin ilk kez çağrılması diğer _thread_'lerin _std::call_once_ çağrılarının _return_ etmesinden önce gerçekleşir.
+ Tipik kullanım senaryorsu, dinamik ömürlü nesnelerin yalnızca bir kez _initialize_ edilmesidir.
