#include <Wire.h>
int Address = 0x53;             // Device Specific addresses
#define DATA0 0x32 // Hexadecima address for the DATAX0 internal register.
#define DATA1 0x33 // Hexadecima address for the DATAX1 internal register.
#define Register 0x2D // Power Control Register
int X0,X1;
void setup() {
  Wire.begin(); // Initiate the Wire library
  Serial.begin(9600);
  delay(100);
  // Enable measurement
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(8);  
  Wire.endTransmission();
}
void loop() {
  Wire.beginTransmission(Address); // Begin transmission to the Sensor 
  //Ask the particular registers for data
  Wire.write(DATA0);
  Wire.write(DATA1);
  
  Wire.endTransmission(); // Ends the transmission and transmits the data from the two registers
  
  Wire.requestFrom(Address,2); // Request the transmitted two bytes from the two registers
  
  if(Wire.available()<=2) {  // 
    X0 = Wire.read(); // Reads the data from the register
    X1 = Wire.read();   
  }
  
  Serial.print("X0= ");
  Serial.print(X0);
  Serial.print("   X1= ");
  Serial.println(X1);
}
