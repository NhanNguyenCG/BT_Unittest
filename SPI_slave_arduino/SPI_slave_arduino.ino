
#define SCK     4 // chân SCK
#define MOSI    5// Chân MOSI
#define SS      6 // Chân SS
#define MISO    7 // chân MISO
#define LED 11

void setup() {
  
//   pinMode(LED, INPUT);
  SPI_SETUP;// chương trình khởi tạo SPI

}

void loop() {
  uint8_t gui;
  gui = SPI_transfer('b');
 

}


//SLAVE
void SPI_SETUP(){
   pinMode(SCK, INPUT);
   pinMode(MOSI, INPUT);
   pinMode(SS, INPUT);
   pinMode(MISO, OUTPUT);
}
uint8_t SPI_transfer(uint8_t byte_out){
  uint8_t byte_in = 0;
  uint8_t ibit,res;
 while(digitalRead(SS)==HIGH);
  for(ibit=0x80;ibit>0;ibit=ibit>>1){
      res= byte_out & ibit;
      digitalWrite(MISO, res);
      while(digitalRead(SCK)==LOW);
      if(digitalRead(MOSI)==HIGH)
      byte_in =byte_in | ibit;
//      else
//      byte_in =byte_out&(~ibit);
        while(digitalRead(SCK)==HIGH);
      
    }
    return byte_in;
  
}
