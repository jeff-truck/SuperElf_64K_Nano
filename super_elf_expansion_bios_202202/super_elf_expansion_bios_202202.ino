#define DATA_SERIAL_IN  2
#define DATA_SERIAL_OUT 3
#define DATA_CLK        4
#define SHIFT_REG_OE    5
#define NADA_01         6
#define ADDRESS_SERIAL  7
#define ADDRESS_SRCLK   8
#define ADDRESS_RCLK    9
#define CONTROL_ADDR_OE 10
#define NADA_02         11
#define NADA_03         12
#define NADA_04         13
#define NANO_RST_P      A0
#define NANO_FGO_P      A1
#define NANO_MRD_N      A2
#define NANO_MWR_N      A3
#define SHIFT_MODE_S0   A4
#define SHIFT_MODE_S1   A5

void turnOnBus() {
  digitalWrite(CONTROL_ADDR_OE, LOW);
  return;
}

void turnOffBus() {
  digitalWrite(CONTROL_ADDR_OE,HIGH);
  digitalWrite(SHIFT_REG_OE, HIGH);
  return;
}

void setDataShiftForShiftDataLeft() { 
  digitalWrite(SHIFT_MODE_S0,LOW);
  digitalWrite(SHIFT_MODE_S1,HIGH);
  clockDataShiftRegister();
  return;
}

void setDataShiftForShiftDataRight() {
  digitalWrite(SHIFT_MODE_S0,HIGH);
  digitalWrite(SHIFT_MODE_S1,LOW);
  clockDataShiftRegister();
  return;
}

void clockDataShiftRegister() {
  delayMicroseconds(1);
  digitalWrite(DATA_CLK,LOW);
  digitalWrite(DATA_CLK,HIGH);
  delayMicroseconds(1);
  digitalWrite(DATA_CLK,LOW);
  return;
}

void setDataShiftForReadRAM() { 
  digitalWrite(SHIFT_MODE_S0,HIGH);
  digitalWrite(SHIFT_MODE_S1,HIGH);
  clockDataShiftRegister();
  digitalWrite(SHIFT_REG_OE,HIGH);
  return;
}

void setDataShiftForWriteRAM() {
  digitalWrite(SHIFT_MODE_S0,LOW);
  digitalWrite(SHIFT_MODE_S1,LOW);
  clockDataShiftRegister();
  digitalWrite(SHIFT_REG_OE,LOW);
  return;
}



void setAddress(long lngAddress) {

  unsigned int intHighByte;
  unsigned int intLowByte;

  intLowByte  = lngAddress;
  intHighByte = lngAddress >> 8;
  
  digitalWrite(ADDRESS_SRCLK,LOW);
  shiftOut(ADDRESS_SERIAL, ADDRESS_SRCLK, MSBFIRST, (intHighByte));

  digitalWrite(ADDRESS_SRCLK,LOW);
  shiftOut(ADDRESS_SERIAL, ADDRESS_SRCLK, MSBFIRST, (intLowByte));

  digitalWrite(ADDRESS_RCLK, LOW);
  digitalWrite(ADDRESS_RCLK, HIGH);
  digitalWrite(ADDRESS_RCLK, LOW);

}

void setDataByte(byte bytData) {

  setDataShiftForShiftDataRight();
  
  for (int bit_ptr = 7; bit_ptr >= 0; bit_ptr--) {
    byte single_bit = bitRead(bytData,bit_ptr);
    digitalWrite(DATA_SERIAL_IN, single_bit);
    clockDataShiftRegister();
  }
  
}

void memoryRead() {
  setDataShiftForReadRAM();
  digitalWrite(NANO_MRD_N,LOW);
  delayMicroseconds(2);
  digitalWrite(NANO_MRD_N,HIGH);
}

void memoryWrite() {
  setDataShiftForWriteRAM();
  digitalWrite(NANO_MWR_N,LOW);
  delayMicroseconds(2);
  digitalWrite(NANO_MWR_N,HIGH);
  digitalWrite(SHIFT_REG_OE,HIGH);
  
}

void setup() {

  digitalWrite(NANO_MWR_N,HIGH);
  digitalWrite(NANO_MRD_N,HIGH);
  digitalWrite(NANO_RST_P,LOW);
  digitalWrite(NANO_FGO_P,LOW);

  digitalWrite(SHIFT_REG_OE,HIGH);
  digitalWrite(CONTROL_ADDR_OE,HIGH);

  digitalWrite(ADDRESS_RCLK,LOW);
  digitalWrite(ADDRESS_SRCLK,LOW);
  
  pinMode(DATA_SERIAL_IN,  OUTPUT);
  pinMode(DATA_SERIAL_OUT, INPUT);
  pinMode(DATA_CLK,        OUTPUT);
  pinMode(SHIFT_REG_OE,    OUTPUT);
  pinMode(NADA_01,         OUTPUT);
  pinMode(ADDRESS_SERIAL,  OUTPUT);
  pinMode(ADDRESS_SRCLK,   OUTPUT);
  pinMode(ADDRESS_RCLK,    OUTPUT);
  pinMode(CONTROL_ADDR_OE, OUTPUT);
  pinMode(NADA_02,         OUTPUT);
  pinMode(NADA_03,         OUTPUT);
  pinMode(NADA_04,         OUTPUT);
  pinMode(NANO_RST_P,      OUTPUT);
  pinMode(NANO_FGO_P,      OUTPUT);
  pinMode(NANO_MRD_N,      OUTPUT);
  pinMode(NANO_MWR_N,      OUTPUT);
  pinMode(SHIFT_MODE_S0,   OUTPUT);
  pinMode(SHIFT_MODE_S1,   OUTPUT);

  Serial.begin(115200);

  Serial.println("Starting Program.");
  
  turnOnBus();
  digitalWrite(NANO_RST_P,HIGH);
  delay(1000);
  digitalWrite(NANO_RST_P,LOW);

  delay(5000);
  
  digitalWrite(NANO_FGO_P,HIGH);
  delay(100);
  digitalWrite(NANO_FGO_P,LOW);
  
  
  turnOffBus();

  
  /*
 
  setAddress(0);
  setDataByte(0x7B);
  memoryWrite();

  setAddress(1);
  setDataByte(0x7A);
  memoryWrite();

  setAddress(2);
  setDataByte(0x30);
  memoryWrite();

  setAddress(3);
  setDataByte(0x00);
  memoryWrite();

  */
  


  /*

  for (long lngAddress = 0; lngAddress <= 1023; lngAddress++) {
    setAddress(lngAddress);
    setDataByte(0x7B);
    memoryWrite();
  }

  for (long lngAddress = 1024; lngAddress <= 2047; lngAddress++) {
    setAddress(lngAddress);
    setDataByte(0x7A);
    memoryWrite();
  }
  
  setAddress(2048);
  setDataByte(0xC0);
  memoryWrite();

  setAddress(2049);
  setDataByte(0x00);
  memoryWrite();

  setAddress(2050);
  setDataByte(0x00);
  memoryWrite();

  */
  


  Serial.println("All Done!");
  
}

/************************************************************************/
/* Loop Code : Run once per initialization                              */
/************************************************************************/

void loop() {

}
