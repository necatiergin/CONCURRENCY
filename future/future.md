_std::future_ ve _std::promise_ sınıfları (sınıf şablonları) standart kütüphaneye _C++11_ standartları ile eklendi.;
_std:future_, standart _\<future>_ başlık dosyasında tanımlanmış bir sınıf şablonu. (C++11)
Bir operasyonun sonucunu _(outcome)_ temsil ediyor. (Ya çalıştırılacak bir fonksiyonun geri dönüş değeri ya da çalıştırılacak fonksiyondan gönderilecek _exception_. Ama ikisi birden değil)

```
template <class T> 
class future; 

template <class T > 
class future<T&>;  //partial specialization

template<> 
class future<void>; //void türü için explicit specialization 

```

Sonuç bir _shared state_ içinde tutuluyor. Bu _shared state_ 
+ std::async fonksiyonu tarafından
+ std::packaged_task tarafından
+ std::promise tarafından
  
oluşturulmuş olabilir. 
_std::future_ nesnesi oluşturulduğunda onun tutacağı sonuç henüz hazır olmayabilir. 
Gelecekte oluşacak bir sonucu tutmak için olanaklara sahip.
  
  
Sonuç _std::future_ nesnesi tarafından sadece bir kez _get_ edilebilir. 
Bir kez _get()_ fonksiyonu çağrıldıktan sonra _future_ nesnesi geçersiz hale gelir. <br>

Geçersiz bir _future_ nesnesi için sadece 
+ destructor
+ valid()
+ move assignment

işlevleri çağrılabilir. Başka bir işlevin çağrılması tanımsız davranıştır.


