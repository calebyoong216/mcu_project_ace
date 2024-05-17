#include "Adafruit_NeoPixel.h"
#include <Arduino.h>

Adafruit_NeoPixel matrix;
int led_num;
int prev_led_num = -1;
int analogValue = 0;

void setup() {
    matrix = Adafruit_NeoPixel(32);
    matrix.begin();
    led_num = 0;
    Serial.begin(115200);
}

void loop() {
#ifdef SERVER
    led_num = (int)((analogRead(2) / 1023.0) * 32.0);
    matrix.setPixelColor(prev_led_num, 0, 0, 0);
    matrix.setPixelColor(led_num, 32, 0, 0);
    prev_led_num = led_num;
    led_num++;
    led_num = led_num % 32;
    matrix.show();
#elif defined(CLIENT)
    analogWrite(5, analogValue);
    analogValue += 32;
#endif

    delay(100);
}
