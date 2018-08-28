/*  ADS8688 library example
 *   
 *  PIN CONNECTION: 
 *  
 *  REFSEL: GND (enable internal 4.096V reference)
 *  RST/PD: +5V/+3.3V
 *  AVDD:   +5V/+3.3V
 *  DVDD:   +5V/+3.3V
 *  CS:     pin 10 / MEGA pin 10 / DUE pin 10
 *  SDI:   pin 11 / MEGA pin 51 / DUE ICSP-MOSI
 *  SDO:   pin 12 / MEGA pin 50 / DUE ICSP-MISO
 *  SCK:    pin 13 / MEGA pin 52 / DUE ICSP-SCK
 *  DAISY:  1st chip GND, 2nd chip SDO of 1st 
 */

#include <ADS8688.h>

ADS8688 bank;    
int range = R0;          
int chips = 2;           

void setup() {

  bank.init();                          // Instantiate ADS8688 with PIN 10 as default CS
  bank.setDaisy(chips);                 // define number of daisy-chained chips
  bank.setChannelSPD(0b11111111);
  bank.setGlobalRange(range);              // set range for all channels
  bank.autoRst();                       // reset auto sequence

  Serial.begin(115200);                 // start serial communication
  }

void loop() {
  Serial.print("values: ");             // print label
  for (byte i=0;i<8;i++) {
    uint16_t val[chips];
    bank.noOp(val);
    Serial.print(bank.I2V(val[0],range));   // 2nd chip
    Serial.print("|");
    Serial.print(bank.I2V(val[1],range));   // 1st chip
    Serial.print("\t");
  }
  Serial.println();
  delay(500);                           // wait for 500 milliseconds
}