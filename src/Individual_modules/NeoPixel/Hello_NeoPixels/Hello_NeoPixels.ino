#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#define LED_PIN    6
#define NUMPIXELS 2
#include <Servo.h>
int read_value;
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);
Servo myservo;
void setup() {
   pixels.begin();
   pixels.show();
   pinMode(13, INPUT);
   pinMode(12, OUTPUT);
   myservo.attach(9);
   Serial.begin(9600);
}

void loop() {
   digitalWrite(12,HIGH);
 
    uint32_t yellow = pixels.Color(255, 252, 0, 255);
    uint32_t green = pixels.Color(0, 255, 0, 255);
    uint32_t red = pixels.Color(255, 0, 0, 255);
    
    read_value = digitalRead(13);
    Serial.println(read_value);
    Serial.println(myservo.read());
    if(read_value == HIGH)
    { 
    pixels.clear();
    pixels.fill(red, 0, 2); //fill the strip (color, start, count)
    pixels.show();
    myservo.write(0); 
    }
    else
    {
    pixels.clear();
    pixels.fill(green, 0, 2); //fill the strip (color, start, count)
    pixels.show();        
    myservo.write(180);  
    }
     
   }
    
  
    
