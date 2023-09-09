//ZAJEDNICKI PINOVI
  //DISPLAY
#define SCLD 9
#define CSD 2
  //BUTTON
#define SCLB 3
#define CSB 4
//ZASEBNI
  //P1
#define DIN1 5
#define DOUT1 6
  //P2
#define DIN2 11
#define DOUT2 12

//ZETONJERKA
#define COIN 7

//BUZZER
#define BUZ 8

//START
#define START 10 //proveriti da li je slobodan pa promeniti ako treba

void podesiPinove() {
  pinMode(SCLD, OUTPUT);
  pinMode(CSD, OUTPUT);
  pinMode(SCLB, OUTPUT);
  pinMode(CSB, OUTPUT);
  pinMode(DIN1, OUTPUT);
  pinMode(DOUT1, INPUT);
  pinMode(DIN2, OUTPUT);
  pinMode(DOUT2, INPUT);
  pinMode(COIN, INPUT);
  pinMode(BUZ, OUTPUT);
}
