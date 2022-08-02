#define SCK     4 // chân SCK
#define MOSI    5// Chân MOSI
#define SS      6 // Chân SS
#define MISO    7 // chân MISO

void setup(){
  SPI_setup();
 }
void loop() {
  uint8_t rev;
  SPI_begin();
  rev = SPI_transfer('a');
  
  delay(1000);
  SPI_end();
 

}
void SPI_setup(void) {
  pinMode(MOSI, OUTPUT);
  pinMode(MISO, INPUT);
  digitalWrite(SCK, LOW);
  pinMode(SCK, OUTPUT);
  digitalWrite(SS, HIGH);
  pinMode(SS, OUTPUT);
}
void SPI_begin(void){
  digitalWrite(SS, LOW);
}

void SPI_end(void){
  digitalWrite(SCK, LOW);
  digitalWrite(SS, HIGH);
}
uint8_t SPI_transfer(uint8_t byte_out){
  uint8_t byte_in =0;
  uint8_t res,ibit;
  for(ibit=0x80;ibit>0;ibit=ibit>>1){
   res = byte_out&ibit;
   digitalWrite(MOSI, res);
//   delayMicroseconds(THalf);
   digitalWrite(SCK, HIGH);
   if(digitalRead(MISO) == HIGH)
    byte_in = byte_in | ibit;
//   delayMicroseconds(THalf);
   digitalWrite(SCK, LOW);
  }
  return byte_in;
}
