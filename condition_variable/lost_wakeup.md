#### lost wakeup

+ _condition_variable_ sınıfının _wait_ fonksiyonu sınıfın _notify_ fonksiyonu çağrılana kadar _thread_'i bloke eder.
+ eğer _writer thread_'de _notify_ fonksiyonu _reader thread_'deki _wait_ çağrısından daha önce gerçekleştirilirse bir sinyal _(notification)_ gönderilmiş olmasına karşın henüz beklemekte olan bir _thread_ yoktur.
+ bu durumda _reader thread_ hiçbir şekilde uyanamaz ve bloke olarak kalır.
+ bu duruma _lost-wakeup_ denir. (kod örneğine bakınız)
