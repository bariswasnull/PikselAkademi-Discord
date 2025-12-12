## Katkı ve Teşekkür

Bu proje, açık kaynaklı **goodbyeDPI** projesi üzerine kurulmuş bir **otomatik kurulum ve yapılandırma aracıdır**.

Ağ paketleme, DPI uyumluluğu ve düşük seviye ağ davranışları **Çağrı Taşkın (cagritaskn)** tarafından geliştirilen **goodbyeDPI** projesine aittir.

Bu repository:
- goodbyeDPI kaynak kodunu değiştirmez
- goodbyeDPI’yi yeniden implemente etmez
- yalnızca kurulum, yapılandırma ve servis yönetimini otomatikleştirir

Derleme sürecinde, ağ üzerinden dosya indirme işlemleri için **libcurl** kütüphanesi kullanılmaktadır.  
Kaynak koddan derleme yapmak isteyen kullanıcıların, sistemlerinde **libcurl** kütüphanesini kurulu ve yapılandırılmış olarak bulundurmaları gerekmektedir (vcpkg).

Orijinal proje:
https://github.com/cagritaskn/GoodbyeDPI-Turkey
