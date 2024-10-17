
# Minishell Project Directory Structure
```
/minishell
│
├── src/
│   ├── parser/
│   │   ├── tokenizer.c
│   │   ├── syntax_analysis.c
│   │   └── parser_utils.c
│   ├── executor/
│   │   ├── executor.c
│   │   ├── command_execution.c
│   │   └── execution_utils.c
│   ├── redirection/
│   │   ├── redirection.c
│   │   └── redirection_utils.c
│   ├── pipe/
│   │   ├── pipe.c
│   │   └── pipe_utils.c
│   ├── signals/
│   │   ├── signals.c
│   │   └── signals_utils.c
│   ├── memory/
│   │   ├── memory.c
│   │   └── memory_utils.c
│
├── builtins/
│   ├── cd.c
│   ├── echo.c
│   ├── env.c
│   ├── exit.c
│   ├── export.c
│   ├── pwd.c
│   ├── unset.c
│
├── include/
│   ├── parser.h
│   ├── executor.h
│   ├── redirection.h
│   ├── pipe.h
│   ├── signals.h
│   ├── memory.h
│   ├── builtins.h
│
├── Makefile
├── minishell.h
├── main.c
├── free.c
```

---

# Yapılacak listelemesi
### Parser'i Oluştur (Girdiyi Ayrıştırmak)
- Bu aşamada komutları ve argümanları anlamlı parçalara (tokens) ayırma yapılacak.
- örn. `ls -l` komutunu `ls` ve `-l` olarak ayır

### Executor (Komutları Çalıştırmak)
- Komutları ayrıştırdıktan sonra bu komutları çalıştırmak lazım.
- Bu aşamada dış komutları (örn. ls, echo) çalıştırmayı sağlayacak temel bir executor yazılabilir.
- `fork()` ve `execve()` fonksiyonları bu noktada devreye girecek.
  * Bu aşamada yapılacaklar:
    * src/executor/executor.c dosyasını oluştur.
    * `execve()` ile dış komutları çalıştırmayı dene. Örneğin, kullanıcı ls yazarsa ls komutunu işletim sisteminde çalıştır ve sonucunu döndür.

### Built-in
- Yerleşik komutlar (built-in commands) `cd`, `exit`, `echo`, `env`, `export`, `pwd`, `unset`, `exit` (numeric control)  komutlari bu asamada incelenecek.
- Önemli olan nokta bu komutlar `execve()` ile değil shell tarafından çalıştırılır. Ayrıca işlenmesi gerekli yani.

### Redirection ve Pipe Mekanizması
- Bir sonraki aşama, redirection (giriş/çıkış yönlendirme) ve pipe işlemlerini eklemek olacaktır. Bu adımda kullanıcıların > ve | gibi operatörleri kullanması sağlayanacak. Bu operatörler ile dosyaya yazma ve pipe işlemleri yapılacak.
  * Bu aşamada yapılacaklar:
    * Redirection için `dup2()` kullanarak giriş ve çıkış yönlendirmelerini uygula.
    * `pipe()` ile komutlar arasında veri akışını sağlama.

### Signals Yönetimi (Sinyal İşleme)
- Örneğin, `Ctrl+C` sinyaliyle çalışan bir komutu durdurabilir, `Ctrl+D` ile shell’i kapatılabilir. Bu aşamada sinyal yönetimini implemente edilmeli.
  * Bu aşamada yapılacaklar:
    * `SIGINT`, `SIGQUIT` gibi sinyalleri yakalamak için signal() fonksiyonunu kullan.


### Bellek Yönetimi
- Program boyunca dinamik bellek tahsisi `malloc()` ile, her ayrılan bellek `free()` ile serbest bırakılmalıdır. Bu aşamada, belleğin düzgün serbest bırakıldığından emin olunmalı.
