#### std::unique_lock

+ _std::lock_guard_'a göre daha esnek.
+ ctor'a argüman verebiliyoruz.
  - default olarak edindiği _mutex_'in _lock_ fonksiyonu çağırıyor.
  - istersek edindiği mutex'in _try_lock_ fonksiyonunu çağırabiliyor. Bunun için ctor'ın ikinci parametresine _std::try_lock_ sabitini argüman olarak geçiyoruz.
  - istersek mutex'i edinmeden başlatabliyoruz. Bunun için ctor'ın ikinci parametresine _std::defer_lock_ sabitini argüman olarak geçiyoruz.
  - istersek zaten kilidi edinmiş bir _mutex_ ile başlatabiliyoruz. Bunun için ctor'ın ikinci parametresine _std::adapt_lock sabitini argüman olarak geçiyoruz.


