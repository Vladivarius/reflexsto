void ispis(int bitovi1[32], int bitovi2[32]) {
    digitalWrite(CSD, LOW);
    for(int i=0; i<32; i++) {
        digitalWrite(DIN1, bitovi1[i]);
        digitalWrite(DIN2, bitovi2[i]);
        digitalWrite(SCLD, HIGH);
        //delay(2);
        digitalWrite(SCLD, LOW);
        delayMicroseconds(10);
    }
    digitalWrite(CSD, HIGH);
}

void citanje(int ulazi1[16], int ulazi2[16], int sredjeni1[9], int sredjeni2[9]) {
    digitalWrite(CSB, LOW);
    delayMicroseconds(5);
    digitalWrite(CSB, HIGH);
    delayMicroseconds(5);

    for(int i=0; i<16; i++) {
        digitalWrite(SCLB, HIGH);
        ulazi1[i] = digitalRead(DOUT1);
        ulazi2[i] = digitalRead(DOUT2);
        digitalWrite(SCLB, LOW);
    }

    //sredjujem nizove
    for(int i=2, j=0; i<8; i++, j++) {
        sredjeni1[j]=ulazi1[i];
        sredjeni2[j]=ulazi2[i];
    }
    for(int i=11, j=5; i<=14; i++, j++) {
        sredjeni1[j]=ulazi1[i];
        sredjeni2[j]=ulazi2[i];
    }

    //invertovacemo nizove
    /*for(int i=0; i<16; i++) {
        ulazi1[i] = 1 - ulazi1[i];
        ulazi2[i] = 1 - ulazi2[i];
    }*/

    //debug
    /*for(int i=0; i<9; i++) {
        Serial.print(sredjeni1[i]);Serial.print(" ");
    }Serial.println("                                                ");/*
    for(int i=11; i<16; i++) {
        Serial.print(ulazi1[i]);Serial.print(" ");
    }Serial.println();*/
}

void OcistiNiz(int niz[], int n) {
    for(int i=0; i<n; i++) {
        niz[i]=0;
    }
}
