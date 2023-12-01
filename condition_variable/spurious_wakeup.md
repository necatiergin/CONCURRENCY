#### spurious wakeup

+ Bazen (önceden öngörülemeyecek biçimde) _reader thread_ bekleme durumunda iken "_spuriously_" (yanlış biçimde) uyandırılır.
+ Oysa _writer thread_ henüz sinyal _(notification)_ göndermemiştir ama _condition variable_ uyumakta olan _reader thread_'i uyandırır.
+ Bunun nedeni _condition variable_'ın gerçekleştirilme _(implementation)_ biçimidir. Böyle uyandırmalardan kaçınmanın maliyeti çok daha yüksek olduğu için _"yanlış uyandırmalara"_ izin verilir.
