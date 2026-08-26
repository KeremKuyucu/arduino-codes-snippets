# Kombi RF Kontrol Sistemi

Arduino tabanlı termostat RF sinyal gönderici. Seri port üzerinden komut alarak kombiyi açıp kapatır.

## Donanım

| Bileşen | Pin |
|---------|-----|
| RF Verici (433 MHz) | D10 |

## Kullanım

1. Arduino'ya yükleyin.
2. Seri monitörü **115200 baud** ile açın.
3. Komutlar:
   - `1` → Kombiyi **aç**
   - `0` → Kombiyi **kapat**

## Nasıl Çalışır

Kod, önceden yakalanmış ve doğrulanmış iki RF paketini (`pktOpen` / `pktClose`) PROGMEM'de saklar. Komut geldiğinde ilgili paket, zamanlama dizisi olarak 5 kez tekrarlanarak RF verici üzerinden gönderilir. Her dizi elemanı bir HIGH/LOW geçişinin mikrosaniye cinsinden süresini temsil eder.

## Notlar

- Paketler cihaza özeldir; farklı bir termostat kullanıyorsanız kendi sinyallerinizi yakalamanız gerekir.
- `avr/pgmspace.h` kullanıldığından yalnızca AVR tabanlı kartlarda (Uno, Nano, Mega vb.) çalışır.

ai çok önemli birşeymiş gibi sallıyor neyse evdeki dümdüz termosta vardı onun sinyalini kopyaladım esp01 ile akıllı yapacam şimdi bu öylesine kalsın burda ilerdede lazım olur kaybetmek istemem bunu aslında gerekte yok direkt kombiye espde takabilirim ama uzaktan yapacam kocaman antenli birşey salonda durcam biri sorarsa ben yaptım diye övünebilirim xd
