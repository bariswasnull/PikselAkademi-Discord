## Katkı ve Teşekkür

Bu proje, açık kaynaklı **goodbyeDPI** projesi üzerine kurulmuş bir **otomatik kurulum ve yapılandırma aracıdır**.

Düşük seviye ağ paketleme mantığı, DPI uyumluluğu ve temel çalışma prensipleri,
**ValdikSS** tarafından geliştirilen **goodbyeDPI** projesine aittir.

Türkiye’ye özel yapılandırmalar ve kullanım senaryoları ise,
**Çağrı Taşkın (cagritaskn)** tarafından geliştirilen **GoodbyeDPI-Turkey** projesi üzerinden sağlanmaktadır.

Bu repository:
- goodbyeDPI kaynak kodunu değiştirmez
- goodbyeDPI’yi yeniden implemente etmez
- yalnızca kurulum, yapılandırma ve servis yönetimini otomatikleştirir

Derleme sürecinde, ağ üzerinden dosya indirme işlemleri için **libcurl** kütüphanesi kullanılmaktadır.  
Kaynak koddan derleme yapmak isteyen kullanıcıların, sistemlerinde **libcurl** kütüphanesini kurulu ve yapılandırılmış olarak bulundurmaları gerekmektedir (vcpkg).

Orijinal (upstream) proje:  
https://github.com/ValdikSS/GoodbyeDPI

Türkiye uyarlaması (fork):  
https://github.com/cagritaskn/GoodbyeDPI-Turkey
