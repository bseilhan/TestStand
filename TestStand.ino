#include <HX711.h>
#include <LiquidCrystal.h>
#include <Wire.h>

#define DOUT  10
#define CLK  11

#define calibration_factor -11840 

#define SLAVE_ADDRESS 0x04

#define ARRAY_LENGTH 1
float data[ARRAY_LENGTH];

LiquidCrystal lcd(8, 2, 4, 5, 6, 7); 
HX711 scale(DOUT, CLK);
float value = 0;
 
void setup() {
 Wire.begin(SLAVE_ADDRESS);
 Wire.onReceive(receiveData);
 Wire.onRequest(sendData);  
 
 lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display } 
 lcd.print("NFA Test Stand"); // Prints "Arduino" on the LCD
 lcd.setCursor(10,1); 
 lcd.print("oz.");
 lcd.noCursor();
 scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
 scale.tare();

}

void loop() { 
 lcd.setCursor(0,1);
 value = scale.get_units();
 lcd.print("         ");
 lcd.setCursor(0,1);
 lcd.print(value,2);
 delay(500); 
}

// callback for received data
void receiveData(int byteCount)
{
   int number = Wire.read();
   lcd.setCursor(15,0);
   lcd.print(number);
}

  
// callback for sending data
void sendData(){
  data[0]=value;
  Wire.write((byte*) &data, ARRAY_LENGTH*sizeof(float));
}
