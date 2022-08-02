#include<stdint.h>
#define SCK     TRISB4   // I2C bus
#define SDA     TRISB1  //
#define SCK_IN  RB4    // 
#define SDA_IN  RB1    //
//dia chi mot slave

//bit start, 8 bit addr(bit w/r), bit ack/nack, bit data (8), ack/nack,data ... stop 
// khoi tao ban dau
    SDA = 1;
    SCK = 1;
void delay(){
    for (int i = 0; i < 1000000; i++)
    {
        //doi tin hieu tu slave
    }
    
}

void I2C_start(){
    //Điều kiện bắt đầu I2C được xác định là  Chuyển đổi từ cao xuống thấp trên đường SDA khi SCL ở mức cao 
    SDA = 1;    //SDA mức cao
    delay();
    SCK = 1;    //xung mức cao
    delay();
    SDA = 0;    //kéo xuong muc thap de truyen du lieu
    delay();    
    SCK = 0;    //sck thấp , chuyen bị tao xung truyen du lieu
    delay();    

}   
void I2C_stop(){
    ////Điều kiện bắt đầu I2C được xác định là  Chuyển đổi từ thấp lên cao trên đường SDA khi SCL ở mức cao
    SDA = 0;    //SDA dang muc thap
    delay();
    SCK = 1;    
    delay();
    SDA = 1;    //thay che do cua SDA
    delay();    //dung xung clk

}
uint8_t TX_i2c(uint8_t data){
    // bit 7 den 0 (MSB to LSB) va 1 xung ack
    uint8_t x;
    static unsigned b;
    // write data to slave
    for(int i=0;i<9;i++){
        x = data & 0x80;
        if (x > 0)
            SDA = 1;
        else
            SDA = 0;
        SCK = 1;
        data >> 1;
        SCK = 0;
    }
    // doc ACK tu slave
    SDA = 1;
    SCK = 1;
    delay();
    b = SDA_IN;
    SCK = 0;
    return b;            
}
unsigned char RX_i2c(char ack){
    /*  Dữ liệu đầu vào I2C thường được gửi ra từ bit 7 đến 0 (MSB đến LSB) bởi máy chủ.
     * Trước tiên, chúng ta cần kiểm tra xem chúng ta có thể kéo SCL cao hay không,
     * đảm bảo không kéo dài đồng hồ.
     * Tiếp theo, đặt giá trị SDA vào bit Thấp, và sau đó dịch chuyển sang trái mỗi lần một bit,
     * và kết thúc xung này
     * Cuối cùng, hãy gửi một ACK nếu có một byte khác cần đọc */
    
    uint8_t d =0;
    SDA = 1;
    
    // doc tu slave
    for(int x=0 ; x< 8; x ++) {
        d <<= 1 ;                // di den bit tiep theo
         do {
            SCK = 1 ;            // master phai o muc cao
         }
        while(SCK_IN ==0);       // doi xung SCK delay toi khi o muc thap
        delay ();             // slave ready, SCL_IN tro lại high
        if(SDA_IN ) d |= 1 ;    // lay data gan vao d
        SCK = 0 ;                // finish this bit
    }
    
    // Send ACK back to slave
    if(ack) SDA = 0 ;            // Nếu ack là 0
    else SDA = 1 ;
    SCK = 1;
    i2c_dly();                   // master gui ACK bit thu n
   
    SCK = 0;                     // SCL and SDA get initialize
    SDA = 1;
    return d ;
}
void main (){
    //vi du truyen nhan
     i2c_start();                 
   
                                 
    i2c_tx(0xE0 );               
    i2c_tx(0x01 );               
   
                                 
    i2c_start();                 
    i2c_tx(0xE1 );               
    sensor = i2c_rx (1);    
    rangehigh = i2c_rx (1);      
    rangelow = i2c_rx (0);       
    i2c_stop();
}