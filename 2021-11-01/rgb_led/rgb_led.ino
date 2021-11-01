#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(2,5,NEO_GRB + NEO_KHZ800);

void setup()
{
  Serial.begin(9600);

  pixels.begin();

  pixels.setBrightness(30);


}


void loop()
{
  pixels.setPixelColor(0,pixels.Color(0,255,0));
  pixels.setPixelColor(1,pixels.Color(0,255,0));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0,pixels.Color(255,0,0));
  pixels.setPixelColor(1,pixels.Color(255,0,0));
  pixels.show();
  delay(1000);
  pixels.setPixelColor(0,pixels.Color(0,0,255));
  pixels.setPixelColor(1,pixels.Color(0,0,255));
  pixels.show();
  delay(1000);
}
