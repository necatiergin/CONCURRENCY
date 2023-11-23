+ Eşzamanlı programlarda, genellikle bir _thread_'in belirli bir olay gerçekleşene kadar beklemesi gerekir (örneğin, bir giriş çıkış işlemi tamamlanana kadar ya da bir veri kullanılabilir duruma gelene kadar).
+ Bir _thread_'in bir olayın gerçekleşip gerçekleşmediğini tekrar tekrar kontrol etmesi verimsiz olabilir (yani işlemci kaynaklarını boşa harcayabilir).
+ _thread_'in bloke edilmesi ve ancak ilgili olay gerçekleştikten sonra yürütülmesinin devam ettirilmesi genellikle daha iyidir.
+ _condition variable_, _thread_'lerin belirli bir koşul gerçekleşene kadar beklemesine (bloke olarak) olanak tanıyan bir senkronizasyon aracıdır.
