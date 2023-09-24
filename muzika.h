int ton0, ton1 = -1; //Koji ton po redu sviramo
unsigned long timer_tone = 0; //Trenutak u kome treba da se pusti sledeci ton

float tonovi0[] = { 2000, 2000, 3000, 3000, 0}; //frekvencija 0 znaci kraj, tzv terminator kao u stringovima
// int trajanje0[] = {}... ali ovo ti ne treba jer si svuda stavio da ton traje 100ms

float tonovi1[] = { 130.81, 146.83, 164.81, 164.81, 164.81, 146.83, 146.83, 130.81, 0 };
// int trajanje1[] = {}... ali ovo ti ne treba jer si svuda stavio da ton traje 100ms

void Process_Muzika() {
    if (ton0 != -1) { //U toku je melodija 0
        if (millis() > timer_tone) {//doslo vreme da se odsvira sledeci ton
            if (tonovi0[ton0] == 0) { //dosli smo do kraja
                ton0 = -1;  //Stavimo da se ne svira vise melodija 0
                noTone(BUZ); //Zaustavimo ton
            }         
            else { //
                tone(BUZ, tonovi0[ton0]);
                ton0++;
                timer_tone = millis() + 100; //Umesto 100 ovde bi islo trajanje0[ton0]    
            }
        }
    }

    if (ton1 != -1) { //U toku je melodija 0
        if (millis() > timer_tone) {//doslo vreme da se odsvira sledeci ton
            if (tonovi1[ton1] == 0) { //dosli smo do kraja
                ton1 = -1;  //Stavimo da se ne svira vise melodija 0
                noTone(BUZ); //Zaustavimo ton
            }
            else {
                tone(BUZ, tonovi1[ton1]);
                ton1++;
                timer_tone = millis() + 100; //Umesto 100 ovde bi islo trajanje0[ton0]          
            }
        }
    }
}

void PustiMuziku(int n) {
    if (n == 0) ton0 = 0;//stavimo ton0 na prvu notu
    else if (n == 1) ton1 = 0;//stavimo ton1 na prvu notu
}
