#include <SoftwareSerial.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <DHT.h>
#include <Wire.h>

#define T1 6
#define T2 5 
#define T3 7 
#define B1 8
#define B2 10
#define B3 9

int Receive = A0;
int Sms = 0;

#define DHTTYPE DHT22

DHT_Unified dht_T1(T1, DHTTYPE);
DHT_Unified dht_T2(T2, DHTTYPE);
DHT_Unified dht_T3(T3, DHTTYPE);

DHT_Unified dht_B1(B1, DHTTYPE);
DHT_Unified dht_B2(B2, DHTTYPE);
DHT_Unified dht_B3(B3, DHTTYPE);

float newTemperature_T1;
float newTemperature_T2;
float newTemperature_T3;

float newTemperature_B1;
float newTemperature_B2;
float newTemperature_B3;

float newHumidity_T1;
float newHumidity_T2;
float newHumidity_T3;

float newHumidity_B1;
float newHumidity_B2;
float newHumidity_B3;

uint32_t delayMS;


float temperature;
float humidity;

unsigned long SendingData = 0;

LiquidCrystal_I2C lcd_A(0x26, 16, 4);
LiquidCrystal_I2C lcd_B(0x27, 16, 4);

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(2, 3); //SIM800L Tx & Rx is connected to Arduino 

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  lcd_A.init();
  lcd_A.backlight();

  lcd_B.begin(16, 4);
  lcd_B.backlight();

  dht_T1.begin();
  dht_T2.begin();
  dht_T3.begin();

  dht_B1.begin();
  dht_B2.begin();
  dht_B3.begin();


  lcd_A.clear();
  lcd_A.setCursor(6, 1);
  lcd_A.print("SYSTEM");
  lcd_A.setCursor(2, 2);
  lcd_A.print("INITIALIZATION");
  delay(1000);

  lcd_B.clear();
  lcd_B.setCursor(6, 1);
  lcd_B.print("SYSTEM");
  lcd_B.setCursor(2, 2);
  lcd_B.print("INITIALIZATION");
  delay(1000);
  
  sensor_t sensor;
  dht_T1.temperature().getSensor(&sensor);
  dht_T2.temperature().getSensor(&sensor);
  dht_T2.temperature().getSensor(&sensor);

  dht_B1.temperature().getSensor(&sensor);
  dht_B2.temperature().getSensor(&sensor);
  dht_B3.temperature().getSensor(&sensor);

  dht_T1.humidity().getSensor(&sensor);
  dht_T2.humidity().getSensor(&sensor);
  dht_T3.humidity().getSensor(&sensor);

  dht_B1.humidity().getSensor(&sensor);
  dht_B2.humidity().getSensor(&sensor);
  dht_B3.humidity().getSensor(&sensor);

  delayMS = sensor.min_delay / 1000;
  // mySerial.println("ATD+ +254748613509;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  // updateSerial();
  // delay(20000); // wait for 20 seconds...
  // mySerial.println("ATH"); //hang up
  // updateSerial();
  // mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  // updateSerial();
  // mySerial.println("AT+CMGS=\"+254748613509\"");//change ZZ with country code and 254714673027 with phone number to sms
  // updateSerial();
  // mySerial.print("SYSTEM TURNED ON"); //text content
  // updateSerial();
  // mySerial.write(26);
  // Wait for SMS send confirmation
  // while (!receivedConfirmation()) {
  //   delay(500); // Wait for 0.5 seconds before checking again
  // }

  // Serial.println("Message sent successfully!");
  // Serial.println(" ");
  // Sms = 0;
  // delay(1000);
}
bool receivedConfirmation() {
  while (mySerial.available()) {
    if (mySerial.find("OK")) {
      return true;
    }
  }
  return false;
}
void loop() {
  delay(delayMS);
  sensors_event_t event_T1;
  sensors_event_t event_T2;
  sensors_event_t event_T3;

  sensors_event_t event_B1;
  sensors_event_t event_B2;
  sensors_event_t event_B3;

  dht_T1.temperature().getEvent(&event_T1);
  dht_T2.temperature().getEvent(&event_T2);
  dht_T3.temperature().getEvent(&event_T3);

  
  lcd_A.clear();
  lcd_A.setCursor(0, 1);
  lcd_A.print("T1: ");
  lcd_A.setCursor(4, 1);
  lcd_A.print(event_T1.temperature, 1);
  lcd_A.setCursor(9, 1);
  lcd_A.print("C");
  lcd_A.setCursor(0, 2);
  lcd_A.print("T2: ");
  lcd_A.setCursor(4, 2);
  lcd_A.print(event_T2.temperature, 1);
  lcd_A.setCursor(9, 2);
  lcd_A.print("C");
  lcd_A.setCursor(0, 3);
  lcd_A.print("T3: ");
  lcd_A.setCursor(4, 3);
  lcd_A.print(event_T3.temperature, 1);
  lcd_A.setCursor(9, 3);
  lcd_A.print("C");

  dht_T1.humidity().getEvent(&event_T1);
  dht_T2.humidity().getEvent(&event_T2);
  dht_T3.humidity().getEvent(&event_T3);


  lcd_A.setCursor(12, 1);
  lcd_A.print(event_T1.relative_humidity, 1);
  lcd_A.setCursor(17, 1);
  lcd_A.print("%");
  lcd_A.setCursor(12, 2);
  lcd_A.print(event_T2.relative_humidity, 1);
  lcd_A.setCursor(17, 2);
  lcd_A.print("%");
  lcd_A.setCursor(12, 3);
  lcd_A.print(event_T3.relative_humidity, 1);
  lcd_A.setCursor(17, 3);
  lcd_A.print("%");
  delay(1000);
  
  
  dht_B1.temperature().getEvent(&event_B1);
  dht_B2.temperature().getEvent(&event_B2);
  dht_B3.temperature().getEvent(&event_B3);

  lcd_B.clear();
  lcd_B.setCursor(0, 1);
  lcd_B.print("B1: ");
  lcd_B.setCursor(4, 1);
  lcd_B.print(event_B1.temperature, 1);
  lcd_B.setCursor(9, 1);
  lcd_B.print("C");
  lcd_B.setCursor(0, 2);
  lcd_B.print("B2: ");
  lcd_B.setCursor(4, 2);
  lcd_B.print(event_B2.temperature, 1);
  lcd_B.setCursor(9, 2);
  lcd_B.print("C");
  lcd_B.setCursor(0, 3);
  lcd_B.print("B3: ");
  lcd_B.setCursor(4, 3);
  lcd_B.print(event_B3.temperature, 1);
  lcd_B.setCursor(9, 3);
  lcd_B.print("C");

  dht_B1.humidity().getEvent(&event_B1);
  dht_B2.humidity().getEvent(&event_B2);
  dht_B3.humidity().getEvent(&event_B3);

  lcd_B.setCursor(12, 1);
  lcd_B.print(event_B1.relative_humidity, 1);
  lcd_B.setCursor(17, 1);
  lcd_B.print("%");
  lcd_B.setCursor(12, 2);
  lcd_B.print(event_B2.relative_humidity, 1);
  lcd_B.setCursor(17, 2);
  lcd_B.print("%");
  lcd_B.setCursor(12, 3);
  lcd_B.print(event_B3.relative_humidity, 1);
  lcd_B.setCursor(17, 3);
  lcd_B.print("%");
  delay(1000);
  if(millis() - SendingData >= 1000) { // Check every 2 seconds
    if(analogRead(Receive) > 300 && Sms == 0){
      Serial.println("Data Received");
      delay(1000);
      mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
      updateSerial();
      mySerial.println("AT+CMGS=\"+254714673027\"");//change ZZ with country code and 254714673027 with phone number to sms
      updateSerial();
      mySerial.print("T1: "); //text content
      dht_T1.temperature().getEvent(&event_T1);    

      mySerial.print(event_T1.temperature, 1); //text content
      mySerial.print(" C");
      mySerial.print("   ");
      dht_T1.humidity().getEvent(&event_T1);
      mySerial.print(event_T1.relative_humidity, 1);
      mySerial.println(" %");
      mySerial.print("T2: "); //text content
      dht_T2.temperature().getEvent(&event_T2);
      mySerial.print(event_T2.temperature, 1); //text 
      mySerial.print(" C");
      mySerial.print("   ");
      dht_T2.humidity().getEvent(&event_T2);
      mySerial.print(event_T2.relative_humidity, 1);
      mySerial.println(" %");
      mySerial.print("T3: "); //text content
      dht_T3.temperature().getEvent(&event_T3);
      mySerial.print(event_T3.temperature, 1); //text content
      mySerial.print(" C");
      mySerial.print("   ");
      dht_T3.humidity().getEvent(&event_T3);
      mySerial.print(event_T3.relative_humidity, 1);
      mySerial.println(" %");
      mySerial.print("B1: "); //text content
      dht_B1.temperature().getEvent(&event_B1);
      mySerial.print(event_B1.temperature, 1); //text content
      mySerial.print(" C");
      mySerial.print("   ");
      dht_B1.humidity().getEvent(&event_B1);
      mySerial.print(event_B1.relative_humidity, 1);
      mySerial.println(" %");
      mySerial.print("B2: "); //text content
      dht_B2.temperature().getEvent(&event_B2);
      mySerial.print(event_B2.temperature, 1); //text content
      mySerial.print(" C");
      mySerial.print("   ");
      dht_B2.humidity().getEvent(&event_B2);
      mySerial.print(event_B2.relative_humidity, 1);
      mySerial.println(" %");
      mySerial.print("B3: "); //text content
      dht_B3.temperature().getEvent(&event_B3);
      mySerial.print(event_B3.temperature, 1); //text content
      mySerial.print(" C");
      mySerial.print("   ");
      dht_B3.humidity().getEvent(&event_B3);
      mySerial.print(event_B3.relative_humidity, 1);
      mySerial.println(" %");
      updateSerial();
      mySerial.write(26);
      
      while (!receivedConfirmation()) {
        delay(500); // Wait for 0.5 seconds before checking again
      }

      Serial.println("Message sent successfully!");
      Sms = 1;
    }else if(analogRead(Receive) < 500){
      Serial.println("Waiting for Data");
      delay(1000);
      Sms = 0;
      delay(500);
    }
    SendingData = millis(); // Update the last GPS enable time
  }
}
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}
