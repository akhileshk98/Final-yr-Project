#include <dht.h>
#include "MQ135.h"
#define ANALOGPIN A0    //  Define Analog PIN on Arduino Board
#define RZERO 206.85    //  Define RZERO Calibration Value



/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Sends and receives message from the server in every 2 seconds
 *  Communicates: wifi_server_01.ino
 */ 
#include <SPI.h>
#include <ESP8266WiFi.h>
MQ135 gasSensor = MQ135(ANALOGPIN);
dht DHT;

#define DHT11_PIN 2
char ssid[] = "AndroidAP";           // SSID of your home WiFi
char pass[] = "plod1395";            // password of your home WiFi

unsigned long askTimer = 0;

IPAddress server(192,168,43,47);       // the fix IP address of the server
WiFiClient client;

void setup() {
  Serial.begin(115200);               // only for debug
  WiFi.begin(ssid, pass);             // connects to the WiFi router
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
     float rzero = gasSensor.getRZero();
  delay(3000);
  Serial.print("MQ135 RZERO Calibration Value : ");
  Serial.println(rzero);
  }
/*  Serial.println("Connected to wifi");
  Serial.print("Status: "); Serial.println(WiFi.status());    // Network parameters
  Serial.print("IP: ");     Serial.println(WiFi.localIP());
  Serial.print("Subnet: "); Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: "); Serial.println(WiFi.gatewayIP());
  Serial.print("SSID: "); Serial.println(WiFi.SSID());
  Serial.print("Signal: "); Serial.println(WiFi.RSSI());*/
  
}

void loop () {
  client.connect(server, 80);   // Connection to the server
  
  Serial.println(".");

  int chk = DHT.read11(DHT11_PIN);
  client.print("Temperature = ");
  client.print(DHT.temperature);
  client.print("\nHumidity = ");
  client.print(DHT.humidity);
  

  float ppm = gasSensor.getPPM();
  client.print("\nCO2 ppm value : ");
  client.print(ppm);
  delay(2000);
  
  
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  
  delay(2000);                  // client will trigger the communication after two seconds
}
