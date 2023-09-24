#include "pinovi.h"
#include "cifrebin.h"
#include "funkcije.h"
#include "muzika.h"

#define DUZINA_SEK 30 //+15
#define INTERVAL 400

const int prazan_32[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int izlaz1[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int izlaz2[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int ulaz1[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ulaz2[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

int novastanja1[9] = {0,0,0,0,0,0,0,0,0};
int novastanja2[9] = {0,0,0,0,0,0,0,0,0};
int sredjenulaz1[9] = {0,0,0,0,0,0,0,0,0};
int sredjenulaz2[9] = {0,0,0,0,0,0,0,0,0};

int zetoni = 0;

int poeni1=0, poeni2=0;

unsigned long pocetnovr = 0, prev = 0;

void setup() {
    Serial.begin(115200);
    podesiPinove();
    intToNiz(izlaz1, 0);
    intToNiz(izlaz2, 0);
    ispis(izlaz1, izlaz2);
    zetoni=0;
}

void loop() {
    if(digitalRead(COIN)) { //Spaja na masu kada vidi zeton i drzi tako 100ms
        zetoni=1;
        Serial.println(zetoni);
        delay(200);
    }
    if(digitalRead(START) && zetoni>=1) { //obrisi ! kada bude postojao taster
        PrecistiSve();
        intToNiz(izlaz1, 0);
        intToNiz(izlaz2, 0);
        ispis(izlaz1, izlaz2);
        
        zetoni= zetoni - 1;
        Serial.println(zetoni);
        Igrica();
        Kraj();
    }
}

void PrecistiSve() {
    OcistiNiz(izlaz1, 32);
    OcistiNiz(izlaz2, 32);
    OcistiNiz(ulaz1, 16);
    OcistiNiz(ulaz2, 16);
    OcistiNiz(novastanja1, 9);
    OcistiNiz(novastanja2, 9);
    OcistiNiz(sredjenulaz1, 9);
    OcistiNiz(sredjenulaz2, 9);
    poeni1 = 0; poeni2 = 0;
}

void Igrica() {    //Ovde ce se odvijati cela igra
    for(int i = 3; i>=0; i--) {
        intToNiz(izlaz1, i);
        intToNiz(izlaz2, i);
        ispis(izlaz1, izlaz2);
        delay(1000);
    }
    pocetnovr = millis();
    prev = pocetnovr;
    unsigned long curr = millis()-pocetnovr;
    while(DUZINA_SEK*1000>curr) {
        curr = millis()-pocetnovr;
        if(curr-prev>INTERVAL) {
            int r1 = random(9), r2 = random(9);
            intToNiz(izlaz1, poeni1);
            intToNiz(izlaz2, poeni2);
            novastanja1[r1] = 1;
            novastanja2[r2] = 1;
            izlaz1[14] = novastanja1[0];
            izlaz2[14] = novastanja2[0];
            for(int i=0; i<8; i++) {
                izlaz1[i] = novastanja1[i+1];
                izlaz2[i] = novastanja2[i+1];
            }
            prev = millis()-pocetnovr;
        }
        
        
        citanje(ulaz1, ulaz2, sredjenulaz1, sredjenulaz2);

        ProveraPogodaka(novastanja1, novastanja2, sredjenulaz1, sredjenulaz2);

        ispis(izlaz1, izlaz2);

        Process_Muzika();
        
        /*for(int i=0; i<9; i++) { ///Ova for petlja ce ispisivati umesto lampica kad se oslobodi komentara
            Serial.print(novastanja1[i]);
        }Serial.println();
        /*for(int i=0; i<32; i++) {
            Serial.print(izlaz1[i]);
        }Serial.println();
        for(int i=0; i<32; i++) {
            Serial.print(izlaz2[i]);
        }Serial.println();*/
    }
}

void Kraj() {
    PustiMuziku(1);
        if(poeni1>poeni2) {
            //pobedio 1.
            
            for(int i=0; i<5; i++) {
                izlaz1[14] = 1;for(int i=0; i<8; i++) {izlaz1[i] = 1;ispis(izlaz1, izlaz2);}
                izlaz2[14] = 0;for(int i=0; i<8; i++) {izlaz2[i] = 0;ispis(izlaz1, izlaz2);}
                delay(300);
                izlaz1[14] = 0;for(int i=0; i<8; i++) {izlaz1[i] = 0;ispis(izlaz1, izlaz2);}
                delay(500);
            }
            
        } else if(poeni2>poeni1) {
            //pobedio 2.
            
            for(int i=0; i<5; i++) {
                izlaz1[14] = 0;for(int i=0; i<8; i++) {izlaz1[i] = 0;ispis(izlaz1, izlaz2);}
                izlaz2[14] = 1;for(int i=0; i<8; i++) {izlaz2[i] = 1;ispis(izlaz1, izlaz2);}
                delay(300);
                izlaz2[14] = 0;for(int i=0; i<8; i++) {izlaz2[i] = 0;ispis(izlaz1, izlaz2);}
                delay(500);
            }
            
            
        } else if(poeni2==poeni1) {
            //nereseno
            for(int i=0; i<5; i++) {
                izlaz1[14] = 1;izlaz2[14] = 1;for(int i=0; i<8; i++) {izlaz1[i] = 1;izlaz2[i] = 1;ispis(izlaz1, izlaz2);}
                delay(300);
                izlaz1[14] = 0;izlaz2[14] = 0;for(int i=0; i<8; i++) {izlaz1[i] = 0;izlaz2[i] = 0;ispis(izlaz1, izlaz2);}
                delay(500);
            }
            
        }

        delay(3000);
        /*PrecistiSve(); // Prebacili smo da stoji dok se ne klikne START
        delay(2000);
        /*intToNiz(izlaz1, 0);
        intToNiz(izlaz2, 0);
        ispis(izlaz1, izlaz2);*/
}

void ProveraPogodaka(int nova1[9], int nova2[9], int ulaz1[9], int ulaz2[9]) {
    for(int i=0; i<9; i++) {
        if(nova1[i]==1 && ulaz1[i]==0) {
            nova1[i]=0;
            poeni1+=1;
            PustiMuziku(0);
        }
        if(nova2[i]==1 && ulaz2[i]==0) {
            nova2[i]=0;
            poeni2+=1;
            PustiMuziku(0);
        }
    }
}
