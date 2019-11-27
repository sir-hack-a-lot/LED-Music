#include <Adafruit_NeoPixel.h>

#define LED_PIN 6
#define LED_COUNT 60
#define POT_PIN 0
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);

void setup() {
  pinMode(POT_PIN,INPUT);
  strip.begin();
  strip.show();
  strip.setBrightness(64);  //draws less current
  Serial.begin(9600);
}

void setLevel(Adafruit_NeoPixel & strip, int delay_val, int in_color []){
  uint32_t color = strip.Color(in_color[0], in_color[1], in_color[2]);
  
  for(int i=1; i<LED_COUNT; i++){
    strip.fill(color,0,i);
    
    if (Serial.available() > 0){
      uint8_t serial_bytes [4];
      Serial.readBytes(serial_bytes,4);
      
      delay_val = serial_bytes[3];      
      color = strip.Color(serial_bytes[0], serial_bytes[1], serial_bytes[2]);
    }
    
    delay(delay_val);
    strip.show();
  }
  

  for(int i=LED_COUNT; i>0; i--){
    strip.fill(color,0,i);
    strip.show();
    
    if (Serial.available() > 0){
      uint8_t serial_bytes [4];
      Serial.readBytes(serial_bytes,4);
      
      delay_val = serial_bytes[3];      
      color = strip.Color(serial_bytes[0], serial_bytes[1], serial_bytes[2]);
    }
    
    delay(delay_val);
    strip.clear();
    } 
}

void loop() {
  int color [3];
  color[0]=255; color[1]=0; color[2]=0;
  uint8_t serial_bytes [4];
  
  //int pot = map(analogRead(0), 0 ,1024, 10, 50);
  //setLevel(strip, pot, color);
  
  
  if (Serial.available() > 0){
      Serial.readBytes(serial_bytes,4);
      
      color[0]=serial_bytes[0]; color[1]=serial_bytes[1]; color[2]=serial_bytes[2];  
      setLevel(strip, serial_bytes[3], color);
   }
  
  
    
}
