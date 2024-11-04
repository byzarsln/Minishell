## YAPILANLAR: 14/09/2024

1. **Argüman sayısı kontrolü yapıldı.**
2. **Initialize data işlemi gerçekleştirildi:**
   - `Initialize env` ile hem hata kontrolü yapıldı hem de `data->env` içerisine ortam değişkenleri (env) aktarıldı.
   - **Çalışma dizini (Working Directory) initialize edilerek**, `getcwd` (current working directory) ile programın çalıştırıldığı dizin alındı. Ayrıca, `cd` komutuyla başka bir dizine geçiş yapıldığında oluşan `OLDPWD` işlendi.
3. **data struct'ının içerisi NULL, global değişkene ise 0 atandı.**
4. **data->user_input**, `readline` ile alındı. Define edilen `PROMPT` ile terminaldeki `"minishell>$"` yazısının renkli görünmesi sağlandı.

*PATH_MAX'teki 4096 değeri, Linux ve Mac sistemlerinde bir dosya yolunun maksimum uzunluğunu ifade eder.*


** HATA DURUMLARI
  DONE:
 <!-- -  echo $a işlemesi echo modda hatalı çalışıyor.  -->
   - export a='
   - exp: echo $a"kj"$a

  DONE:
 <!-- - unset  durumunda hata var.hataya ulaşmak için aşağıdakileri yap
   - export i
   - export i=asim
   - unset i
   - export
 - bu işlemleri yaptığında env içinden i değeri silinmiş olacak ama export içinde hala var  -->
 - handle_quotes fonksiyonu içerisinde bir yorum satırı bıraktım burada hatanın nedeni yazıyor.

 - sinyaller döngü durumlarında işlemiyor(control -c)
 - terminaldeki şapka C işareti kaldırılacak
 - ctrl+c durumunun heredoc sırasında kontrol edilmesi 
 - ctrl+c statusünün durmunun 1 olması
 - leakler kontrol edilecek
 - echo $i$i$? hata durumu export i="'"
 <!-- - global exit durumları düzenlenecek --> DONEEEEEEEEEE!
 - control d durumundaki exit yazısı düzeltilecek
 <!-- - çıkışlardaki statusler kontrol edilecek --> DONE


 - lst_delone lardaki kullanılmayan void(*del) fonksiyonların silinmesi gerekiyor.
 - wall wextra werror ile kontrol et