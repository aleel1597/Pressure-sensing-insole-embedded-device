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
  pinMode(0,INPUT);//temperature sensor connected to analog 0
  analogReference(DEFAULT);
}
 
void loop(void) {

  Serial.flush();
  for(i = 0; i < 1; i++){
    
    fsrPin = fsrPins[i];
    fsrReading = analogRead(fsrPin);  
   
    // analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
    fsrVoltage = map(fsrReading, 0, 773, 0, 3300);
    Serial.print(fsrVoltage);
    Serial.print("  ");


    if (fsrVoltage != 0) {
      // The voltage = Vcc * R / (R + FSR) where R = 10K and Vcc = 5V
      // so FSR = ((Vcc - V) * R) / V        yay math!
      fsrResistance = 3300 - fsrVoltage;     // fsrVoltage is in millivolts so 5V = 5000mV
      fsrResistance *= 25;                // 10K resistor
      fsrResistance /= fsrVoltage;
      fsrConductance = 1000000;           // we measure in micromhos so 
      fsrConductance /= fsrResistance;
         
      // Use the two FSR guide graphs to approximate the force
      
      if (fsrConductance <= 1000) {
        fsrForce = fsrConductance / 80;
        //Serial.print(".newtons-");  
        Serial.println(fsrForce);
        //Serial.print("sensor-");  
        //Serial.println(fsrPin);  
      } else {
        fsrForce = fsrConductance - 1000;
        fsrForce /= 30;
        //Serial.print(".newtons-");  
        Serial.println(fsrForce);
        //Serial.print("sensor-");  
        //Serial.println(fsrPin);  
      }
    }

 }
  //Serial.println(".--------------------");
  delay(500);
}
