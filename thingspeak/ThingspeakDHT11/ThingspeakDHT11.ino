#include <ThingSpeak.h>
#include <ESP8266WiFi.h>
#include <dht.h>
dht DHT;
#define DHT11_PIN 2

// Network parameters
const char* ssid     = "ES_1279";
const char* password = "";

// ThingSpeak information
char thingSpeakAddress[] = "api.thingspeak.com";
unsigned long channelID = 1039140;
char* readAPIKey = "RKFJF5VKCAK5DD3W";
char* writeAPIKey = "HVHSRQ90BNE1G7PU";
const unsigned long postingInterval = 120L * 1000L;
unsigned int dataFieldOne = 1;                            // Field to write temperature data
unsigned int dataFieldTwo = 2;                       // Field to write temperature data

unsigned int aField = 6;                             //Field to hold first constant of the thermistor calibration                
unsigned int bField = 7;                             //Field to hold second constant of the thermistor calibration
unsigned int cField = 8;                             //Field to hold third constant of the thermistor calibration
// Global variables
// These constants are device specific.  You need to get them from the manufacturer or determine them yourself.
float aConst = 2.25E-02;   
float bConst = -0.003422894649;
float cConst = 0.00001518485044;

unsigned long lastConnectionTime = 0;
long lastUpdateTime = 0; 
WiFiClient client;


void setup() {
  // put your setup code here, to run once:

Serial.begin(115200);
Serial.println("Start");
WiFi.begin(ssid, password);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println( "Connected" );
    ThingSpeak.begin( client );

// Read the constants at startup.
aConst = readTSData( channelID, aField );
bConst = readTSData( channelID, bField );
cConst = readTSData( channelID, cField );
}

void loop() {
  // put your main code here, to run repeatedly:
// Update only if the posting time is exceeded
      float chk = DHT.read11(DHT11_PIN);
      float temp = DHT.temperature;
      float humid = DHT.humidity;
    
        Serial.print("Temperature = ");
  Serial.print(temp);
  Serial.print("\nHumidity = ");
  Serial.print(humid);
        write2TSData( channelID , dataFieldOne , temp , dataFieldTwo , humid );
        // Write the temperature in F, C, and time since starting.
}


float readTSData( long TSChannel,unsigned int TSField ){
    
  float data =  ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
  Serial.println( " Data read from ThingSpeak: " + String( data, 9 ) );
  return data;

}

// Use this function if you want to write a single field.
int writeTSData( long TSChannel, unsigned int TSField, float data ){
  int  writeSuccess = ThingSpeak.writeField( TSChannel, TSField, data, writeAPIKey ); // Write the data to the channel
  if ( writeSuccess ){
    
    Serial.println( String(data) + " written to Thingspeak." );
    }
    
    return writeSuccess;
}

// Use this function if you want to write multiple fields simultaneously.
int write2TSData( long TSChannel, unsigned int TSField1, float field1Data, unsigned int TSField2, long field2Data){

  ThingSpeak.setField( TSField1, field1Data );
  ThingSpeak.setField( TSField2, field2Data );
 // ThingSpeak.setField( TSField3, field3Data );
   
  int writeSuccess = ThingSpeak.writeFields( TSChannel, writeAPIKey );
  return writeSuccess;
}
