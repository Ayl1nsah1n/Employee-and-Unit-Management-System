/**
* main.c
* Bu proje parametre olarak girilen birim ve calisanları dosyalarda tutarak belirli fonksiyonlarla değişiklikler yapmayı sağlar.
* 1. Ödev
* 22/12/2024 
* Aylin Şahin aylin.sahin@stu.fsm.edu.tr 
*/

#include <stdio.h>
#include <stdlib.h>
#include "proje.h"



int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Kullanim: %s <birimler_dosya_yolu> <calisanlar_dosya_yolu>\n", argv[0]);
        return 1;
    }

    const char *birimlerDosyaAdi = argv[1];
    const char *calisanlarDosyaAdi = argv[2];

    int birimSayisi = 0;
    Birim *birimler[MAX_CALISAN] = {0};

    Birim *birim1 = yeniBirimOlustur("Muhasebe", 101);
    Birim *birim2 = yeniBirimOlustur("IT", 102);

    birimEkle(birimler, &birimSayisi, birim1);
    birimEkle(birimler, &birimSayisi,birim2);

    Calisan *calisan1 = yeniCalisanOlustur("Kadir", "Mete", 101, 8000.0, 2010);
    Calisan *calisan2 = yeniCalisanOlustur("Elif", "Cakil", 101, 9000.0, 2015);
    Calisan *calisan3 = yeniCalisanOlustur("Efe", "Demir", 102, 12000.0, 2012);
    Calisan *calisan4 = yeniCalisanOlustur("Zeynep", "Yildiz",102, 11000.0, 2013);
    // Çalışanları birimlere ekleme
    calisanEkle(birim1, calisan1);
    calisanEkle(birim1, calisan2);
    calisanEkle(birim2, calisan3);
    calisanEkle(birim2, calisan4);

    // Birimleri listeye ekleme
    birimler[birimSayisi++] = birim1;
    birimler[birimSayisi++] = birim2;

    printf("\nTum Birim Bilgileri:\n");
    tumBirimBilgileriYazdir(birimler, birimSayisi);

    // Ortalama maaşları hesaplayıp yazdır
    printf("\nMaas Ortalamalari:\n");
    birimMaasOrtalamasiHesapla(birimler[0]);
    birimMaasOrtalamasiHesapla(birimler[1]);

   

    // Ortalama maaşın üzerindeki çalışanları listele
    printf("\nOrtalama Maasin Uzerinde Kazananlar:\n");
    birimUstuMaasCalisanlariListele(birimler[0]);
    birimUstuMaasCalisanlariListele(birimler[1]);

    

    // Her birimdeki en yüksek maaşlı çalışanı yazdır
    printf("\nBirimlerdeki En Yuksek Maasli Calisanlar:\n");
    birimEnYuksekMaasCalisaniYazdir(birimler[0]);
    birimEnYuksekMaasCalisaniYazdir(birimler[1]);
    
    

    // Maaşları güncelle
    printf("\nMaas Guncellemeleri:\n");
    maasGuncelle(birimler[0], 10000.0);
    maasGuncelle(birimler[1], 10000.0);

    

    // Bilgileri dosyaya kaydet
    printf("\nBilgiler dosyaya kaydediliyor...\n");
    bilgileriDosyayaYaz(birimlerDosyaAdi, calisanlarDosyaAdi, &birimSayisi, birimler);

    // Belleği serbest bırak
    for (int i = 0; i < birimSayisi; i++) {
        for (int j = 0; j < birimler[i]->calisanSayisi; j++) {
            free(birimler[i]->birimCalisanlar[j]->calisanAdi);
            free(birimler[i]->birimCalisanlar[j]->calisanSoyadi);
            free(birimler[i]->birimCalisanlar[j]);
        }
        free(birimler[i]->birimAdi);
        free(birimler[i]->birimCalisanlar);
        free(birimler[i]);
    }

    return 0;
}