// IOTA Vending Machine IO Board for 5 Products with ArduinoYun

// D13 - IO Reday
// D12 - Setup button read http://192.168.240.1/arduino/digital/12 if button pushet opening url http://192.168.240.2
// D11 - Product 1 set http://192.168.240.1/arduino/digital/11/1
// D10 - Product 2 set http://192.168.240.1/arduino/digital/10/1
// D 9 - Product 3 set http://192.168.240.1/arduino/digital/9/1
// D 5 - Product 4 set http://192.168.240.1/arduino/digital/4/1
// D 3 - Product 5 set http://192.168.240.1/arduino/digital/3/1
// D 4 - optional for detecting product output success, is option but not testing yet!

// D 6 - WS2812 LEDs NeoPixel Stripe

// A 0 - IR sensor empty 1 (true/false) http://192.168.240.1/arduino/analog/0
// A 1 - IR setup button (true/false) http://192.168.240.1/arduino/analog/1
// A 2 - IR sensor empty 3 (true/false) http://192.168.240.1/arduino/analog/2
// A 3 - IR sensor empty 4 (true/false) http://192.168.240.1/arduino/analog/3
// A 4 - IR sensor empty 5 (true/false) http://192.168.240.1/arduino/analog/4

// API Server IP is in my case 192.168.240.2 (change it to your Serrver IP adress)



#include <Bridge.h>             // bridge to openwrt
#include <BridgeServer.h>       // make http server avirable 
#include <BridgeClient.h>       // make http client avirable
#include <Adafruit_NeoPixel.h>  // lib for ws2812 Neopixels
#define PIN            6        // pin there is ws2812 NeoPixel connectet
#define NUMPIXELS      7        // numbers of ws2812 Neopixels
#include <Servo.h>              // Servo Motor
#include <Process.h>            // Process is need for cURL command if setup button pressed

const int setupbutton = 12; 
int buttonState = 0;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // create Neopixel object to control ws2812 

Servo myservo;         // create servo object to control a servo
int pos = 0;           // variable to store the servo position

BridgeServer server;   // Listen to the default port 5555, the Yún webserver,will forward there all the HTTP requests you send 


void setup() {
  // Bridge startup
  pixels.begin();
  pinMode(A0, INPUT);
  pinMode(A1, OUTPUT);
  analogWrite(A1, 0);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);    
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(setupbutton, INPUT);
  Bridge.begin();
  Serial.begin(115200);
  digitalWrite(13, HIGH);
  Serial.println("ready"); 
  //myservo.attach(3);         // attaches the servo on pin 9 to the servo object  
  

  // Listen for incoming connection only from localhost
  // (no one from the external network could connect)
  server.listenOnLocalhost();
  server.begin();  
}

void loop() {
  // Get clients coming from server
  BridgeClient client = server.accept();

  // There is a new client?
  if (client) {
    // Process request
    process(client);

    // Close connection and free resources.
    client.stop();
  }
  myservo.detach();
  delay(50); // Poll every 50ms

    if (analogRead(A0) < 600) {
     for(int i=0;i<NUMPIXELS;i++){                     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(100,0,0));  // Moderately bright green/blue color.
      pixels.show();                                   // This sends the updated pixel color to the hardware.
      delay(10);                                       // Delay for a period of time (in milliseconds).
     }     
    } 
     else {
      for(int i=0;i<NUMPIXELS;i++){                     // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
       pixels.setPixelColor(i, pixels.Color(0,60,30));  // Moderately bright green/blue color.
       pixels.show();                                   // This sends the updated pixel color to the hardware.
       delay(10);                                       // Delay for a period of time (in milliseconds).
      }
    }

     buttonState = digitalRead(setupbutton);            // Setup button state for init setup mode
      if (buttonState == HIGH) {
       Serial.println("Setup button on ");
       analogWrite(A1, 255);
      } 
    else {
       analogWrite(A1, 0);
       Serial.println("Setup button off ");
      }
}


void process(BridgeClient client) {
  // read the command
  String command = client.readStringUntil('/');


  client.println("Status: 200");
  client.println("Access-Control-Allow-Origin: *");   
  client.println("Access-Control-Allow-Methods: GET");
  client.println("Content-Type: text/html");
  client.println("Connection: close");
  client.println();
  

  // is "digital" command?
  if (command == "digital") {
    digitalCommand(client);
  }

  // is "analog" command?
  if (command == "analog") {
    analogCommand(client);
  }
  
}



void digitalCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL, with a value like: "/digital/13/1"
  if (client.read() == '/') {
    value = client.parseInt();
    digitalWrite(pin, value);
  } else {
    value = digitalRead(pin);
  }

  // Send feedback to client and to seriell
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" is "));
  client.println(value);
  Serial.print(F("Pin D"));
  Serial.print(pin);
  Serial.print(F(" is "));
  Serial.println(value);


  if (digitalRead(11) == HIGH){        // Motor runtime to need output product  
    for(int i=0;i<NUMPIXELS;i++) {                    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0,100,0)); // Moderately bright green color.
      pixels.show();                                  // This sends the updated pixel color to the hardware.
      delay(0);                                       // Delay for a period of time (in milliseconds).
    }
    Serial.println("set Motor on");
    delay(2);                       // Motor runtime to need output product
      myservo.attach(3);
      for (pos = 200; pos >= 0; pos -= 1)
     {   // goes from 0 degrees to 90 degrees, in steps of 1 degree
      myservo.write(pos);                   // tell servo to go to position in variable 'pos'
      delay(5);                             // waits 15ms for the servo to reach the position
    }
      for (pos = 0; pos <= 200; pos += 1) {   // goes from 90 degrees to 0 degrees
      myservo.write(pos);                   // tell servo to go to position in variable 'pos'
      delay(5);                             // waits 15ms for the servo to reach the position
      myservo.detach();
    }   
  }

  if (digitalRead(10) == HIGH){ 
    Serial.println("set Motor on");
    delay(200);                       // Motor runtime to need output product
  }

  if (digitalRead(9) == HIGH){ 
    Serial.println("set Motor on");
    delay(200);                       // Motor runtime to need output product
  }

  if (digitalRead(5) == HIGH){ 
    Serial.println("set Motor on");
    delay(200);                       // Motor runtime to need output product
  }

  if (digitalRead(3) == HIGH){ 
    Serial.println("set Motor on");    
    delay(200);                       // Motor runtime to need output product
  }



  if (digitalRead(11) == HIGH){ 
    digitalWrite(11, LOW);             // Motor set if off
    Serial.println("set Motor off");  
  }

  if (digitalRead(10) == HIGH){ 
    digitalWrite(10, LOW);             // Motor set if off
    Serial.println("set Motor off");  
  }

  if (digitalRead(9) == HIGH){ 
    digitalWrite(9, LOW);              // Motor set if off
    Serial.println("set Motor off");  
  }

  if (digitalRead(5) == HIGH){ 
    digitalWrite(5, LOW);              // Motor set if off
    Serial.println("set Motor off");  
  }

  if (digitalRead(3) == HIGH){ 
    digitalWrite(3, LOW);              // Motor set if off
    Serial.println("set Motor off");
  }

  //client.println("Access-Control-Allow-Origin: *");
  client.println("success");           // Product is out message Client
  Serial.println("success");           // Product is out message debug
  
  // Update datastore key with the current pin value
  String key = "D";
  key += pin;
  Bridge.put(key, String(value));
}

void analogCommand(BridgeClient client) {
  int pin, value;

  // Read pin number
  pin = client.parseInt();

  // If the next character is a '/' it means we have an URL, with a value like: "/analog/5/120"
  if (client.read() == '/') {
    // Read value and execute command
    value = client.parseInt();
    analogWrite(pin, value); 


    // Send feedback to client
    client.print(F("Pin A"));
    client.print(pin);
    client.print(F(" set to analog "));
    client.println(value);

    // Serial output   
    Serial.print(F(" Pin A"));
    Serial.print(pin);
    Serial.print(F(" read analog = "));
    Serial.println(value);

    // Update datastore key with the current pin value
    String key = "D";
    key += pin;
    Bridge.put(key, String(value));
  } 
  
  else {
    // Read analog pin
    value = analogRead(pin);

    // Send analog feedback to client
    if (value > 600) {
      client.print("true");
      Serial.println("true");     
    } 
    else {
      client.print("false");
      Serial.println("false");
    }

    // Update datastore key with the current pin value
    String key = "A";
    key += pin;
    Bridge.put(key, String(value));
  }
}
