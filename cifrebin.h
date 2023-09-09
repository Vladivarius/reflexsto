int brojeviArr[10][8] = {
  1,1,1,0,1,1,0,1,
  0,1,0,0,0,0,0,1,
  1,1,0,1,1,1,0,0,
  1,1,0,1,0,1,0,1,
  0,1,1,1,0,0,0,1,
  1,0,1,1,0,1,0,1,
  1,0,1,1,1,1,0,1,
  1,1,0,0,0,0,0,1,
  1,1,1,1,1,1,0,1,
  1,1,1,1,0,1,0,1
};

void matRedToArr(int matrica[10][8], int niz[8], int red) {
    for(int i=0; i<8; i++) {
        niz[i]=matrica[red][i];
    }
}

void intToNiz(int izlazniBitovi[32], int broj) {
  broj = broj%1000;
  int cifre[3];
  cifre[2] = broj%10;
  cifre[1] = (broj%100)/10;
  cifre[0] = broj/100;
  int j[8],d[8],s[8];
  matRedToArr(brojeviArr, j, cifre[2]);
  matRedToArr(brojeviArr, d, cifre[1]);
  matRedToArr(brojeviArr, s, cifre[0]);
  for(int i=24; i<32; i++) {
    if(broj>99){
      izlazniBitovi[i]=s[i-24];
      }else{
        izlazniBitovi[i]=0;
        }
  }
  for(int i=16; i<24; i++) {
    if(broj>9) {
      izlazniBitovi[i]=d[i-16];
      }else{
        izlazniBitovi[i]=0;
        }
  }
  for(int i=8; i<16; i++) izlazniBitovi[i]=j[i-8];
  for(int i=0; i<8; i++) izlazniBitovi[i]=0;
}
