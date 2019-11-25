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
      uint8_t incomingByte = Serial.read();
      if (incomingByte != 0xA) { 
        uint8_t in_val = incomingByte;
        if(in_val > 5 && in_val < 500){
          delay_val = in_val;
        }
      }
    }
    delay(delay_val);
    strip.show();
  }
  

  for(int i=LED_COUNT; i>0; i--){
    strip.fill(color,0,i);
    strip.show();
    delay(delay_val);
    strip.clear();
    } 
}

void loop() {
  int color [3];
  color[0]=255; color[1]=0; color[2]=255;
  uint8_t serial_bytes [4];
  
  if (Serial.available() > 0){
      Serial.readBytes(serial_bytes,4);
      
      in_val = serial_bytes[0]
      for (int i=1; i<4; i++){
        color[i]= serial_bytes[i];
      }
      setLevel(strip, in_val, color);
   }
    
}
