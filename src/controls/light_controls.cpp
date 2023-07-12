#include "controls/light_controls.h"

#include <Adafruit_NeoPixel.h>
#include "config.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM_PIXELS, LED_DATA_PIN, NEO_RGB + NEO_KHZ400);

void initLightControls()
{
    strip.begin();
    setLights(0, 0, 0); // turn off lights
}

void setLights(unsigned char red, unsigned char green, unsigned char blue)
{
    for (unsigned int pixel_index = 0; pixel_index < LED_NUM_PIXELS; pixel_index++)
    {
        setLight(pixel_index, red, green, blue);
    }
}

void setLight(unsigned int pixel_index, unsigned char red, unsigned char green, unsigned char blue)
{
    if (pixel_index >= LED_NUM_PIXELS)
    {
        Serial.printf("Invalid pixel index: '%d'\r\n", pixel_index);
        return;
    }

    if (red > 255 || green > 255 || blue > 255) {
        Serial.printf("Invalid color value: rgb(%d, %d, %d)\r\n", red, green, blue);
        return;
    }

    unsigned int color = (red << 16) | (green << 8) | blue;
    strip.setPixelColor(pixel_index, color);
    strip.show();
}