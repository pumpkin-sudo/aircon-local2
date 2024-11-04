//OFF- 180 
//L FAN - 105
//L COOL - 30



#ifdef ESP8266
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#else
#error "Board not found"
#endif
#include <Servo.h> 
#include <PubSubClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_ADDR   0x3C
Adafruit_SSD1306 display(128, 64, &Wire, -1);



//Relays for switching appliances
#define Relay1            D4
#define Relay2            D6
#define Relay3            D7
#define Relay4            D8
// #define Relay5            D1
// #define Relay6            D2

#define ser               D5
////////////////////////////////////////////////////////////////////
// Define global variables for timing
unsigned long previousMillis = 0;
const long fanDelay = 15000; // 30 seconds

// Variable to track the state of the servo
bool fanActive = false;
///////////////////////////////////////////////////

Servo servo;
// Update these with values suitable for your network.

const char* ssid = "PLDTHOMEFIBR6b250";
const char* password = "PLDTWIFI9ubrw";
const char* mqtt_server = "192.168.1.27"; // Local IP address of Raspberry Pi

const char* username = "";
const char* pass = "";
int pos=0;

// Subscribed Topics

#define sub1 "device1/relay1" //OFF SLOT
#define sub2 "LOW COOL" // 
#define sub3 "LOW FAN"
#define sub4 "Manual/OFF"
#define sub5 "device1/relay5"
#define sub6 "device1/relay6"
#define sub7 "device1/relay7"
#define sub9 "device1/relay9"
#define sub10 "aircon on"
#define sub11 "aircon off"// slot


WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE  (50)
char msg[MSG_BUFFER_SIZE];
int value = 0;


// Connecting to WiFi Router

void setup_wifi()
{

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length)
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
//  servo.write(pos);
//////////////////////////**********************OFF************************ /////////////////////////////////// 
  if (strstr(topic, sub1))
  {
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1')
    {
      Serial.println("off");
      servo.write(180); // off
    }
  
  }



//////////////////////////**********************AIRCON (GOOGLE)************************ /////////////////////////////////// 
  else if (strstr(topic, sub10))
  {
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1'){

     
      servo.write(105); // LOW FAN 3MINS
      Serial.println("LOW FAN 3MINS");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Voice on");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("LOW FAN");
      display.display();    

      
//      delay(10000);
//      servo.write(30); // LOW COOL
//      Serial.println("LOW COOL pass");
    }
  
    else {
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("Voice on");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("TURNING OFF");
      display.display();   
       
      Serial.println("OFF");
      Serial.println("LOW FAN 3MINS");
      servo.write(105); // LOW FAN 3MINS
      delay(120000);
      
      servo.write(180);
    }
  }




//========== delay na pwede mag work ang ibang condition using millis ===================
//else if (strstr(topic, sub10)) {
//    // Print the payload
//    for (int i = 0; i < length; i++) {
//      Serial.print((char)payload[i]);
//    }
//    Serial.println();
//
//    // Switch on the LED if a '1' was received as the first character
//    if ((char)payload[0] == '1') {
//      if (!fanActive) {
//        // Start the fan
//        servo.write(105); // LOW FAN 3MINS
//        Serial.println("LOW FAN 3MINS");
//        previousMillis = millis(); // Record the start time
//        fanActive = true;
//      }
//    }
//  
//
//  // Handle the non-blocking delay
//  if (fanActive) {
//    unsigned long currentMillis = millis();
//    if (currentMillis - previousMillis >= fanDelay) {
//      // Time has elapsed, switch the servo
//      servo.write(30); // LOW COOL
//      Serial.println("LOW COOL pass");
//      fanActive = false; // Reset the state
//    }
//  }
//}


//////////////////////////**********************LOW COOL************************ ///////////////////////////////////
  else if ( strstr(topic, sub2))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      digitalWrite(Relay2, HIGH);   //

//      display.clearDisplay();
//      display.setTextSize(1);
//      display.setCursor(0,0);
//      display.println("John Aircon");
//      display.setTextSize(2);
//      display.setCursor(0,12);
//      display.println("LOW FAN");
//      display.display();     
//      servo.write(105);
//      delay(10000);
      
      servo.write(30);
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("John Aircon");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("LOW COOL");
      display.display();  
      Serial.println("low cool");
     

     
    }
//    else {
//      digitalWrite(Relay2, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }

//////////////////////////**********************LOW FAN************************ ///////////////////////////////////
  else if ( strstr(topic, sub3))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      digitalWrite(Relay3, HIGH);
      servo.write(105);
      Serial.println("low fan");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("John Aircon");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("LOW FAN");
      display.display();    
//       startTimer();

  



    } 
//    else {
//      digitalWrite(Relay3, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }
//////////////////////////**********************MANUAL OFF************************ ///////////////////////////////////
  else if ( strstr(topic, sub4))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
    
//      for (pos = 180; pos >= 0; pos-= 1){
//        servo.write(pos);
//        delay(15);
//      }

      servo.write(180);
      Serial.println("4");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("John Aircon");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("OFF");
      display.display();    
    } 
//    else {
//      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }



//////////////////////////**********************TIMER 1HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub5))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      Serial.println("1HR");
      Serial.println("LOW FAN 3MINS");
      servo.write(105); // LOW FAN 3MINS
      delay(180000);
      
      servo.write(30); // LOW COOL
      Serial.println("LOW COOL");
      delay(3.6e+6);
      
      servo.write(105); // LOW FAN 3MINS
      Serial.println("LOW FAN 3MINS");
      delay(180000);
      
      servo.write(180);   // OFF
    } 

//    else {
//      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }

//////////////////////////**********************TIMER 2HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub6))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      
      Serial.println("2HR");
      Serial.println("LOW FAN 3MINS");
      servo.write(105); // LOW FAN 3MINS
      delay(180000);
      
      servo.write(30); // LOW COOL
      Serial.println("LOW COOL");
      delay(7.2e+6);
      
      servo.write(105); // LOW FAN 3MINS
      Serial.println("LOW FAN 3MINS");
      delay(180000);
      
      servo.write(180);   // OFF


    } 
//    else {
//      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }



//////////////////////////********************** ALREADY ON 1HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub7))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      Serial.println("1HR");

      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("John Aircon");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("TIMER 1 HR");
      display.display();    
      
      servo.write(30); // LOW COOL
      Serial.println("LOW COOL");
      delay(3.6e+6);
      
      servo.write(105); // LOW FAN 3MINS
      Serial.println("LOW FAN 3MINS");
      delay(180000);
      
      servo.write(180);   // OFF
    } 

//    else {
//      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }


//////////////////////////*********************ALREADY ON 2HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub9))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {

      Serial.println("2HR");
      display.clearDisplay();
      display.setTextSize(1);
      display.setCursor(0,0);
      display.println("John Aircon");
      display.setTextSize(2);
      display.setCursor(0,12);
      display.println("TIMER 2 HR");
      display.display();  
      
      servo.write(30); // LOW COOL
      Serial.println("LOW COOL");
      delay(7.2e+6);
      
      servo.write(105); // LOW FAN 3MINS
      Serial.println("LOW FAN 3MINS");
      delay(180000);
      
      servo.write(180);   // OFF


    } 
//    else {
//      digitalWrite(Relay4, LOW);  // Turn the LED off by making the voltage HIGH
//    }
  }


  else
  {
    Serial.println("unsubscribed topic");
  }

}


// Connecting to MQTT broker

void reconnect()
{
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (client.connect(clientId.c_str() , username, pass)) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe(sub1);
      client.subscribe(sub2);
      client.subscribe(sub3);
      client.subscribe(sub4);
      client.subscribe(sub5);
      client.subscribe(sub6);
      client.subscribe(sub7);
      client.subscribe(sub9);
      client.subscribe(sub10);
      client.subscribe(sub11);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
//void lowcool() {
//  Serial.println("lowcool");
//  servo.write(30);
//  delay(5000);
//  }
//


//void startTimer() {
//  int totalSeconds = 180; // 3 minutes = 180 seconds
//  
//  for (int i = totalSeconds; i >= 0; i--) {
//    int minutes = i / 60;
//    int seconds = i % 60;
//    
//    display.clearDisplay();
//    display.setTextSize(2);
//    display.setTextColor(SSD1306_WHITE);
//    display.setCursor(0, 20);
//    display.printf("Time: %02d:%02d", minutes, seconds);
//    display.display();
//    
//    delay(1000); // Wait for 1 second
//  }
//  
//  // Display "Time's up!" when the timer reaches 0
//  display.clearDisplay();
//  display.setTextSize(2);
//  display.setTextColor(SSD1306_WHITE);
//  display.setCursor(0, 20);
//  display.println("Time's up!");
//  display.display();
//}

void setup()
{
   if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(0,0);
  display.println("John pogi");
  display.display();


  
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);

  servo.attach(ser, 500, 2400);
  Serial.begin(115200);
  servo.write(180);
  setup_wifi();

  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop()
{

  if (!client.connected()) 
  {
    reconnect();
  }
  client.loop();

}