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

//Relays for switching appliances
#define Relay1            D4
#define Relay2            D6
#define Relay3            D7
#define Relay4            D8
// #define Relay5            D1
// #define Relay6            D2

#define ser               D5



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
  servo.write(pos);
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
  if (strstr(topic, sub10))
  {
    for (int i = 0; i < length; i++)
    {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1')
    {
      Serial.println("ON");
      Serial.println("LOW FAN 3MINS");
      servo.write(105); // LOW FAN 3MINS
      delay(180000);
      
      servo.write(30); // LOW COOL
      
    }
  
    else {
      Serial.println("OFF");
      Serial.println("LOW FAN 3MINS");
      servo.write(105); // LOW FAN 3MINS
      delay(180000);
      servo.write(180);
    }
  }


  
  
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
      servo.write(30);
     Serial.println("2");
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
      Serial.println("3");
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



//////////////////////////********************** ON 1HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub7))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {
      Serial.println("1HR");
      
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


//////////////////////////**********************ON 2HR ************************ ///////////////////////////////////
  else if ( strstr(topic, sub9))
  {
    for (int i = 0; i < length; i++) {
      Serial.print((char)payload[i]);
    }
    Serial.println();
    // Switch on the LED if an 1 was received as first character
    if ((char)payload[0] == '1') {

      Serial.println("2HR");
      
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



void setup()
{

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