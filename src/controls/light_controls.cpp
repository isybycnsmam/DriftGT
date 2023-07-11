#include "controls/light_controls.h"

#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM_PIXELS, LED_DATA_PIN, NEO_RGB + NEO_KHZ400);

void init_light_controls()
{
    strip.begin();
    set_lights(0x000000); // turn off lights
}

void set_lights(unsigned int color)
{
    for (int i = 0; i < LED_NUM_PIXELS; i++)
    {
        set_light(i, color);
    }
}

void set_light(unsigned int index, unsigned int color)
{
    if (index >= LED_NUM_PIXELS)
    {
        Serial.printf("Invalid pixel index: '%d'\r\n", index);
        return;
    }

    strip.setPixelColor(index, color);
    strip.show();
}