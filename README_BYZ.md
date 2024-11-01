## YAPILANLAR: 14/09/2024

1. **Argüman sayısı kontrolü yapıldı.**
2. **Initialize data işlemi gerçekleştirildi:**
   - `Initialize env` ile hem hata kontrolü yapıldı hem de `data->env` içerisine ortam değişkenleri (env) aktarıldı.
   - **Çalışma dizini (Working Directory) initialize edilerek**, `getcwd` (current working directory) ile programın çalıştırıldığı dizin alındı. Ayrıca, `cd` komutuyla başka bir dizine geçiş yapıldığında oluşan `OLDPWD` işlendi.
3. **data struct'ının içerisi NULL, global değişkene ise 0 atandı.**
4. **data->user_input**, `readline` ile alındı. Define edilen `PROMPT` ile terminaldeki `"minishell>$"` yazısının renkli görünmesi sağlandı.

*PATH_MAX'teki 4096 değeri, Linux ve Mac sistemlerinde bir dosya yolunun maksimum uzunluğunu ifade eder.*


** HATA DURUMLARI
 - "export i" durumu kontrol edilecek bu durumda export listesine eklenirken env listesine eklenmemsi gerekiyor
 -  echo $a işlemesi echo modda hatalı çalışıyor. 
  - export a='
  - exp: echo $a"kj"$a
 - space tab gelince seg errero kontrol edilecek
