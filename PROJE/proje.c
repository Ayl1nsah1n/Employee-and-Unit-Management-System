/**
* proje.c
* Bu proje parametre olarak girilen birim ve calisanları dosyalarda tutarak belirli fonksiyonlarla değişiklikler yapmayı sağlar.
* 1. Ödev
* 22/12/2024 
* Aylin Şahin aylin.sahin@stu.fsm.edu.tr 
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "proje.h"

Birim* yeniBirimOlustur(const char *birimAdi, unsigned short int birimKodu){
    Birim *birim = (Birim*)malloc(sizeof(Birim));
    birim->birimAdi = (char*)malloc(strlen(birimAdi) + 1);
    strcpy(birim->birimAdi, birimAdi);
    birim->birimKodu = birimKodu;
    birim->calisanSayisi = 0;
    birim->birimCalisanlar = (Calisan**)malloc(MAX_CALISAN * sizeof(Calisan*));
    return birim;
}

Calisan* yeniCalisanOlustur(const char *ad, const char *soyad, unsigned short int kod, float maas, int girisYili){
    Calisan *calisan = (Calisan*)malloc(sizeof(Calisan));
    calisan->calisanAdi = (char*)malloc(strlen(ad) + 1);
    strcpy(calisan->calisanAdi, ad);
    calisan->calisanSoyadi = (char*)malloc(strlen(soyad) + 1);
    strcpy(calisan->calisanSoyadi, soyad);
    calisan->birimKodu = kod;
    calisan->maas = maas;
    calisan->girisYili = girisYili;
    return calisan;
}

void calisanEkle(Birim *birim, Calisan *calisan){

 for (int i = 0; i < birim->calisanSayisi; i++) {
        if (birim->birimCalisanlar[i] == calisan) {
            printf("Calisan zaten birime eklenmis: %s %s\n", calisan->calisanAdi, calisan->calisanSoyadi);
            return;
        }
    }

    if(birim->calisanSayisi < MAX_CALISAN){
        birim->birimCalisanlar[birim->calisanSayisi] = calisan;
        birim->calisanSayisi++;
    }else{
        printf("Birime daha fazla calisan eklenemez!\n");
    }
}

void birimEkle(Birim **birimler, int *birimSayisi, Birim *yeniBirim) {
    if (*birimSayisi >= MAX_CALISAN) {
        printf("Daha fazla birim eklenemez! Maksimum sayiya ulasildi.\n");
        return;
    }
    birimler[*birimSayisi] = yeniBirim;
    (*birimSayisi)++;
    printf("Birim %s eklendi.\n", yeniBirim->birimAdi);
}

void calisanBilgiYazdir(const Calisan *calisan){
    printf("Calisan: %s %s\n", calisan->calisanAdi, calisan->calisanSoyadi);
    printf("Birim Kodu: %d\n", calisan->birimKodu);
    printf("Calisan Maasi: %.2f\n", calisan->maas);
    printf("Calisan Giris Yili: %d\n", calisan->girisYili);
}

void birimBilgileriYazdir( Birim *birim){
    printf("\nBirim Bilgileri:\n");
    printf("Birim Adi: %s\n", birim->birimAdi);
    printf("Birim Kodu: %d\n", birim->birimKodu);
    printf("Calisan Sayisi: %d\n", birim->calisanSayisi);
    for(int i = 0; i < birim->calisanSayisi; i++){
        calisanBilgiYazdir(birim->birimCalisanlar[i]);
    }
}

void tumBirimBilgileriYazdir(Birim **birimler, int birimSayisi){
    for(int i = 0; i < birimSayisi; i++){
        birimBilgileriYazdir(birimler[i]);
    }
}

float birimMaasOrtalamasiHesapla(const Birim *birim){
    float maasToplam = 0.0;
    for(int i = 0; i < birim->calisanSayisi; i++){
        maasToplam += birim->birimCalisanlar[i]->maas;
    }
    return birim->calisanSayisi > 0 ? maasToplam / birim->calisanSayisi : 0.0;
}

void birimUstuMaasCalisanlariListele(const Birim *birim){
    float ort = birimMaasOrtalamasiHesapla(birim);
    printf("Ortalama Maas: %.2f\n", ort);
    printf("Ortalamanin uzerindeki maas alan calisanlar:\n");
    for(int i = 0; i < birim->calisanSayisi; i++){
        if(birim->birimCalisanlar[i]->maas > ort){
            calisanBilgiYazdir(birim->birimCalisanlar[i]);
        }
    }
}

void birimEnYuksekMaasCalisaniYazdir(const Birim *birim){
    if(birim->calisanSayisi == 0){
        printf("Birimde calisan yok!\n");
        return;
    }

    Calisan *enYuksekMaasliCalisan = birim->birimCalisanlar[0];
    for(int i = 1; i < birim->calisanSayisi; i++){
        if(birim->birimCalisanlar[i]->maas > enYuksekMaasliCalisan->maas){
            enYuksekMaasliCalisan = birim->birimCalisanlar[i];
        }
    }
    printf("En yuksek maasli calisan: %s %s\n", enYuksekMaasliCalisan->calisanAdi, enYuksekMaasliCalisan->calisanSoyadi);
    printf("Maasi: %.2f\n", enYuksekMaasliCalisan->maas);
}

void maasGuncelle(Birim *birim, float guncelMaas){
    for(int i = 0; i < birim->calisanSayisi; i++){
        if(2024 - birim->birimCalisanlar[i]->girisYili > 10 && birim->birimCalisanlar[i]->maas < guncelMaas){
            birim->birimCalisanlar[i]->maas = guncelMaas;
            printf("Calisan %s %s'nin yeni maasi: %.2f\n", birim->birimCalisanlar[i]->calisanAdi, birim->birimCalisanlar[i]->calisanSoyadi, birim->birimCalisanlar[i]->maas);
        }
    }
}

void bilgileriDosyayaYaz(const char *birimDosyaAdi, const char *calisanDosyaAdi, int *birimSayisi, Birim **birimler){
    FILE *birimDosya = fopen(birimDosyaAdi, "w");
    FILE *calisanDosya = fopen(calisanDosyaAdi, "w");

    if (!birimDosya || !calisanDosya) {
        printf("Dosya acilamadi!\n");
        return;
    }

    for (int i = 0; i < *birimSayisi; i++){
        fprintf(birimDosya, "%s %d\n", birimler[i]->birimAdi, birimler[i]->birimKodu);

        for(int j = 0; j < birimler[i]->calisanSayisi; j++){
            fprintf(calisanDosya, "%s %s %d %.2f %d\n", 
                    birimler[i]->birimCalisanlar[j]->calisanAdi, 
                    birimler[i]->birimCalisanlar[j]->calisanSoyadi, 
                    birimler[i]->birimCalisanlar[j]->birimKodu, 
                    birimler[i]->birimCalisanlar[j]->maas, 
                    birimler[i]->birimCalisanlar[j]->girisYili);
        }
    }

    fclose(birimDosya);
    fclose(calisanDosya);
}

void dosyadanBilgileriOku(const char *birimDosyaAdi, const char *calisanDosyaAdi, int *birimSayisi, Birim **birimler){
    FILE *birimDosya = fopen(birimDosyaAdi, "r");
    FILE *calisanDosya = fopen(calisanDosyaAdi, "r");

    if (!birimDosya || !calisanDosya) {
        printf("Dosya acilamadi!\n");
        return;
    }

    while(!feof(birimDosya)){
        char birimAdi[MAX_AD_UZUNLUK];
        unsigned short int birimKodu;
        if(fscanf(birimDosya, "%s %hu", birimAdi, &birimKodu) != 2) break;

        Birim *birim = yeniBirimOlustur(birimAdi, birimKodu);
        birimler[*birimSayisi] = birim;
        (*birimSayisi)++;
    }

    while (!feof(calisanDosya)){
        char calisanAdi[MAX_AD_UZUNLUK], calisanSoyadi[MAX_AD_UZUNLUK];
        unsigned short int birimKodu;
        float maas;
        int girisYili;

        if(fscanf(calisanDosya, "%s %s %hu %f %d", calisanAdi, calisanSoyadi, &birimKodu, &maas, &girisYili) != 5) break;

        for (int i = 0; i < *birimSayisi; i++) {
            if (birimler[i]->birimKodu == birimKodu) {
                Calisan *calisan = yeniCalisanOlustur(calisanAdi, calisanSoyadi, birimKodu, maas, girisYili);
                calisanEkle(birimler[i], calisan);
                break;
            }
        }
    }

    fclose(birimDosya);
    fclose(calisanDosya);
}