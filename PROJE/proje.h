/**
* proje.h
* Bu proje parametre olarak girilen birim ve calisanları dosyalarda tutarak belirli fonksiyonlarla değişiklikler yapmayı sağlar.
* 1. Ödev
* 22/12/2024 
* Aylin Şahin aylin.sahin@stu.fsm.edu.tr 
*/

#ifndef PROJE1_H
#define PROJE1_H

#include <stdio.h>


#define MAX_AD_UZUNLUK 30
#define MAX_CALISAN 20



typedef struct {
    char *calisanAdi;
    char *calisanSoyadi;
    unsigned short int birimKodu;
    float maas;
    int girisYili;
} Calisan;

typedef struct {
    char *birimAdi;
    unsigned short int birimKodu;
    Calisan **birimCalisanlar;
    int calisanSayisi;
} Birim;

Birim* yeniBirimOlustur(const char *ad, unsigned short int kod);
Calisan* yeniCalisanOlustur(const char *ad, const char *soyad, unsigned short int kod, float maas, int girisYili);
void birimEkle(Birim **birimler, int *birimSayisi, Birim *yeniBirim);
void calisanEkle(Birim *birim, Calisan *calisan);
void calisanBilgiYazdir(const Calisan *calisan);
void birimBilgileriYazdir(Birim *birim);
void tumBirimBilgileriYazdir(Birim **birimler, int birimSayisi);
float birimMaasOrtalamasiHesapla(const Birim *birim);
void birimUstuMaasCalisanlariListele(const Birim *birim);
void birimEnYuksekMaasCalisaniYazdir(const Birim *birim);
void maasGuncelle(Birim *birim, float guncelmaas);
void bilgileriDosyayaYaz(const char *birimDosyaAdi, const char *calisanDosyaAdi, int *birimSayisi, Birim **birimler);
void dosyadanBilgileriOku(const char *birimDosyaAdi, const char *calisanDosyaAdi, int *birimSayisi, Birim **birimler);

#endif
