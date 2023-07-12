#ifndef LIGHT_CONTROLS
#define LIGHT_CONTROLS

void initLightControls();

void setLights(unsigned char red, unsigned char green, unsigned char blue);
void setLight(unsigned int pixel_index, unsigned char red, unsigned char green, unsigned char blue);

#endif // LIGHT_CONTROLS