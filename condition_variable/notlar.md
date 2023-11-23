+ Eşzamanlı programlarda, genellikle bir _thread_'in belirli bir olay gerçekleşene kadar beklemesi gerekir (örneğin, bir giriş çıkış işlemi tamamlanana kadar ya da bir veri kullanılabilir duruma gelene kadar).
+ Bir _thread_'in bir olayın gerçekleşip gerçekleşmediğini tekrar tekrar kontrol etmesi verimsiz olabilir (yani işlemci kaynaklarını boşa harcayabilir).
+ _thread_'in bloke edilmesi ve ancak ilgili olay gerçekleştikten sonra yürütülmesinin devam ettirilmesi genellikle daha iyidir.
+ _condition variable_, _thread_'lerin belirli bir koşul gerçekleşene kadar beklemesine (bloke olarak) olanak tanıyan bir senkronizasyon aracıdır.
+ Bir koşul değişkeni, ilgilenilen bazı olaylara karşılık gelir.
+ Bir olayı beklemek isteyen bir _thread_, _condition variable_ üzerinde bir bekleme işlemi gerçekleştirir.
+ Bir veya daha fazla bekleyen _thread_'i bir olaydan haberdar etmek isteyen bir _thread_, _condition variable_ üzerinde bir sinyal işlemi gerçekleştirir.
+ Bununla birlikte, sinyal verilen thread çalışmaya tekrar başladığında, sinyal verilen koşulun doğru olduğu garanti edilmez (ve yeniden kontrol edilmesi gerekir), çünkü örneğin başka bir thread koşulun değişmesine neden olmuş olabilir veya sahte _(spurious)_ bir uyanma meydana gelmiş olabilir.
