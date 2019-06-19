/* FSR testing sketch. 
 
Connect one end of FSR to 5V, the other end to Analog 0.
Then connect one end of a 10K resistor from Analog 0 to ground
Connect LED from pin 11 through a resistor to ground 
 
For more information see www.ladyada.net/learn/sensors/fsr.html */

int fsrPins[] = {0,1,2};
int i;
int fsrPin;     // the FSR and 10K pulldown are connected to a0
int fsrReading;     // the analog reading from the FSR resistor divider
int fsrVoltage;     // the analog reading converted to voltage
unsigned long fsrResistance;  // The voltage converted to resistance, can be very big so make "long"
unsigned long fsrConductance; 
unsigned long fsrForce;       // Finally, the resistance converted to force


 
void setup(void) {
  Serial.begin(9600);   // We'll send debugging information via the Serial monitor
}
 
void loop(void) {
  for(i = 3; i < 4; i++){
    fsrPin = fsrPins[i];
    fsrReading = analogRead(fsrPin);  
    Serial.print("Analog reading = ");
    Serial.println(fsrReading);
   
    // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
    fsrVoltage = map(fsrReading, 0, 773, 0, 3300);
    Serial.print("Voltage reading in mV = ");
    Serial.print(fsrVoltage);  
    Serial.print(" on sensor ");
    Serial.println(fsrPin);

  


 }
  Serial.println("--------------------");
  delay(1000);
}
