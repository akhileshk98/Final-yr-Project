int PulseSensorPurplePin = A0;        // Pulse Sensor PURPLE WIRE connected to ANALOG PIN 0


int Signal;                // holds the incoming raw data. Signal value can range from 0-1024


// The SetUp Function:
void setup() {
          // pin that will blink to your heartbeat!
   Serial.begin(9600);         // Set's up Serial Communication at certain speed. 
   
}

// The Main Loop Function
void loop() {

  Signal = analogRead(PulseSensorPurplePin);  // Read the PulseSensor's value. 
                                              // Assign this value to the "Signal" variable.

   Serial.println(Signal);                    // Send the Signal value to Serial Plotter.

   
   

delay(1000);
   
   
}
