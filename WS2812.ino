#include <Adafruit_NeoPixel.h>
#define LEDPin 10
#define NumberOfLEDs 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NumberOfLEDs, LEDPin, NEO_GRB + NEO_KHZ800);

void initLED() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}

void runLED(int r1, int g1, int b1, int r2, int g2, int b2) {
  strip.setPixelColor(0, strip.Color(r1, g1, b1));
  strip.setPixelColor(1, strip.Color(r2, g2, b2));
  strip.show(); // Initialize all pixels to 'off'
}

void LEDStatus(int a, int b, int c) {
  strip.setPixelColor(0, strip.Color(a*40, 0, 0));
  strip.setPixelColor(1, strip.Color(b*40, 0, 0));
  strip.setPixelColor(2, strip.Color(c*40, 0, 0));
  strip.show(); // Initialize all pixels to 'off'
}
