#include <Arduino.h>
//#include <WiFi.h>               //we are using the ESP32
#include <ESP8266WiFi.h>      // uncomment this line if you are using esp8266 and comment the line above
#include <Firebase_ESP_Client.h>

int LED1 = 16;      // Assign LED1 to pin GPIO2
int LED2 = 5; 
int LED3 = 4; 
int LED4 = 0;     // Assign LED1 to pin GPIO16
//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "MG"
#define WIFI_PASSWORD "bmtl2009"

// Insert Firebase project API Key
#define API_KEY "AIzaSyA9hTeKicT_GzSOsicFyicuxo2FCqR4XE0"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://iotfarming-83203-default-rtdb.firebaseio.com/" 

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;                     //since we are doing an anonymous sign in 
//char   Val[2];
void setup(){
  pinMode(LED1, OUTPUT);

  pinMode(LED2, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop()
{
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 2000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    // Write an Int number on the database path test/int
    Firebase.RTDB.setString(&fbdo, "/FirebaseIOT/S6", "incomingData");

    if (Firebase.RTDB.getInt(&fbdo, "/FirebaseIOT/S1")) 
    {
      
       // Val[] = fbdo.stringData());
       if(fbdo.stringData()=="1")
        digitalWrite(LED1,HIGH);
        else
        digitalWrite(LED1,LOW);
        Serial.print(fbdo.stringData());
        
      }
       if (Firebase.RTDB.getInt(&fbdo, "/FirebaseIOT/S2")) 
    {
      
        //Val[] = fbdo.stringData());
        if(fbdo.stringData()=="1")
        digitalWrite(LED2,HIGH);
        else
        digitalWrite(LED2,LOW);
        Serial.print(fbdo.stringData());
       
      }
      if (Firebase.RTDB.getInt(&fbdo, "/FirebaseIOT/S3")) 
    {
      
      if(fbdo.stringData()=="1")
        digitalWrite(LED3,HIGH);
        else
        digitalWrite(LED3,LOW);
        Serial.print(fbdo.stringData());
        
      }
      if (Firebase.RTDB.getInt(&fbdo, "/FirebaseIOT/S4")) 
    {
      
     if(fbdo.stringData()=="1")
        digitalWrite(LED4,HIGH);
        else
        digitalWrite(LED4,LOW);
        Serial.print(fbdo.stringData());
        
      }
      Serial.println("");
  }
  
    
    
  
}