// About Myself

// 👋 Hi, I’m @Riajul-Islam-EWU.  
// 🌏 I'm from Dhaka, Bangladesh.  
// 👀 I’m interested in Website Development and Design.  
// 💻 I’m currently working with Laravel Framework.  
// 💞️ I’m looking to collaborate on Website Development.

// 📫 How to reach me:

// - ✉️ **ritewu2014@gmail.com**
// - 📞 **[+8801722787007](+8801722787007)**
// - 🔎 **[GitHub](https://github.com/Riajul-Islam-EWU)**
// - 🔎 **[LinkedIn](https://www.linkedin.com/in/rit-ewu)**
// - 🔎 **[Twitter](https://twitter.com/rit_ewu)**
// - 🔎 **[Skype](https://join.skype.com/invite/vF7JhBbtaHRQ)**
// **Feel free to contact.**


// Code for Module:

#include <ThingSpeak.h>
#include <DHT.h>
#include <Servo.h>
Servo servo;
Servo servo1;
Servo servo2;
#include <ESP8266WiFi.h>
int P1=16; 
int angle = 0;
String apiKey = "9FTC9KQCTFK2KRXZ"; // Enter your Write API key from ThingSpeak
const char *ssid = "SazzaD_wifi"; // replace with your wifi ssid and wpa2 key
const char *pass = "forgotpassword007";
const char* server = "api.thingspeak.com";
// ThingSpeak information
unsigned long channelID = 857672;
char* readAPIKey = "YOXAGI1IOMNNLR16";
unsigned int dataFieldOne = 4; // Field to write control data 1
unsigned int dataFieldTwo = 7;
// Global variables
// These constants are device specific. You need to get them from the manufacturer or determine them yourself.
float aConst = 2.25E-02;
float bConst = 2.25E-02;
#define DHTPIN 0 //pin where the dht11 is connected
DHT dht(DHTPIN, DHT11);
25 | P a g e
WiFiClient client;
//Dust
int measurePin = A0;
int ledPower = 14;
unsigned int samplingTime = 280;
unsigned int deltaTime = 40;
unsigned int sleepTime = 9680;
float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
void setup() 
{
 Serial.begin(115200);
 delay(10);
 dht.begin();
 pinMode(P1,INPUT);
 
 servo.attach(5);
 servo.write(0);
 delay(100);
 
 servo1.attach(4);
 servo1.write(0);
 delay(100);
 servo2.attach(12);
 servo2.write(0);
 delay(100);
 Serial.println("Connecting to ");
 Serial.println(ssid);
 WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED) 
26 | P a g e
 {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 ThingSpeak.begin( client );
 // Read the constants at startup.
 aConst = readTSData( channelID, dataFieldOne );
 bConst = readTSData( channelID, dataFieldTwo );
 //Serial.println(aConst);
 delay(1000);
 //Dust
 pinMode(ledPower,OUTPUT); 
}
void loop() 
{
 //Dust
 Serial.println (" ");
 digitalWrite(ledPower,LOW);
 delayMicroseconds(samplingTime);
 voMeasured = analogRead(A0);
 delayMicroseconds(deltaTime);
 digitalWrite(ledPower,HIGH);
 delayMicroseconds(sleepTime);
 calcVoltage = voMeasured*(5.0/1024);
 dustDensity = 0.17*calcVoltage-0.1;
 if ( dustDensity < 0)
 {
 dustDensity = 0.00;
 }
 //Serial.println("Dust Density:");
27 | P a g e
// Serial.println(dustDensity);
 if (dustDensity<0.10)
 {
 // digitalWrite(13,HIGH);
 Serial.println("no dust");
 
 servo2.write(180); //command to rotate the servo to the specified angle
 delay(1000); 
 }
 else if(dustDensity>0.10)
 {
 servo2.write(0);
 delay(1000);
 }
 
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 int P1 = digitalRead(16);
 int massage =1;
 
 if(P1==HIGH)
 {
 for(angle = 0; angle < 180; angle += 5) // command to move from 0 degrees to 180 degrees 
 { 
 servo.write(angle);//command to rotate the servo to the specified angle
 servo1.write(angle);
 delay(0); 
 } 
 }
 delay(1000);
 /* else if(P1==LOW)
 {
 servo.write(0);
 delay(1000);
 }*/ 
 
Serial.println("Waiting..."); //reading data from thing speak
 aConst = readTSData( channelID, dataFieldOne );
 Serial.println(aConst);
28 | P a g e
 if(aConst==HIGH)
 {
 for(angle; angle>=1; angle-=5) // command to move from 180 degrees to 0 degrees 
 { 
 servo.write(angle);//command to rotate the servo to the specified angle
 servo1.write(angle); 
 delay(5); 
 }
 }
 
 Serial.println("Waiting..."); //reading data from thing speak
 bConst = readTSData( channelID, dataFieldTwo );
 Serial.println(bConst); 
 
 if(bConst==HIGH && angle<1)
 {
 for(angle ; angle < 180; angle += 5) // command to move from 0 degrees to 180 degrees 
 { 
 servo.write(angle);//command to rotate the servo to the specified angle
 servo1.write(angle); 
 delay(5); 
 }
 } 
 
 if(t>38 && P1==LOW)
 {
 if(angle>10)
 {
 for(angle; angle>=1; angle-=5) // command to move from 180 degrees to 0 degrees 
 { 
 servo.write(angle);//command to rotate the servo to the specified angle
 servo1.write(angle); 
 delay(5); 
 }
 } 
 }
 else if(t<25)
 {
29 | P a g e
 if(angle<1)
 {
 for(angle ; angle < 180; angle += 5) // command to move from 0 degrees to 180 degrees 
 { 
 servo.write(angle);//command to rotate the servo to the specified angle
 servo1.write(angle);
 delay(0); 
 } 
 } 
 } 
 
 if (isnan(h) || isnan(t)) 
 {
 Serial.println("Failed to read from DHT sensor!");
 return;
 }
 if (client.connect(server,80)) // "184.106.153.149" or api.thingspeak.com
 { 
 String postStr = apiKey;
 postStr +="&field1=";
 postStr += String(t);
 postStr +="&field2=";
 postStr += String(h);
 postStr +="&field3=";
 postStr += String(P1);
 postStr +="&field5=";
 postStr += String(dustDensity);
 if(angle<1)
 {
 postStr +="&field6=";
 postStr += String(massage);
 }
 else if(angle>10)
 {
 massage = 0;
 postStr +="&field6=";
 postStr += String(massage);
 }
 postStr += "\r\n\r\n";
30 | P a g e
 client.print("POST /update HTTP/1.1\n");
 client.print("Host: api.thingspeak.com\n");
 client.print("Connection: close\n");
 client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
 client.print("Content-Type: application/x-www-form-urlencoded\n");
 client.print("Content-Length: ");
 client.print(postStr.length());
 client.print("\n\n");
 client.print(postStr);
 Serial.print("Temperature: ");
 Serial.print(t);
 Serial.println (" ");
 Serial.print(" degrees Celcius, Humidity: ");
 Serial.print(h);
 Serial.println (" ");
 Serial.print(", Motion: ");
 Serial.print(P1);
 Serial.println (" ");
 Serial.print(", Dust Density (ug /m3): ");
 Serial.print(dustDensity);
 Serial.println (" ");
 Serial.println(". Send to Thingspeak.");
 }
 client.stop();
 Serial.println (" ");
 Serial.println (" ");
 Serial.println("Waiting...");
 
 // thingspeak needs minimum 15 sec delay between updates
 delay(1000);
 //Dust
/*Serial.print ("Dust Density (ug /m3) = ");
Serial.print (FineDust);
31 | P a g e
Serial.println (" ");*/
delay (3000);
 
}
float readTSData( long TSChannel, unsigned int TSField ) {
 float data = ThingSpeak.readFloatField( TSChannel, TSField, readAPIKey );
 Serial.println( "Data read from ThingSpeak: " + String( data, 9 ) );
 return data;
}